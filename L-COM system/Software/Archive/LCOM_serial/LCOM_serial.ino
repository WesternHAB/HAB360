/*
*   Author  :   Stephen Amey
*   Date    :   Aug. 11, 2020
*   Purpose :   This software is used to run the LCOM (LoRa communication) module. It provides both receival and transmission of data, and interfacing with an external device via UART.
*   
*   For some reason, it can receive messaes from itself?
*   I disabled the interrupt during transmission and it seems to work.
*   However this isn't an optimal solution?
*   
*   Need to adjust the data payload size? Seems to max at 72?
*/




// May have to switch back to this for reliability, although a FreeRTOS implementation is nice to do/figure everything out!
// Problem is FreeRTOS uses the watchdog timer which I want for reliability.
// So to use it, can't use FreeRTOS..
// Additionally, might not be able to do a system reset either?






//Use setCRC() with 1 or 2 as parameter (# bytes). Set 0 to disable CRC

/*
 * The new issue:
 * 1st side can send messages repeatedly
 * 2nd side sends a message, it is not received by 1st side
 * 1st side's messages no longer received by second side
 * 
 * Resetting 2nd side lets it receive messages again, until it sends a message
 * 
 * So: Once a side sends a message, it can no longer receive messages.
 *      Is the interrupt line being set, then not reset?
 */


/* 
 *  So the next problem is with reading in serial characters. The serial buffer is 64 bytes, and delaying in the main loop leads to characters being lost.
 *  So, either need to check that buffer very fast until it is done, or do what I did and wait for no more characters + timeout.
 *  
 *  The next step in all this would be utilizing FreeRTOS I think.
 *  Interrupt on serial, check every few ms?
 *  Task then reads it in until done, looking for start/end characters.
 *  
 *  The LoRa interrupt can set a flag, and another task polls on this flag every so often, and services it.
 *  Another, lesser priority task to check the temperature.
 */



 // Use if(lastTime - millis() > TASK_DELAY){...}
 // Implement timed tasks like this to implement a cooperative scheduler
 // This still allows the use of the watchdog as well 


/*-------------------------------------------------------------------------*\
|                                  Includes                                 |
\*-------------------------------------------------------------------------*/


    #include <RadioLib.h>


/*-------------------------------------------------------------------------*\
|                                 Definitions                               |
\*-------------------------------------------------------------------------*/


    //#define RADIOLIB_DEBUG
    //#define RADIOLIB_VERBOSE

    /* Pins------------------------------------------------------------------------*/
        /* LoRa module */
        #define NSS                             10
        #define DIO1                            2
        #define NRST                            9
        #define BUSY                            8
        
        /* Thermistor */
        #define THERMISTOR_PIN                  A0

    /* Temperature-----------------------------------------------------------------*/
        #define READ_TEMP_PERIOD                1000                // 1 second
        #define ANALOG_MAX_VALUE                1023.0
        #define KELVIN_CELCIUS_DIFFERENCE       273.15  
        #define R2_OHM                          10000               // Ohm
        #define C1                              1.009249522e-03
        #define C2                              2.378405444e-04
        #define C3                              2.019202697e-07

    /* Communication---------------------------------------------------------------*/
        /* LoRa */
        #define LORA_MAX_PAYLOAD_SIZE           255
        #define FREQUENCY                       915.0                   // Canadian unlicensed band
        #define BANDWIDTH                       125.0
        #define SPREADING_FACTOR                9
        #define CODING_RATE                     7
        #define SYNC_WORD                       0x12                    // (private network)
        #define OUTPUT_POWER                    14                      // (max 22 dBm)
        #define CURRENT_LIMIT                   60.0                    // (max 140 mA)
        #define PREAMBLE_LENGTH                 8
        // Nyquist formula: bit_rate = 2*BANDWIDTH*log(CODING_RATE)/LOG(2)
    
        /* Serial */
        #define SERIAL_BAUD                     115200
        #define MAX_SERIAL_PAYLOAD_SIZE         (LORA_MAX_PAYLOAD_SIZE + 3)                 //  LoRa + 3 (start/end flags, frame length)
        //#define START_FLAG                      0x7E
        //#define END_FLAG                        0x7F
        #define SERIAL_READ_TIMEOUT 10


