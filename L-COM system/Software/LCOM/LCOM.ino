/*
*   Author  :   Stephen Amey
*   Date    :   Aug. 28, 2021
*   Purpose :   This software is used to run the LCOM (LoRa communication) module. It provides both receival and transmission of data, and interfacing with an external device via UART.
*/

/*
 * RadioLib operates at 902MHz for this EBYTE module. Amateur band is 902-928MHz.
 * The antenna used is 915MHz, so I assume this is close enough that it won't cause issues.
 */
 /*
  * To do:
  * The repeater message stuff doesn't feel like it fits in Utility. Really, it doesn't fit anywhere except for the main LCOM file.
  * This is because the actual functionality still has to be implemented in LCOM file anyways. Fix this later.
  * 
  * Consider removing status packets entirely?
  * We return data in Ack packets, so might as well just use that.
  * 
  * 
  * Commands uses the buffer from SerialInterface. The buffer is also bigger than needed for commands.
  * Thus, reuse the serial buffer again for the Ack packet, since really that's the appropriate one anyways considering semantics.
  * So instead of command buffer, put it back into buf, but do record the length.
  * 
  * The buffer passing in parameters is automatically bigger than the max return size by 1 byte (repeater command), so make it the programmers duty to make the buffer and know that the result is passed back to it.
  * 
  */

// Commands
    // Status codes
    // Serial (any initialization, and input/output functions. Packet creation, verification, getID). Definitions in header.
    // Utility (variable extraction, time, temperature)

    // Tasks:
    // Serial receive
    // LoRa receive (via flag)
    // Housekeeping (e.g. temperature)
    // Watchdog kick

/*-------------------------------------------------------------------------*\
|                                  Includes                                 |
\*-------------------------------------------------------------------------*/


    #include <avr/wdt.h>
    #include "Commands.h"
    #include "RadioController.h"
    #include "SerialInterface.h"
    #include "Utility.h"


/*-------------------------------------------------------------------------*\
|                                 Definitions                               |
\*-------------------------------------------------------------------------*/


    #define READ_SERIAL_PERIOD      1
    #define READ_RADIO_PERIOD       100
    

/*-------------------------------------------------------------------------*\
|                                  Variables                                |
\*-------------------------------------------------------------------------*/


    // Task timing
    uint32_t lastReadSerialTime = 0;
    uint32_t lastReadRadioTime = 0;


/*-------------------------------------------------------------------------*\
|                             Function prototypes                           |
\*-------------------------------------------------------------------------*/


    // Tasks
    void readSerial();
    void readRadio();
    void handleSerialPacket(uint8_t* buf);


/*-------------------------------------------------------------------------*\
|                                    Setup                                  |
\*-------------------------------------------------------------------------*/


    void setup(){
        // Enable the watchdog on a 4s timeout
        MCUSR=0;
        wdt_enable(WDTO_4S);
        
        // Begin serial communication
        Serial.begin(SERIAL_BAUD);
        while(!Serial);

        enableDebug();

        // Initialize the radio
        initializeRadio();

        Serial.flush();
    }
    

/*-------------------------------------------------------------------------*\
|                                    Main                                   |
\*-------------------------------------------------------------------------*/


    void loop(){
        /* Read serial every 1ms */
        readSerial();
        
        /* Read LoRa radio every 100ms */
        readRadio();

        /* Give the watchdog a kick */
        wdt_reset();
    }

    
