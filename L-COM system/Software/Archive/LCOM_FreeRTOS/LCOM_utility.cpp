/*
*   Author  :   Stephen Amey
*   Date    :   July 18, 2021
*/


#include "LCOM_utility.h"


/*-------------------------------------------------------------------------*\
|								   Variables					   			|
\*-------------------------------------------------------------------------*/


    uint8_t cyclicID = 0;

    bool UNIXSet = false;
    uint32_t epoch, currentTime = 0;
    uint32_t lastMillis = 0;

    uint8_t payloadBuffer[PKT_MAX_DATA_PAYLOAD_LEN];


/*-------------------------------------------------------------------------*\
|								   Functions					   			|
\*-------------------------------------------------------------------------*/


	/*-------------------------------------------------------------------------------------*\
    |   Name:       verifyPacket                                                            |
    |   Purpose:    Verifies a packet by checking for the start and end flags.              |
    |               Does not check the rest of the packet content, e.g. packet type.        |
    |   Arguments:  uint8_t *buf                                                            |
    |   Returns:    boolean                                                                 |
    \*-------------------------------------------------------------------------------------*/
    boolean verifyPacket(uint8_t *buf){        
        // Ensure the first byte is the start flag
        if(buf[0] != START_FLAG){
            Serial.println(F("Bad start flag"));
            return false;
        }

        // Find the length of the packet, and verify that the end flag is in the correct location
        uint8_t len = buf[LENGTH_INDEX];
        if(buf[len-1] != END_FLAG){
            Serial.println(F("Bad end flag"));
            return false;
        }

        // If passed the checks, return valid
        return true;
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       createPacket                                                            |
    |   Purpose:    Creates a packet with a given payload.                                  |
    |   Arguments:  uint8_t *buf                                                            |
    |   Returns:    boolean                                                                 |
    \*-------------------------------------------------------------------------------------*/
    void createPacket(uint8_t *buf, uint8_t type, uint8_t *payloadBuf, uint16_t bufLen){

        // Clear the buffer       
        for(uint16_t i = 0; i != PKT_MAX_LEN; i++) buf[i] = 0;

        // Start flag
        buf[0] = START_FLAG;
        
        // Packet type and ID
        buf[1] = ((type & 0b00000111) << 5) | (getPacketID() & 0b00011111);
        
        // Packet length
        buf[2] = (bufLen & 0xFF00) >> 8;
        buf[3] = bufLen & 0x00FF;

        // UNIX time
        uint32_t curTime = getCurrentTime();
        buf[4] = (curTime & 0xFF000000) >> 24;
        buf[5] = (curTime & 0x00FF0000) >> 16;
        buf[6] = (curTime & 0x0000FF00) >> 8;
        buf[7] = (curTime & 0x000000FF);

        // Payload
        memcpy(buf+8, payloadBuf, bufLen);

        // End flag
        buf[bufLen+8] = END_FLAG;
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       createAckPacket                                                         |
    |   Purpose:    Creates an Ack packet and returns it.                                   |
    |   Arguments:  uint8_t *buf, uint16_t res, uint8_t *retDataBuf                         |
    |   Returns:    boolean                                                                 |
    \*-------------------------------------------------------------------------------------*/
    void createAckPacket(uint8_t *buf, uint16_t res, uint8_t *retDataBuf, uint16_t bufLen){
        // Clear the payload buffer      
        for(uint16_t i = 0; i != PKT_MAX_LEN; i++) payloadBuffer[i] = 0;

        // Set the result field
        payloadBuffer[0] = (res & 0xFF00) >> 8;
        payloadBuffer[1] = res & 0x00FF;

        // Copy the rest of the data into the buffer
        if(bufLen != 0 || retDataBuf != NULL){
            memcpy(payloadBuffer+2, retDataBuf, bufLen);
        }
        // Ensure buf len is zero if data buffer is null
        else{
            bufLen = 0; 
        }

        // Create the packet
        createPacket(buf, ACK_PACKET, payloadBuffer, bufLen+2);
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getCurrentTime                                                          |
    |   Purpose:    Returns the current time based on UNIX epoch. 0 if not set.             |
    |   Arguments:  void                                                                    |
    |   Returns:    uint32_t                                                                |
    \*-------------------------------------------------------------------------------------*/
    uint32_t getCurrentTime(){
        // Return 0 if UNIX epoch not set
        if(!UNIXSet) return 0;

        // Find the new current time and return it
        currentTime += (uint32_t)((millis() - lastMillis)/1000);
        lastMillis = millis();
        return currentTime;
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       extract_<data type>                                                     |
    |   Purpose:    Extracts a variable of a given data type from a byte array.             |
    |               These functions are used to deal with byte-alignment and endianess.     |
    |               If using printf(), remember to use the long-type identifiers if needed. |
    |   Arguments:  uint8_t *buffer, uint16_t position                                      |
    |   Returns:    <data type>                                                             |
    \*-------------------------------------------------------------------------------------*/
        uint32_t extract_uint32_t(const uint8_t *buf, uint16_t pos){ 
            return ((uint32_t)buf[pos] << 24) | ((uint32_t)buf[pos+1] << 16) | ((uint32_t)buf[pos+2] << 8) | ((uint32_t)buf[pos+3]);
        }  
        uint16_t extract_uint16_t(const uint8_t *buf, uint16_t pos){
            return ((uint16_t)buf[pos] << 8) + ((uint16_t)buf[pos+1]);
        }  
		uint8_t extract_uint8_t(const uint8_t *buf, uint16_t pos){
            return (uint8_t)buf[pos];
        }  		
        float extract_float(const uint8_t *buf, uint16_t pos){
            uint32_t uint_bytes = ((uint32_t)buf[pos] << 24) + ((uint32_t)buf[pos+1] << 16) + ((uint32_t)buf[pos+2] << 8) + ((uint32_t)buf[pos+3]);
            return *((float *) &uint_bytes);
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
