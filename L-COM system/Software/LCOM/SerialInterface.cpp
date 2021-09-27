/*
*   Author  :   Stephen Amey
*   Date    :   Aug. 28, 2021
*/


#include "SerialInterface.h"


/*-------------------------------------------------------------------------*\
|								   Variables					   			|
\*-------------------------------------------------------------------------*/


    uint8_t serialReadBuffer[PKT_MAX_LEN]; // Need separate buffers as the read buffer may fill over several loops
    uint8_t serialSendBuffer[PKT_MAX_LEN];
    bool startFlagFound = false;
    uint16_t rIdx = 0;
    uint16_t packetLen = 0;
    uint8_t cyclicID = 0;
    uint16_t sendBufferLen = 0;
    uint32_t lastCharReceivedTime = 0;


/*-------------------------------------------------------------------------*\
|								   Functions					   			|
\*-------------------------------------------------------------------------*/


    /*-------------------------------------------------------------------------------------*\
    |   Name:       readSerial                                                              |
    |   Purpose:    Checks for new serial data and reads it into the buffer.                |
    |   Arguments:  void                                                                    |
    |   Returns:    int16_t                                                                 |
    \*-------------------------------------------------------------------------------------*/
    int16_t readSerialData(void){
        /* Wait for new serial data */
        if(Serial.available()){

            // Read in the next character
            uint8_t newSerialByte = Serial.read();
            lastCharReceivedTime = millis();

            // If the start of a new packet was found, set the flag and prepare the buffer
            if(!startFlagFound && newSerialByte == START_FLAG){
                startFlagFound = true;
                rIdx = 0;
                packetLen = 0;
                for(uint16_t i = 0; i != PKT_MAX_LEN; i++) serialReadBuffer[i] = 0; 
            }

            // If the start flag was found
            if(startFlagFound){

                // Add the byte to the buffer
                serialReadBuffer[rIdx++] = newSerialByte;

                // Record the length of the packet
                if(rIdx == LENGTH_INDEX+2){
                    packetLen = extract_uint16_t(serialReadBuffer, LENGTH_INDEX);
                }

                // If the end flag was found, verify the packet
                if(rIdx == packetLen){

                    // Reset the flag
                    startFlagFound = false;

                    // If the packet is valid, handle it
                    if(verifyPacket(serialReadBuffer)){
                        return PACKET_COMPLETE;
                    }
                    else{
                        return MALFORMED_PACKET;                      
                    }
                }
                // Else if the end flag was not found and the buffer is full, reset the flag
                else if(rIdx == PKT_MAX_LEN){                   
                    startFlagFound = 0;
                    Log(F("Packet reading error"), MALFORMED_PACKET);
                    return MALFORMED_PACKET;
                }
            }
            return NEW_PARTIAL_SERIAL_DATA;
        }
        else{
            if(startFlagFound && (millis() - lastCharReceivedTime) > SERIAL_PACKET_TIMEOUT){
                startFlagFound = false;
                Serial.flush();
                Log(F("Packet timeout\r\n"));
            }
            return NO_NEW_SERIAL_DATA;
        }
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getSerialSebdBuffer                                                     |
    |   Purpose:    Returns a pointer to the outgoing serial data buffer.                   |
    |   Arguments:  void                                                                    |
    |   Returns:    int16_t                                                                 |
    \*-------------------------------------------------------------------------------------*/
    //uint8_t* getSerialSendBuffer(void){
    //    return serialSendBuffer;
    //}

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getSerialReadBuffer                                                     |
    |   Purpose:    Returns a pointer to the incoming serial data buffer.                   |
    |   Arguments:  void                                                                    |
    |   Returns:    int16_t                                                                 |
    \*-------------------------------------------------------------------------------------*/
    uint8_t* getSerialReadBuffer(void){
        return serialReadBuffer;
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getSerialReadBufferLength                                                     |
    |   Purpose:    Returns the data length in bytes of the last received serial data.      |
    |   Arguments:  void                                                                    |
    |   Returns:    int16_t                                                                 |
    \*-------------------------------------------------------------------------------------*/
    uint16_t getSerialReadBufferLength(void){
        return packetLen;
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       verifyPacket                                                            |
    |   Purpose:    Verifies a packet by checking for the start and end flags.              |
    |               Does not check the rest of the packet content, e.g. packet type.        |
    |   Arguments:  uint8_t* buf                                                            |
    |   Returns:    boolean                                                                 |
    \*-------------------------------------------------------------------------------------*/
    bool verifyPacket(uint8_t* buf){
        // Ensure the first byte is the start flag
        if(buf[0] != START_FLAG){
            Log(F("Packet verification error"), MISPLACED_START_FLAG);
            return false;
        }

        // Find the length of the packet, and verify that the end flag is in the correct location
        uint16_t len = extract_uint16_t(buf, LENGTH_INDEX);
        if(buf[len-1] != END_FLAG){
            Log(F("Packet verification error"), MISPLACED_END_FLAG);
            return false;
        }

        // If passed the checks, return valid
        return true;
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       createPacket                                                            |
    |   Purpose:    Creates a serial packet with a given payload.              				|
    |   Arguments:  uint8_t, uint8_t*, uint16_t                                             |
    |   Returns:    uint8_t*                                                                |
    \*-------------------------------------------------------------------------------------*/
    uint8_t* createPacket(uint8_t type, uint8_t* payloadBuf, uint16_t bufLen){
        // Start flag
        serialSendBuffer[0] = START_FLAG;
        
        // Packet type and ID
        serialSendBuffer[1] = ((type & 0b00000111) << 5) | (getPacketID() & 0b00011111);
        
        // Packet length
        serialSendBuffer[2] = (bufLen & 0xFF00) >> 8;
        serialSendBuffer[3] = bufLen & 0x00FF;

        // UNIX time
        uint32_t curTime = getUnixTime();
        serialSendBuffer[4] = (curTime & 0xFF000000) >> 24;
        serialSendBuffer[5] = (curTime & 0x00FF0000) >> 16;
        serialSendBuffer[6] = (curTime & 0x0000FF00) >> 8;
        serialSendBuffer[7] = (curTime & 0x000000FF);
		
        // Payload
        memcpy(serialSendBuffer+PAYLOAD_INDEX, payloadBuf, bufLen);

        // End flag
        serialSendBuffer[bufLen+PAYLOAD_INDEX] = END_FLAG;
				
        // Clear the rest of the buffer       
        for(uint16_t i = bufLen+PKT_HEADER_TRAILER_LEN; i != PKT_MAX_LEN; i++) serialSendBuffer[i] = 0;

        // Set the send buffer length
        sendBufferLen = bufLen+PKT_HEADER_TRAILER_LEN;
        
        return serialSendBuffer;
    }
	
    /*-------------------------------------------------------------------------------------*\
    |   Name:       createAckPacket                                                         |
    |   Purpose:    Creates an Ack serial packet with the given result and return data.		|
    |   Arguments:  int16_t, uint8_t*, uint16_t                                             |
    |   Returns:    uint8_t*                                                                |
    \*-------------------------------------------------------------------------------------*/	
    uint8_t* createAckPacket(int16_t res, uint8_t* retBuf, uint16_t bufLen){
        // Shift all bytes forward twice for non-zero payloads
        if(bufLen > 0){           
            for(uint16_t i = bufLen-1; i >= 2; i--) retBuf[i] = retBuf[i-2];
        }
                
        // Set the result field
        retBuf[0] = (res & 0xFF00) >> 8;
        retBuf[1] = res & 0x00FF;
		
        // Create and return the packet
        return createPacket(ACK_PACKET, retBuf, bufLen+2);
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       createMessagePacket                                                     |
    |   Purpose:    Creates a message serial packet with the given result and return data.  |
    |   Arguments:  uint16_t, float, float, uint8_t*, uint16_t                              |
    |   Returns:    uint8_t*                                                                |
    \*-------------------------------------------------------------------------------------*/
    uint8_t* createMessagePacket(int16_t res, float RSSI, float SNR, uint8_t* retBuf, uint16_t bufLen){       
        // Buffer for the float->uint32_t bytes conversion
        uint32_t fBytes;
        
        // Shift all bytes forward ten for non-zero payloads
        if(bufLen > 0){           
            for(uint16_t i = bufLen-1; i >= 10; i--) retBuf[i] = retBuf[i-2];
        }
        
        // Set the result field
        retBuf[0] = (res & 0xFF00) >> 8;
        retBuf[1] = res & 0x00FF;

        // Set the RSSI field
        fBytes = *((uint32_t *) &RSSI);
        retBuf[6] = (fBytes & 0xFF000000) >> 24;
        retBuf[7] = (fBytes & 0x00FF0000) >> 16;
        retBuf[8] = (fBytes & 0x0000FF00) >> 8;
        retBuf[9] = (fBytes & 0x000000FF);

        // Set the SNR field
        fBytes = *((uint32_t *) &SNR);
        retBuf[6] = (fBytes & 0xFF000000) >> 24;
        retBuf[7] = (fBytes & 0x00FF0000) >> 16;
        retBuf[8] = (fBytes & 0x0000FF00) >> 8;
        retBuf[9] = (fBytes & 0x000000FF);
        
        // Create and return the packet
        return createPacket(ACK_PACKET, retBuf, bufLen+10);
    }

	/*-------------------------------------------------------------------------------------*\
    |   Name:       getPacketID                                                             |
    |   Purpose:    Returns a cyclic 5-bit packet ID.                                       |
    |   Arguments:  void                                                                    |
    |   Returns:    uint8_t                                                                 |
    \*-------------------------------------------------------------------------------------*/
    uint8_t getPacketID(){
        if(++cyclicID > 0b00011111) cyclicID = 0;
        return cyclicID;
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getSendBufferLen                                                        |
    |   Purpose:    Returns the length of the last packet data in the send buffer.          |
    |   Arguments:  void                                                                    |
    |   Returns:    uint16_t                                                                |
    \*-------------------------------------------------------------------------------------*/
    uint16_t getSendBufferLen(){
        return sendBufferLen;
    }