/*-------------------------------------------------------------------------*\
|                                  Functions                                |
\*-------------------------------------------------------------------------*/


    /* ----------------------------- Tasks ----------------------------- */
    void readSerial(){
        if((lastReadSerialTime - millis()) > READ_SERIAL_PERIOD){
            lastReadSerialTime = millis();
            /* Update task interval */

            /* Attempt to read new serial data */
            int16_t res = readSerialData();
            if(res == PACKET_COMPLETE){
                uint8_t* pBuf = getSerialReadBuffer();
                uint16_t bufLen = getSerialReadBufferLength();
                
                Log(F("Complete packet received. Length:"));
                Log(bufLen);

                // Handle the packet
                handleSerialPacket(pBuf, bufLen);
            }
            else if(res != NO_NEW_SERIAL_DATA){
                // Generally this is the parial message
                //Log(F("Info"), res);
            }
        }
    }

    void readRadio(){
        if((lastReadRadioTime - millis()) > READ_RADIO_PERIOD){
            lastReadRadioTime = millis();
            /* Update task interval */

            /* Attempt to read new radio data */
            int16_t res = readRadioData();
            if(res != NO_NEW_RADIO_DATA){ //NEW_RADIO_DATA_BUFFERED
                // Get the radio data
                uint8_t* pBuf = getRadioData();
                uint16_t bufLen = getRadioDataLength();

                Serial.printf(F("Radio data received. Data length: %u\r\n"), bufLen);
                Serial.print(F("Message: "));
                Serial.println((const char*)pBuf);

                // Format into serial packet and send it
                // Insert res, RSSI, and SNR via function call to create a message packet
                float RSSI = getMessageRSSI();
                float SNR = getMessageSNR();
                createMessagePacket(res, RSSI, SNR, pBuf, bufLen+10);               
            }
        }
    }

    /* ----------------------- Helper functions ------------------------ */
    void handleSerialPacket(uint8_t* buf, uint16_t bufLen){
        // Print out the cyclic ID
        Serial.print(F("Packet ID: ")); Serial.println(buf[TYPE_CYCLIC_FIELD_INDEX] & 0b00011111);

        // Print out packet length
        Serial.print(F("Length: ")); Serial.println(bufLen);

        // Print out UNIX time
        Serial.print(F("UNIX: ")); Serial.println(extract_uint32_t(buf, 4));
        
        switch(buf[TYPE_CYCLIC_FIELD_INDEX] & 0b11100000){
            /*case STATUS_PACKET:
                {
                    Log(F("Received status packet"));

                    char floatBuf[10];
                    Serial.print(F("\tLoRa set: ")); Serial.println((uint8_t)buf[8]);
                    Serial.print(F("\tUNIX set: ")); Serial.println((uint8_t)buf[9]);
                    Serial.print(F("\tUptime: ")); Serial.println(extract_uint32_t(buf, 10));                          
                    dtostrf(extract_float(buf, 14), 5, 3, floatBuf);
                    Serial.print(F("\tTemperature: ")); Serial.println(floatBuf);
                    Serial.print(F("\tTOA: ")); Serial.println(extract_uint32_t(buf, (uint16_t)18));
                }
                break;*/
            case ACK_PACKET:
                {
                    Log(F("Received Ack packet"), (uint8_t)buf[8]);
                }
                break;
            case COMMAND_PACKET:
                {
                    Log(F("Received command packet"));

                    // Execute the command
                    int16_t res = executeCommand(buf+PKT_HEADER_LEN, bufLen - PKT_HEADER_TRAILER_LEN, buf);
                    Log("Command executed", res);

                    // Create and send the Ack packet
                    uint16_t retBufLen = getReturnBufferLength();
                    uint8_t* sendBuf = createAckPacket(res, buf, retBufLen+2);
                    uint16_t sendBufferLength = getSendBufferLen();
                    Serial.write((char*)sendBuf, sendBufferLength);
                }
                break;
            case MESSAGE_PACKET:
                {
                    Log(F("Received message packet"));
                    
                    char floatBuf[10];
                    dtostrf(extract_float(buf, 8), 5, 3, floatBuf);
                    Serial.print(F("\tRSSI: ")); Serial.println(floatBuf);
                    dtostrf(extract_float(buf, 12), 5, 3, floatBuf);
                    Serial.print(F("\tSNR: ")); Serial.println(floatBuf);
                    Serial.print(F("\tResult ID: ")); Serial.println(extract_uint16_t(buf, 16), HEX);
					
					// Extract the data (just copy it to the start of the same buffer), then send it over the radio
                    int16_t res = transmitRadio(buf+MESSAGE_INDEX, bufLen-MESSAGE_INDEX-PKT_TRAILER_LEN);
                }
                break;
            default:
                Serial.println(F("Received unknown packet type"));    
        }
    }
