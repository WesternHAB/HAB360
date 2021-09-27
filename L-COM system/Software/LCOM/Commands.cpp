/*
*   Author  :   Stephen Amey
*   Date    :   Aug. 29, 2021
*/


#include "Commands.h"


/*-------------------------------------------------------------------------*\
|								   Variables					   			|
\*-------------------------------------------------------------------------*/


    //uint8_t retBuffer[MAX_COMMAND_LEN];
    uint16_t retBufferLen;


/*-------------------------------------------------------------------------*\
|								   Functions					   			|
\*-------------------------------------------------------------------------*/


    /*-------------------------------------------------------------------------------------*\
    |   Name:       getRetBuffer                                                         |
    |   Purpose:    Returns a pointer to the command buffer.                                |
    |   Arguments:  void                                                                    |
    |   Returns:    uint8_t*                                                                |
    \*-------------------------------------------------------------------------------------*/
    /*uint8_t* getRetBuffer(void){
        return retBuffer;
    }*/

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getretBufferLength                                                   |
    |   Purpose:    Returns the data length in bytes of returned data in the command buffer.|
    |   Arguments:  void                                                                    |
    |   Returns:    uint16_t                                                                |
    \*-------------------------------------------------------------------------------------*/
    uint16_t getReturnBufferLength(void){
        return retBufferLen;
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       executeCommand                                                          |
    |   Purpose:    Executes the passed command.                                            |
    |   Arguments:  void                                                                    |
    |   Returns:    int16_t                                                                 |
    \*-------------------------------------------------------------------------------------*/
    int16_t executeCommand(const uint8_t* buf, uint16_t len, uint8_t* retBuf){ // This whole function may go better in the LCOM file
        
        // Print command data
        Serial.printf(F("Received command: %02X\r\n"), buf[CMD_INDEX]);

        /* Clear the return buffer */
        //for(uint16_t i = 0; i != sizeof(retBuffer); i++) retBuf[i] = 0;

        /* Reset the return data length */
        retBufferLen = 0;

        /* Execute the associated command */
        int16_t res = CMD_OK;
        switch(buf[CMD_INDEX]){
            case SET_LORA_PARAMETERS:
                res = setLoRaParameters(buf, len);
                break;
            case SET_UNIX:
                res = setUnix(buf, len);
                break;
            case SET_MODE_MESSAGE:
                res = setModeMessage(buf, len);
                break;
            case GET_LORA_PARAMETERS:
                res = getLoRaParameters(buf, len, retBuf);
                break;
            case GET_UNIX:
                res = getUnix(buf, len, retBuf);
                break;
            case GET_MODE_MESSAGE:
                res = getModeMessage(buf, len, retBuf);
                break;
            case GET_MODULE_STATUS:
                res = getModuleStatus(buf, len, retBuf);
                break;
            case RADIO_RESET:
                res = radioReset(len);
                break;
            case SYSTEM_RESET:
                res = systemReset(len);
                break;
            default:
                res = CMD_UNKNOWN_COMMAND;
                Serial.println(F("Unknown command."));
        }

        return res;
    }

    /* ---------------------------- Setters ---------------------------- */

    /*-------------------------------------------------------------------------------------*\
    |   Name:       setLoRaParameters                                                       |
    |   Purpose:    Set the LoRa parameters used by the EBYTE module.                       |
    |   Arguments:  Via buf, uint16_t                                                       |
    |               Bytes               Field                                               |
    |               -------------------------------------------                             |
    |               0                   Command                                             |
    |               1-4                 Frequency                                           |
    |               5-8                 Bandwidth                                           |
    |               9                   Spreading factor                                    |
    |               10                  Coding rate                                         |
    |               11                  Sync word                                           |
    |               12                  Power                                               |
    |               13-14               Preamble length                                     |
    |               15-18               Current limit                                       |
    |                                                                                       |
    |   Returns:    int16_t (error code)                                                    |
    \*-------------------------------------------------------------------------------------*/
    int16_t setLoRaParameters(const uint8_t* buf, uint16_t len){
        
        /* Check to make sure the payload is of the correct size */
        if(len != SET_LORA_PARAMETERS_PAYLOAD_LEN) return CMD_MALFORMED_PAYLOAD;

        /* Parameters */            
        int8_t power;
        uint8_t spreadingFactor, codingRate, syncWord;
        uint16_t preambleLength;
        float frequency, bandwidth, currentLimit;
        
        /* Get the values from byte string */
        frequency       = extract_float(buf, 1);
        bandwidth       = extract_float(buf, 5);
        spreadingFactor = extract_uint8_t(buf, 9);
        codingRate      = extract_uint8_t(buf, 10);
        syncWord        = extract_uint8_t(buf, 11);
        power           = (int8_t)extract_uint8_t(buf, 12);
        preambleLength  = extract_uint16_t(buf, 13);
        currentLimit    = extract_float(buf, 15);
        
        /* Validation checks on the parameters */
        if(frequency < 150.0 || frequency > 960.0)          return CMD_INVALID_FREQUENCY;
        if(bandwidth < 0.0 || bandwidth > 510.0)            return CMD_INVALID_BANDWIDTH;
        if(spreadingFactor < 5 || spreadingFactor > 12)     return CMD_INVALID_SPREADING_FACTOR;
        if(codingRate < 5 || codingRate > 8)                return CMD_INVALID_CODING_RATE;
        if(syncWord == 0x34)                                return CMD_INVALID_SYNC_WORD;
        if(power < -17 || power > 22)                       return CMD_INVALID_POWER;
        if(preambleLength < 6)                              return CMD_INVALID_PREAMBLE_LENGTH;     // || preambleLength > 65535 (limited by data type)
        if(currentLimit < 0 || currentLimit > 140)          return CMD_INVALID_CURRENT_LIMIT;

        /* Set the radio parameters */
        int16_t res = setRadioParameters(frequency, bandwidth, spreadingFactor, codingRate, syncWord, power, preambleLength, currentLimit);

        /* Set the return buffer length */
        retBufferLen = 0;

        /* Return the result */
        return res;
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       setUNIX                                                                 |
    |   Purpose:    Set the UNIX timestamp.                                                 |
    |   Arguments:  Via buf, uint16_t                                                       |
    |               Bytes               Field                                               |
    |               -------------------------------------------                             |
    |               0                   Command                                             |
    |               1-4                 Timestamp                                           |
    |                                                                                       |
    |   Returns:    int16_t (error code)                                                    |
    \*-------------------------------------------------------------------------------------*/
    int16_t setUnix(const uint8_t* buf, uint16_t len){

        /* Check to make sure the payload is of the correct size */
        if(len != SET_UNIX_PAYLOAD_LEN) return CMD_MALFORMED_PAYLOAD;

        /* Parameters */            
        uint32_t timestamp;

        /* Get the values from byte string */           
        timestamp = extract_uint32_t(buf, 1);

        /* Set the return buffer length */
        retBufferLen = 0;

        /* Return successful */
        return CMD_OK;
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       setModeMessage                                                          |
    |   Purpose:    Set the mode and repeater message.                                      |
    |   Arguments:  Via buf, uint16_t                                                       |
    |               Bytes               Field                                               |
    |               -------------------------------------------                             |
    |               0                   Command                                             |
    |               1                   Mode                                                |
    |               2-256               Message                                             |
    |                                                                                       |
    |   Returns:    int16_t (error code)                                                    |
    \*-------------------------------------------------------------------------------------*/
    int16_t setModeMessage(const uint8_t* buf, uint16_t len){

        /* Check to make sure the payload is of the correct size */
        if(len != SET_MODE_MESSAGE_PAYLOAD_LEN) return CMD_MALFORMED_PAYLOAD;

        /* Parameters */            
        uint8_t mode;
        //uint8_t[LORA_MAX_PAYLOAD_SIZE] message;

        /* Get the values from byte string */           
        mode = extract_uint8_t(buf, 1);
        //memcpy(message...);

        /* Set the return buffer length */
        retBufferLen = 0;

        /* Return successful */
        return CMD_OK;
    }

    /* ---------------------------- Getters ---------------------------- */

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getLoRaParameters                                                       |
    |   Purpose:    Returns the currently set LoRa parameters.                              |
    |   Arguments:  Via buf, uint16_t, buf                                                  |
    |               Bytes               Field                                               |
    |               -------------------------------------------                             |
    |               0-254               Return data                                         |
    |                                                                                       |
    |   Returns:    int16_t (error code)                                                    |
    \*-------------------------------------------------------------------------------------*/
    int16_t getLoRaParameters(const uint8_t* buf, uint16_t len, uint8_t* retBuf){

        /* Check to make sure the payload is of the correct size */
        if(len != GET_LORA_PARAMETERS_PAYLOAD_LEN) return CMD_MALFORMED_PAYLOAD;
        
        /* Buffer for the float->uint32_t bytes conversion */
        uint32_t fBytes;
     
        /* Parameters */           
        float frequency         = getFrequency();
        float bandwidth         = getBandwidth();
        uint8_t spreadingFactor = getSpreadingFactor();
        uint8_t codingRate      = getCodingRate();
        uint8_t syncWord        = getSyncWord();
        int8_t power            = getPower();
        uint16_t preambleLength = getPreambleLength();
        float currentLimit      = getCurrentLim();

        /* Frequency */
        fBytes = *((uint32_t *) &frequency);
        retBuf[0] = (fBytes & 0xFF000000) >> 24;
        retBuf[1] = (fBytes & 0x00FF0000) >> 16;
        retBuf[2] = (fBytes & 0x0000FF00) >> 8;
        retBuf[3] = (fBytes & 0x000000FF);

        /* Bandwidth */
        fBytes = *((uint32_t *) &bandwidth);
        retBuf[4] = (fBytes & 0xFF000000) >> 24;
        retBuf[5] = (fBytes & 0x00FF0000) >> 16;
        retBuf[6] = (fBytes & 0x0000FF00) >> 8;
        retBuf[7] = (fBytes & 0x000000FF);

        /* Spreading factor */
        retBuf[8] = spreadingFactor;

        /* Coding rate */
        retBuf[9] = codingRate;

        /* Sync word   */         
        retBuf[10] = syncWord;
        
        /* Power */
        retBuf[11] = power;
        
        /* Preamble length */
        retBuf[12] = (preambleLength & 0xFF00) >> 8;
        retBuf[13] = (preambleLength & 0x00FF);

        /* Current limit */
        fBytes = *((uint32_t *) &currentLimit);
        retBuf[14] = (fBytes & 0xFF000000) >> 24;
        retBuf[15] = (fBytes & 0x00FF0000) >> 16;
        retBuf[16] = (fBytes & 0x0000FF00) >> 8;
        retBuf[17] = (fBytes & 0x000000FF);

        /* Set the return buffer length */
        retBufferLen = GET_LORA_PARAMETERS_RETURN_LEN;

        /* Return successful */
        return CMD_OK;
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getUnix                                                                 |
    |   Purpose:    Returns the current UNIX timestamp.                                     |
    |   Arguments:  Via buf, uint16_t, buf                                                  |
    |               Bytes               Field                                               |
    |               -------------------------------------------                             |
    |               0-254               Return data                                         |
    |                                                                                       |
    |   Returns:    int16_t (error code)                                                    |
    \*-------------------------------------------------------------------------------------*/
    int16_t getUnix(const uint8_t* buf, uint16_t len, uint8_t* retBuf){

        /* Check to make sure the payload is of the correct size */
        if(len != GET_UNIX_PAYLOAD_LEN) return CMD_MALFORMED_PAYLOAD;
     
        /* Parameters */           
        uint32_t timestamp = getUnixTime();
        //Serial.printf(F("TS: %u\r\n"),timestamp);

        /* UNIX */
        retBuf[0] = (timestamp & 0xFF00) >> 24;
        retBuf[1] = (timestamp & 0xFF00) >> 16;
        retBuf[2] = (timestamp & 0xFF00) >> 8;
        retBuf[3] = (timestamp & 0x00FF);

        /* Set the return buffer length */
        retBufferLen = GET_UNIX_RETURN_LEN;

        /* Return successful */
        return CMD_OK;
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getModeMessage                                                          |
    |   Purpose:    Returns the current mode and repeater message.                          |
    |   Arguments:  Via buf, uint16_t, buf                                                  |
    |               Bytes               Field                                               |
    |               -------------------------------------------                             |
    |               0-254               Return data                                         |
    |                                                                                       |
    |   Returns:    int16_t (error code)                                                    |
    \*-------------------------------------------------------------------------------------*/
    int16_t getModeMessage(const uint8_t* buf, uint16_t len, uint8_t* retBuf){
     
        /* Check to make sure the payload is of the correct size */
        if(len != GET_MODE_MESSAGE_PAYLOAD_LEN) return CMD_MALFORMED_PAYLOAD;
     
        /* Parameters */           
        uint8_t mode = getMode();
        uint8_t* messageBuf = getRepeaterMessage();

        /* Mode */
        retBuf[0] = mode;

        /* Repeater message */
        memcpy(retBuf, messageBuf, SET_MODE_MESSAGE_PAYLOAD_LEN-2);

        /* Set the return buffer length */
        retBufferLen = GET_MODE_MESSAGE_RETURN_LEN;

        /* Return successful */
        return CMD_OK;
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getModuleStatus                                                         |
    |   Purpose:    Returns the status (temperature, transmit time, etc.) of the module.    |
    |   Arguments:  Via buf, uint16_t, buf                                                  |
    |               Bytes               Field                                               |
    |               -------------------------------------------                             |
    |               0-254               Return data                                         |
    |                                                                                       |
    |   Returns:    int16_t (error code)                                                    |
    \*-------------------------------------------------------------------------------------*/
    int16_t getModuleStatus(const uint8_t* buf, uint16_t len, uint8_t* retBuf){

        /* Check to make sure the payload is of the correct size */
        if(len != GET_MODULE_STATUS_PAYLOAD_LEN) return CMD_MALFORMED_PAYLOAD;
        
        /* Buffer for the float->uint32_t bytes conversion */
        uint32_t fBytes;
        
        /* Parameters */           
        bool LoRaSet        = getLoRaSet();
        bool UnixSet        = getUnixSet();
        uint32_t uptime     = millis();
        float temperature   = getModuleTemperature();
        uint32_t timeOnAir  = getTOA();
        float dataRate      = getLoRaDataRate();

        /* LoRa */
        retBuf[0] = (uint8_t)LoRaSet;

        /* UNIX */
        retBuf[1] = (uint8_t)UnixSet;

        /* Uptime */
        retBuf[2] = (uptime & 0xFF00) >> 24;
        retBuf[3] = (uptime & 0xFF00) >> 16;
        retBuf[4] = (uptime & 0xFF00) >> 8;
        retBuf[5] = (uptime & 0x00FF);

        /* Temperature */
        fBytes = *((uint32_t *) &temperature);
        retBuf[6] = (fBytes & 0xFF000000) >> 24;
        retBuf[7] = (fBytes & 0x00FF0000) >> 16;
        retBuf[8] = (fBytes & 0x0000FF00) >> 8;
        retBuf[9] = (fBytes & 0x000000FF);

        /* Time on air */
        retBuf[10] = (timeOnAir & 0xFF00) >> 24;
        retBuf[11] = (timeOnAir & 0xFF00) >> 16;
        retBuf[12] = (timeOnAir & 0xFF00) >> 8;
        retBuf[13] = (timeOnAir & 0x00FF);
        
        /* Data rate */
        fBytes = *((uint32_t *) &dataRate);
        retBuf[14] = (fBytes & 0xFF000000) >> 24;
        retBuf[15] = (fBytes & 0x00FF0000) >> 16;
        retBuf[16] = (fBytes & 0x0000FF00) >> 8;
        retBuf[17] = (fBytes & 0x000000FF);

        /* Set the return buffer length */
        retBufferLen = GET_MODULE_STATUS_RETURN_LEN;
        
        /* Return successful */
        return CMD_OK;        
    }

    /* ------------------------- Miscellaneous ------------------------- */

    /*-------------------------------------------------------------------------------------*\
    |   Name:       radioReset                                                              |
    |   Purpose:    Perform a reset of the radio module.                                    |
    |   Arguments:  Via buf, uint16_t                                                       |
    |               Bytes               Field                                               |
    |               -------------------------------------------                             |
    |               0                   Command                                             |
    |                                                                                       |
    |   Returns:    int16_t (error code)                                                    |
    \*-------------------------------------------------------------------------------------*/
    int16_t radioReset(uint16_t len){
        
        /* Check to make sure the payload is of the correct size */
        if(len != RADIO_RESET_PAYLOAD_LEN) return CMD_MALFORMED_PAYLOAD;

        /* Attempt to reset the radio */
        int16_t res = resetRadio();

        /* Set the return buffer length */
        retBufferLen = 0;
        
        /* Return successful */
        return res;
    }
        
    /*-------------------------------------------------------------------------------------*\
    |   Name:       systemReset                                                             |
    |   Purpose:    Perform a system reset of the L-COM module.                             |
    |   Arguments:  Via buf, uint16_t                                                       |
    |               Bytes               Field                                               |
    |               -------------------------------------------                             |
    |               0                   Command                                             |
    |                                                                                       |
    |   Returns:    int16_t (error code)                                                    |
    \*-------------------------------------------------------------------------------------*/
    int16_t systemReset(uint16_t len){
        
        /* Check to make sure the payload is of the correct size */
        if(len != SYSTEM_RESET_PAYLOAD_LEN) return CMD_MALFORMED_PAYLOAD;
 
        /* Delay 10 seconds, watchdog will kick in at 4 seconds */
        delay(10000);

        /* Set the return buffer length */
        retBufferLen = 0;
       
        /* If we get a result back then that's probably not good */
        return CMD_OK;
    }
