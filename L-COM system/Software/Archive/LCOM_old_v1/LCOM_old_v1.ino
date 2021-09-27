/*
*   Author  :   Stephen Amey
*   Date    :   Aug. 11, 2020
*   Purpose :   This software is used to run the LCOM (LoRa communication) module. It provides both receival and transmission of data, and interfacing with an external device via UART.
*/

//Use setCRC() with 1 or 2 as parameter (# bytes). Set 0 to disable CRC

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
        #define CURRENT_LIMIT                   40.0                    // (max 140 mA)
        // Nyquist formula: bit_rate = 2*BANDWIDTH*log(CODING_RATE)/LOG(2)
    
        /* Serial */
        #define SERIAL_BAUD                     115200
        #define MAX_SERIAL_PAYLOAD_SIZE         (LORA_MAX_PAYLOAD_SIZE + 3)                 //  LoRa + 3 (start/end flags, frame length)
        #define START_FLAG                      0x7E
        #define END_FLAG                        0x7F


/*-------------------------------------------------------------------------*\
|                                  Variables                                |
\*-------------------------------------------------------------------------*/


    /* LoRa */
    SX1262 radio = new Module(NSS, DIO1, NRST, BUSY);

    /* Temperature */
    uint16_t Vth;
    float logR1, Tc;

    /* Communication */
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
        uint8_t res = radio.begin(FREQUENCY, BANDWIDTH, SPREADING_FACTOR, CODING_RATE, SYNC_WORD, OUTPUT_POWER);
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

        /* Enable the receive callback */
        radio.setDio1Action(receiveCallback);

        /* Set RF switch pins */
        radio.setRfSwitchPins(4, 3); // Rx, Tx
        // Tx: Pd3 -> 3
        // Rx: PD4 -> 4

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

        /* If data received on serial */
        if(Serial.available()){
            
            /* Read in the data */
            serIndex = 0;
            while(Serial.available()){
                serialReceiveBuf[serIndex++] = Serial.read();
                delay(1);
            }

            /* Transmit the data */
            Serial.print(F("[SX1262] Transmitting packet: "));
            Serial.println((char*)serialReceiveBuf);
            //memcpy(transmissionBuf, serialReceiveBuf + 2, serIndex - 3);
            //if(radio.transmit(transmissionBuf, serIndex - 3) != ERR_NONE)
            memcpy(transmissionBuf, serialReceiveBuf, serIndex);    // We don't have a frame format yet (don't need it??)
            uint8_t res = radio.transmit(transmissionBuf, serIndex);
            if(res != ERR_NONE){         
                Serial.println("Transmission error occured.");
                Serial.println(res);
            }

            /* Data rate */
            Serial.print(F("[SX1262] Datarate:\t"));
            Serial.print(radio.getDataRate());
            Serial.println(F(" bps"));
        }

        /* Temperature info */
        Serial.print("Temperature: "); 
        Serial.print(getInternalTemperature());
        Serial.println(" C");   
  
        /* Delay */
        delay(1000);         
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
            uint8_t res = radio.readData(receiveBuf, sizeof receiveBuf);
            
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