/*-------------------------------------------------------------------------*\
|                                  Variables                                |
\*-------------------------------------------------------------------------*/


    /* LoRa */
    SX1262 radio = new Module(NSS, DIO1, NRST, BUSY);
    volatile bool enableReceiveInterrupt = true;
    volatile bool receivedFlag = false;

    /* Temperature */
    uint16_t Vth;
    float logR1, Tc;
    uint32_t lastReadTime = 0;

    /* Communication */
    uint32_t serialReadStartTime = 0;
    uint8_t serialReceiveBuf[MAX_SERIAL_PAYLOAD_SIZE];  // For receiving serial messages to transmit
    uint8_t serIndex = 0;

    uint8_t transmissionBuf[LORA_MAX_PAYLOAD_SIZE];     // Holds the data to transmit
    uint8_t receiveBuf[LORA_MAX_PAYLOAD_SIZE];          // Holds received transmissions


/*-------------------------------------------------------------------------*\
|                             Function prototypes                           |
\*-------------------------------------------------------------------------*/


    void receiveCallback(void);
    float getInternalTemperature(void);


/*-------------------------------------------------------------------------*\
|                                    Setup                                  |
\*-------------------------------------------------------------------------*/


    void setup() {
        /* Begin serial communication */
        Serial.begin(SERIAL_BAUD);
    
        /* LoRa initialization */
        Serial.print(F("[SX1262] Initializing ... "));
        int16_t res = radio.begin(FREQUENCY, BANDWIDTH, SPREADING_FACTOR, CODING_RATE, SYNC_WORD, OUTPUT_POWER, PREAMBLE_LENGTH);
        if(res != ERR_NONE) {
            Serial.print(F("failed, code "));
            Serial.println(res);
            while (true);
            // Try again code here, reset?
        }
        Serial.println("Success!");

        /* Set the current limit */
        Serial.print(F("[SX1262] Setting current limit ... "));
        res = radio.setCurrentLimit(CURRENT_LIMIT);
        if (res != ERR_NONE) {
            Serial.print(F("failed, code "));
            Serial.println(res);
            while (true);
            // Try again code here, reset?
        }
        Serial.println(F("success!"));

        /* Set RF switch pins */
        radio.setRfSwitchPins(7, 6); // Rx, Tx
        // Tx: PD3 -> 6
        // Rx: PD4 -> 7

        /* Enable the receive callback */
        radio.setDio1Action(receiveCallback);

        /* Start listening in interrupt mode */
        res = radio.startReceive();
        if (res != ERR_NONE) {
            Serial.print(F("failed, code "));
            Serial.println(res);
            while (true);
            // Try again code here, reset?
        }
        Serial.println(F("success!"));
    }


