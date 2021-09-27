/*
*   Author  :   Stephen Amey
*   Date    :   June 5, 2020
*   Purpose :   This software is used to run the LCOM (LoRa communication) module, using FreeRTOS. It provides both receival and transmission of data, and interfacing with an external device via UART.
*/

// Always use F() for string!
// Never use printf, it eats up memory! (sprintf if really needed)

/*-------------------------------------------------------------------------*\
|                                  Includes                                 |
\*-------------------------------------------------------------------------*/

   
    #include <RadioLib.h>
    #include "Commands.h"
    #include "LCOM_utility.h"

    /* Definitions */
    #include "FreeRTOS_definitions.h"
    #include "LCOM_definitions.h"
    #include "Serial_definitions.h"   
    #include "Status_codes.h"   
    
    /* FreeRTOS */
    #include <Arduino_FreeRTOS.h>  


/*-------------------------------------------------------------------------*\
|                                  Variables                                |
\*-------------------------------------------------------------------------*/


    /* FreeRTOS*/
        // Task handles
        TaskHandle_t TaskSerial_Handler;
        TaskHandle_t TaskCommands_Handler;

    /* Buffers */ // Having separate buffers uses more memory but allows more relaxed timing requirements (and better readability in general)
    uint8_t receiveSerialBuffer[PKT_MAX_LEN];                   // Holds received serial data 
    uint8_t sendSerialBuffer[PKT_MAX_LEN];                      // Holds serial data to send
    uint8_t receiveLoRaBuffer[LORA_MAX_PAYLOAD_SIZE];           // Holds received LoRa data (can combine receiveSerial/sendLoRa and receiveLoRa/sendSerial buffers?)
    uint8_t sendLoRaBuffer[LORA_MAX_PAYLOAD_SIZE];              // Holds LoRa data to send  
    uint8_t commandBuffer[PKT_MAX_DATA_PAYLOAD_LEN+1];          // Holds command data (+1 for null terminator) (might be better to just use the receiveSerialBuffer?
    uint8_t commandBufferLength = 0;

    // Point to return data when making Ack packets
    uint8_t *pRetData = NULL;
    uint16_t retDataLen = 0;


/*-------------------------------------------------------------------------*\
|                             Function prototypes                           |
\*-------------------------------------------------------------------------*/


    /* FreeRTOS tasks */
        void TaskSerial     (void* pvParameters);
        void TaskCommands   (void* pvParameters);
       

    /* Functions */
        boolean verifyPacket(uint8_t *buf);
        uint32_t extract_uint32_t(uint8_t *buf, uint64_t pos);
        uint16_t extract_uint16_t(uint8_t *buf, uint64_t pos);
        float extract_float(uint8_t *buf, uint64_t pos);


/*-------------------------------------------------------------------------*\
|                                    Setup                                  |
\*-------------------------------------------------------------------------*/


    void setup() {

        /* Serial debug */
        Serial.begin(SERIAL_BAUD);
        while(!Serial);

            // Serial handling
            if(!xTaskCreate(
                TaskSerial
                ,  "Serial"
                ,  SERIAL_TASK_STACK_SIZE       // Stack size
                ,  NULL                         // Parameters passed to the task function
                ,  1                            // Priority
                ,  &TaskSerial_Handler )       // Task handle
            ) Serial.println(F("Serial task failed to create!"));

            // Command execution handling
            if(!xTaskCreate(
                TaskCommands
                ,  "Commands"
                ,  COMMANDS_TASK_STACK_SIZE     // Stack size
                ,  NULL                         // Parameters passed to the task function
                ,  2                            // Priority
                ,  &TaskCommands_Handler )     // Task handle
            ) Serial.println(F("Command task failed to create!"));
    }

    // Unused loop
    void loop(){}


