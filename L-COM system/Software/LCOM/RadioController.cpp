/*
*   Author  :   Stephen Amey
*   Date    :   Aug. 28, 2021
*/


#include "RadioController.h"


/*-------------------------------------------------------------------------*\
|								   Variables					   			|
\*-------------------------------------------------------------------------*/


    SX1262 radio = NULL;
    volatile bool enableReceiveInterrupt = true;
    volatile bool receivedFlag = false;
    uint8_t radioReadBuffer[MAX_LORA_MESSAGE_SIZE];
    bool LoRaSet = false;

    /* Radio parameters */
    float frequency         = DEFAULT_FREQUENCY;
    float bandwidth         = DEFAULT_BANDWIDTH;  
    uint8_t spreadingFactor = DEFAULT_SPREADING_FACTOR;
    uint8_t codingRate      = DEFAULT_CODING_RATE;
    uint8_t syncWord        = DEFAULT_SYNC_WORD;
    int8_t power            = DEFAULT_OUTPUT_POWER;
    uint16_t preambleLength = DEFAULT_PREAMBLE_LENGTH;
    float currentLimit      = DEFAULT_CURRENT_LIMIT;


/*-------------------------------------------------------------------------*\
|								   Functions					   			|
\*-------------------------------------------------------------------------*/


    /*-------------------------------------------------------------------------------------*\
    |   Name:       initializeRadio                                                         |
    |   Purpose:    Initializes the LoRa radio pins, current limit, and starts listening.   |
    |   Arguments:  void                                                                    |
    |   Returns:    void                                                                    |
    \*-------------------------------------------------------------------------------------*/
    int16_t initializeRadio(void){
        /* Create the radio object */
        radio = new Module(NSS, DIO1, NRST, BUSY);

        //radio.reset();
    
        /* LoRa initialization */
        Log(F("[SX1262] Initializing radio..."));
        int16_t res = radio.begin(frequency, bandwidth, spreadingFactor, codingRate, syncWord, power, preambleLength);
        if(res != ERR_NONE) {
            Log(F("Initialization failed"), res);     
            return res;
        }
        Log(F("Radio initialization success"));
    
        /* Set the current limit */
        Log(F("[SX1262] Setting current limit..."));
        res = radio.setCurrentLimit(DEFAULT_CURRENT_LIMIT);
        if (res != ERR_NONE) {
            Log(F("Current limit set failed"), res);     
            return res;
        }
        Log(F("Current limit set success"));
    
        /* Set RF switch pins */
        radio.setRfSwitchPins(RX, TX);
    
        /* Enable the receive callback */
        radio.setDio1Action(receiveCallback);
    
        /* Start listening in interrupt mode */
        Log(F("[SX1262] Starting to listen in interrupt mode..."));
        res = radio.startReceive();
        if (res != ERR_NONE) {
            Log(F("Listening start failed"), res);     
            return res;
        }
        Log(F("Listening start success"));
        
        /* Return the result */
        return ERR_NONE;
    }

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
        
        /* Set the received flag */
        receivedFlag = true;    
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       readRadioData                                                           |
    |   Purpose:    Reads back data from the radio into a buffer.                           |
    |   Arguments:  void                                                                    |
    |   Returns:    int16_t                                                                 |
    \*-------------------------------------------------------------------------------------*/
    int16_t readRadioData(void){
        /* If LoRa data received */
        if(receivedFlag){

            /* Disable the interrupt and reset the flag before processing data */
            enableReceiveInterrupt = false;
            receivedFlag = false;

            /* Empty the buffer */
            for(uint16_t i = 0; i != (sizeof radioReadBuffer); i++){
                radioReadBuffer[i] = 0;
            }

            // Read the data
            int16_t res = radio.readData(radioReadBuffer, sizeof radioReadBuffer);                 
            Log(F("[SX1262] Received packet"), res);
            if(res == ERR_NONE){
                // Print data
                Log(F("[SX1262] Data:"));
                Log((char*)radioReadBuffer);
            }
        
            // Print RSSI (Received Signal Strength Indicator)
            Log(F("[SX1262] RSSI (dBm):"));
            Log(radio.getRSSI());
    
            // Print SNR (Signal-to-Noise Ratio)
            Log(F("[SX1262] SNR (dB):"));
            Log(radio.getSNR());    
            
            /* Start listening in interrupt mode */
            radio.startReceive();

            /* Reenable the interrupt */
            enableReceiveInterrupt = true;

            /* Return the result */
            return res;
        }
        else{
            return NO_NEW_RADIO_DATA;
        }
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getRadioData                                                            |
    |   Purpose:    Returns a pointer to the radio data buffer.                             |
    |   Arguments:  uint8_t*                                                                |
    |   Returns:    uint8_t*                                                                |
    \*-------------------------------------------------------------------------------------*/
    uint8_t* getRadioData(void){
        return radioReadBuffer;
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getRadioDataLength                                                      |
    |   Purpose:    Returns the data length in bytes of the last received radio data.       |
    |   Arguments:  void                                                                    |
    |   Returns:    uint16_t                                                                |
    \*-------------------------------------------------------------------------------------*/
    uint16_t getRadioDataLength(void){
        return radio.getPacketLength();
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       transmitRadio                                                           |
    |   Purpose:    Transmits the data in the buffer over the radio.                        |
    |   Arguments:  uint8_t*, uint16_t                                                      |
    |   Returns:    int16_t                                                                 |
    \*-------------------------------------------------------------------------------------*/
    int16_t transmitRadio(uint8_t* buf, uint16_t len){
        /* Disable the interrupt */
        enableReceiveInterrupt = false;

        Serial.print("Transmitting data: \"");
        Serial.write((char*)buf, len);
        Serial.println("\"");

        /* Transmit the data */
        int16_t res = radio.transmit(buf, len);
        Log("Transmission finished", res);

        /* Enable the interrupt */
        enableReceiveInterrupt = true;
        receivedFlag = false;

        /* Start listening in interrupt mode */
        radio.startReceive();    

        /* Return */
        return res;
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       setRadioParameters                                                      |
    |   Purpose:    Sets the radio parameters.                                              |
    |   Arguments:  void                                                                    |
    |   Returns:    int16_t                                                                 |
    \*-------------------------------------------------------------------------------------*/
    int16_t setRadioParameters(
        float _frequency, float _bandwidth, uint8_t _spreadingFactor, uint8_t _codingRate,
        uint8_t _syncWord, int8_t _power, uint16_t _preambleLength, float _currentLimit
    ){
        int16_t res;
        if((res = radio.setFrequency(_frequency))                != ERR_NONE) return res;
            frequency = _frequency;
        if((res = radio.setBandwidth(_bandwidth))                != ERR_NONE) return res;
            bandwidth = _bandwidth;
        if((res = radio.setSpreadingFactor(_spreadingFactor))    != ERR_NONE) return res;
            spreadingFactor = _spreadingFactor;
        if((res = radio.setCodingRate(_codingRate))              != ERR_NONE) return res;
            codingRate = _codingRate;
        if((res = radio.setSyncWord(_syncWord))                  != ERR_NONE) return res;
            syncWord = _syncWord;
        if((res = radio.setOutputPower(_power))                  != ERR_NONE) return res;
            power = _power;
        if((res = radio.setPreambleLength(_preambleLength))      != ERR_NONE) return res;
            preambleLength = _preambleLength;
        if((res = radio.setCurrentLimit(_currentLimit))          != ERR_NONE) return res;
            currentLimit = _currentLimit;
        return res;
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getLoRaSet                                                              |
    |   Purpose:    Returns whether LoRa parameters have been changed from the default.     |
    |   Returns:    bool                                                                    |
    \*-------------------------------------------------------------------------------------*/
    bool getLoRaSet(void){
        return LoRaSet;
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       radioReset                                                              |
    |   Purpose:    Resets the radio.                                                       |
    |   Returns:    int16_t                                                                 |
    \*-------------------------------------------------------------------------------------*/
    int16_t resetRadio(void){
        radio.reset();
        //delete radio;
        return initializeRadio();
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getFrequency                                                            |
    |   Purpose:    Returns the current frequency of the radio.                             |
    |   Returns:    float                                                                   |
    \*-------------------------------------------------------------------------------------*/
    float getFrequency(void){
        return frequency;
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getBandwidth                                                            |
    |   Purpose:    Returns the current bandwidth of the radio.                             |
    |   Returns:    float                                                                   |
    \*-------------------------------------------------------------------------------------*/
    float getBandwidth(void){
        return bandwidth;
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getSpreadingFactor                                                      |
    |   Purpose:    Returns the current spreading factor of the radio.                      |
    |   Returns:    uint8_t                                                                 |
    \*-------------------------------------------------------------------------------------*/
    uint8_t getSpreadingFactor(void){
        return spreadingFactor;
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getCodingRate                                                           |
    |   Purpose:    Returns the current coding rate of the radio.                           |
    |   Returns:    uint8_t                                                                 |
    \*-------------------------------------------------------------------------------------*/
    uint8_t getCodingRate(void){
        return codingRate;
    }    

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getSyncWord                                                             |
    |   Purpose:    Returns the current sync word of the radio.                             |
    |   Returns:    uint8_t                                                                 |
    \*-------------------------------------------------------------------------------------*/
    uint8_t getSyncWord(void){
        return syncWord;
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getPower                                                                |
    |   Purpose:    Returns the current power of the radio.                                 |
    |   Returns:    uint8_t                                                                 |
    \*-------------------------------------------------------------------------------------*/
    uint8_t getPower(void){
        return power;
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getPreambleLength                                                       |
    |   Purpose:    Returns the current preamble length of the radio.                       |
    |   Returns:    uint16_t                                                                |
    \*-------------------------------------------------------------------------------------*/
    uint16_t getPreambleLength(void){
        return preambleLength;
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getCurrentLim                                                           |
    |   Purpose:    Returns the current current limit of the radio.                         |
    |   Returns:    float                                                                   |
    \*-------------------------------------------------------------------------------------*/
    float getCurrentLim(void){
        return currentLimit;
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getTOA                                                                  |
    |   Purpose:    Returns the estimated time on air for the current LoRa parameters.      |
    |   Returns:    uint32_t                                                                |
    \*-------------------------------------------------------------------------------------*/
    uint32_t getTOA(void){
        //return radio.getTimeOnAir(); // Missing from the current library?
        return 0;
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getLoRaDataRate                                                         |
    |   Purpose:    Returns the data rate of the last packet transmitted.                   |
    |   Returns:    float                                                                   |
    \*-------------------------------------------------------------------------------------*/
    float getLoRaDataRate(void){
        return radio.getDataRate();
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getMessageRSSI                                                          |
    |   Purpose:    Returns the RSSI of the last packet transmitted.                        |
    |   Returns:    float                                                                   |
    \*-------------------------------------------------------------------------------------*/
    float getMessageRSSI(void){
        return radio.getRSSI();
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getMessageSNR                                                           |
    |   Purpose:    Returns the SNR of the last packet transmitted.                         |
    |   Returns:    float                                                                   |
    \*-------------------------------------------------------------------------------------*/
    float getMessageSNR(void){
        return radio.getSNR();        
    }