/*-------------------------------------------------------------------------*\
|                                    Main                                   |
\*-------------------------------------------------------------------------*/


    void loop() {
        /* If LoRa data received */
        if(receivedFlag){

            /* Disable the interrupt and reset the flag before processing data */
            enableReceiveInterrupt = false;
            receivedFlag = false;

            /* Empty the buffer */
            for(uint8_t i = 0; i != (sizeof receiveBuf); i++){
                receiveBuf[i] = 0;
            }
            
            int16_t res = radio.readData(receiveBuf, sizeof receiveBuf);           
            if(res == ERR_NONE){
                // packet was successfully received
                Serial.println(F("[SX1262] Received packet!"));
        
                // print data of the packet
                Serial.print(F("[SX1262] Data:\t\t"));
                Serial.println((char*)receiveBuf);
        
                // print RSSI (Received Signal Strength Indicator)
                Serial.print(F("[SX1262] RSSI:\t\t"));
                Serial.print(radio.getRSSI());
                Serial.println(F(" dBm"));
        
                // print SNR (Signal-to-Noise Ratio)
                Serial.print(F("[SX1262] SNR:\t\t"));
                Serial.print(radio.getSNR());
                Serial.println(F(" dB"));      
            }
            else if(res == ERR_CRC_MISMATCH){
                // packet was received, but is malformed
                Serial.println(F("CRC error!"));    
            }
            else{
                // some other error occurred
                Serial.print(F("failed, code "));
                Serial.println(res);      
            }
            
            /* Start listening in interrupt mode */
            radio.startReceive();

            /* Reenable the interrupt */
            enableReceiveInterrupt = true;
        }

        /* If data received on serial */
        if(Serial.available()){
            
            /* Read in the data */
            serIndex = 0;
            while(1){
                // Read characters until no more appear for 10ms
                if(Serial.available()){
                    serialReadStartTime = millis();
                    serialReceiveBuf[serIndex++] = Serial.read();
                    if(serIndex == LORA_MAX_PAYLOAD_SIZE) break;
                }
                else if((millis() - serialReadStartTime) > SERIAL_READ_TIMEOUT){
                    break;
                }
            }
            serialReceiveBuf[serIndex] = 0;

            /* Prepare the data for transmission */
            memcpy(transmissionBuf, serialReceiveBuf, serIndex);    // We don't have a frame format yet (don't need it??)
            transmissionBuf[serIndex] = 0;
            Serial.print(F("[SX1262] Transmitting packet: "));
            Serial.println((char*)transmissionBuf);

            Serial.println("Size data:");
            Serial.println(sizeof serialReceiveBuf);
            Serial.println(sizeof transmissionBuf);
            
            
            /* Disable the interrupt */
            enableReceiveInterrupt = false;

            /* Transmit the data */
            int16_t res = radio.transmit(transmissionBuf, serIndex);
            if(res != ERR_NONE){         
                Serial.println("Transmission error occured.");
                Serial.println(res);
            }

            /* Enable the interrupt */
            enableReceiveInterrupt = true;
            receivedFlag = false;

            /* Start listening in interrupt mode */
            radio.startReceive();

            /* Data rate */
            Serial.print(F("[SX1262] Datarate:\t"));
            Serial.print(radio.getDataRate());
            Serial.println(F(" bps"));
        }

        /* Temperature info */
        if((millis() - lastReadTime) > READ_TEMP_PERIOD){
            lastReadTime = millis();
            Serial.print("Temperature: "); 
            Serial.print(getInternalTemperature());
            Serial.println(" C");   
        }
  
        /* Delay */
        delay(1);         
    }


/*-------------------------------------------------------------------------*\
|                                  Functions                                |
\*-------------------------------------------------------------------------*/


    /*-------------------------------------------------------------------------------------*\
    |   Name:       receiveCallback                                                         |
    |   Purpose:    Handles the interrupt from the LoRa module.                             |
    |   Arguments:  void                                                                    |
    |   Returns:    void                                                                    |
    \*-------------------------------------------------------------------------------------*/
        void receiveCallback(void){
            if(!enableReceiveInterrupt) {
                return;
            }
            
            // We got a packet, set the flag
            receivedFlag = true;    
        }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getInternalTemperature                                                  |
    |   Purpose:    Finds the temperature of the internal thermistor.                       |
    |   Arguments:  Void                                                                    |
    |   Returns:    float (temperature)                                                     |
    \*-------------------------------------------------------------------------------------*/
        float getInternalTemperature(void){
            Vth = analogRead(THERMISTOR_PIN);
            logR1 = log(R2_OHM * (ANALOG_MAX_VALUE / (float)Vth - 1.0));
            Tc = (1.0 / (C1 + C2*logR1 + C3*logR1*logR1*logR1)) - KELVIN_CELCIUS_DIFFERENCE;
            return Tc;
        }