/*-------------------------------------------------------------------------*\
|                                    Tasks                                  |
\*-------------------------------------------------------------------------*/


    /*-------------------------------------------------------------------------------------*\
    |   Name:       TaskSerial                                                              |
    |   Purpose:    Handles any data received on the serial interface. Adds the data to     |
    |               a buffer, then either transmits it or executes it as a command.         |
    \*-------------------------------------------------------------------------------------*/
    void TaskSerial(void* pvParameters){
        (void) pvParameters;

        /* Variables */
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        boolean startFlagFound = false;
        uint8_t newSerialByte = 0;
        uint8_t rIdx = 0;
        //uint8_t receiveSerialBuffer[PKT_MAX_LEN];      // Holds the incoming serial data
        uint8_t packetLen = 0;
        int16_t res = CMD_OK;

        /* Begin serial communication */
        //Serial.begin(SERIAL_BAUD);
        //while(!Serial);
        //Serial.flush();
        
        Serial.println("SERIAL TASK STARTED");

         /* Begin task looping */
        for (;;){
            
            // Wait for serial data to become available
            if(Serial.available()){

                // Read in the next character
                newSerialByte = Serial.read();

                // If the start of a new packet was found, set the flag and prepare the buffer
                if(!startFlagFound && newSerialByte == START_FLAG){
                    Serial.println(F("\r\n"));
                    startFlagFound = true;
                    rIdx = 0;
                    packetLen = 0;
                    for(uint16_t i = 0; i != PKT_MAX_LEN; i++) receiveSerialBuffer[i] = 0; 
                }

                // If the start flag was found
                if(startFlagFound){
                    // Record the length of the packet
                    if(rIdx == LENGTH_INDEX) packetLen = (uint8_t)newSerialByte;
                    
                    // Add the byte to the buffer
                    receiveSerialBuffer[rIdx++] = newSerialByte;
                
                    // If the end flag was found, verify and process the packet
                    if(rIdx == packetLen){

                        // If the packet is valid, handle it
                        if(verifyPacket(receiveSerialBuffer)){

                            // Print out the cyclic ID
                            Serial.print(F("Packet ID: ")); Serial.println((uint8_t)(receiveSerialBuffer[TYPE_CYCLIC_FIELD_INDEX] & 0b00011111));

                            // Print out packet length
                            Serial.print(F("Length: ")); Serial.println((uint8_t)receiveSerialBuffer[LENGTH_INDEX]);

                            // Print out UNIX time
                            Serial.print(F("UNIX: ")); Serial.println(extract_uint32_t(receiveSerialBuffer, (uint16_t)3));

                            // Check the type of packet and handle it
                            char floatBuf[10]; // Remove this later
                            switch(receiveSerialBuffer[TYPE_CYCLIC_FIELD_INDEX] & 0b11100000){
                                case STATUS_PACKET:
                                    {
                                        Serial.println(F("Received status packet!"));
                                        Serial.print(F("\tLoRa set: ")); Serial.println((uint8_t)receiveSerialBuffer[7]);
                                        Serial.print(F("\tUNIX set: ")); Serial.println((uint8_t)receiveSerialBuffer[8]);
                                        Serial.print(F("\tUptime: ")); Serial.println(extract_uint32_t(receiveSerialBuffer, (uint16_t)9));                          
                                        dtostrf(extract_float(receiveSerialBuffer, (uint16_t)13), 5, 3, floatBuf);
                                        Serial.print(F("\tTemperature: ")); Serial.println(floatBuf);
                                        Serial.print(F("\tTOA: ")); Serial.println(extract_uint32_t(receiveSerialBuffer, (uint16_t)17));
                                    }
                                    break;
                                case COMMAND_PACKET:
                                    {
                                        Serial.println(F("Received command packet!"));
                                        Serial.print(F("\tCommand ID: ")); Serial.println((uint8_t)receiveSerialBuffer[7]);
    
                                        // Copy the command data to the buffer
                                        memcpy(commandBuffer, receiveSerialBuffer+PKT_HEADER_LEN, sizeof(commandBuffer));
                                        commandBuffer[packetLen] = 0; // Zero out the copied end flag
                                        commandBufferLength = packetLen;
    
                                        // Notify and yield to the command task
                                        vTaskNotifyGiveFromISR(TaskCommands_Handler, &xHigherPriorityTaskWoken);
                                        if (xHigherPriorityTaskWoken) taskYIELD();
                                    }
                                    break;
                                case ACK_PACKET:
                                    {
                                        Serial.println(F("Received ACK packet!"));
                                        Serial.print(F("\tResult ID: ")); Serial.println(extract_uint16_t(receiveSerialBuffer, (uint16_t)7), HEX);
                                    }
                                    break;
                                case MESSAGE_PACKET:
                                    {
                                        // RSSI, SNR, and Result ID should be zero as this was received from the attached device and is to be sent.
                                        Serial.println(F("Received message packet!"));
                                        dtostrf(extract_float(receiveSerialBuffer, (uint16_t)7), 5, 3, floatBuf);
                                        Serial.print(F("\tRSSI: ")); Serial.println(floatBuf);
                                        dtostrf(extract_float(receiveSerialBuffer, (uint16_t)11), 5, 3, floatBuf);
                                        Serial.print(F("\tSNR: ")); Serial.println(floatBuf);
                                        Serial.print(F("\tResult ID: ")); Serial.println(extract_uint16_t(receiveSerialBuffer, (uint16_t)15), HEX);
    
                                        // Copy the message to the transmission buffer
                                        uint16_t messageLen = packetLen - PKT_HEADER_LEN - PKT_TRAILER_LEN - 10;
                                        memcpy(sendLoRaBuffer, receiveSerialBuffer + PKT_HEADER_LEN + 10, messageLen);
    
                                        // Transmit the message
                                        //res = radio.transmit(transmissionBuf, messageLen); // Don't have the LoRa setup yet
    
                                        // Send Ack on serial
                                        createAckPacket(sendSerialBuffer, (uint16_t)res, NULL, 0);
                                        Serial.write((char*)sendSerialBuffer);
                                    }
                                    break;
                                default:
                                    Serial.println(F("Received unknown packet type!"));    
                            }
                        }

                        // Reset the flag
                        startFlagFound = 0;
                    }
                    // Else if the end flag was not found and the buffer is full, reset the flag
                    else if(rIdx == PKT_MAX_LEN){                   
                        startFlagFound = 0;
                    }  
                }

                // Delay for the task period
                vTaskDelay(SERIAL_TASK_PERIOD / portTICK_PERIOD_MS);
            }
        }
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       TaskCommands                                                            |
    |   Purpose:    Handles any commands received from TaskSerial via the commandQueue.     |
    \*-------------------------------------------------------------------------------------*/
    void TaskCommands(void* pvParameters){
        (void) pvParameters;
        uint16_t res = CMD_OK;

        /* Begin task looping */
        for (;;){
            
            // Wait until a command is received
            if (ulTaskNotifyTake(pdTRUE, portMAX_DELAY)) {

                // Print command data
                Serial.print(F("Received command: "));
                Serial.println(commandBuffer[0], HEX);

                // Reset the return data pointer and return data length
                pRetData = NULL;
                retDataLen = 0;

                // Execute the associated command
                switch(commandBuffer[0]){
                    case SET_LORA_PARAMETERS:
                        res = setLoRaParameters(commandBuffer, commandBufferLength);
                        break;
                    case GET_LORA_PARAMETERS:
                        res = getLoRaParameters(commandBuffer, &retDataLen);
                        pRetData = commandBuffer;
                        break;
                    case SYSTEM_RESET:
                        break;
                    default:
                        Serial.println(F("Unknown command."));
                }

                // Send an ACK packet back containing the result
                // -> Get... commands can fill a buffer. This buffer is then passed into a createAckPacket function.
                // The function puts data into another passed buffer, and this can then be transmitted
                // e.g. createAckPacket(returnAckBuf, cmdResBuf);
                // Serial.write(returnAckBuf);
                // -> We can even just write data back into the commandBuffer possibly to make it use less data.

                // Create and send an Ack packet with any return data
                createAckPacket(sendSerialBuffer, res, pRetData, retDataLen);
                Serial.write((char*)sendSerialBuffer);
            }
        }
    }


/*-------------------------------------------------------------------------*\
|                                  Functions                                |
\*-------------------------------------------------------------------------*/


    /*-------------------------------------------------------------------------------------*\
    |   Name:       vApplicationStackOverflowHook                                           |
    |   Purpose:    Handles stack overflow of tasks                                         |
    \*-------------------------------------------------------------------------------------*/
    void vApplicationStackOverflowHook(TaskHandle_t xTask, char* pcTaskName){
        while (true){
            Serial.println(F("Stack overflow"));
            delay(1000);
        }
    }


//Watchdog reset code
/*
WDTCR=0x18;
WDTCR=0x08;
#asm("wdr")
while(1);
*/
// Need to occaisionally trigger the watchdog with:
// wdt_reset();
// This prevents it from resetting. Not doing this will cause a reset.


/*
 * Biggest payload message we can receive on serial is 237 bytes
Thus while LoRa can transmit 255 bytes, part of that is our header, and thus actual text payload is less (depends on packet type)
 */
