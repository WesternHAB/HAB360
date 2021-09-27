/*
*   Author  :   Stephen Amey
*   Date    :   Aug. 28, 2021
*/


#include "Utility.h"


/*-------------------------------------------------------------------------*\
|								   Variables					   			|
\*-------------------------------------------------------------------------*/


    bool debugMode = false;
    bool UnixSet = false;
    uint32_t currentTime = 0, lastMillis = 0;
    uint8_t mode = NORMAL_MODE;
    uint8_t repeaterMessage[1]; //MAX_REPEATER_MESSAGE_SIZE

/*-------------------------------------------------------------------------*\
|								   Functions					   			|
\*-------------------------------------------------------------------------*/


    /*-------------------------------------------------------------------------------------*\
    |   Name:       enableDebug                                                             |
    |   Purpose:    Allows outputting of debug messages on the serial interface.            |
    |   Arguments:  void                                                                    |
    |   Returns:    void                                                                    |
    \*-------------------------------------------------------------------------------------*/
    void enableDebug(void){
        debugMode = true;
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       Log                                                                     |
    |   Purpose:    Debug message logging. If debugMode enabled, outputs messages on serial.|
    |   Arguments:  Compatible data type, int16_t                                           |
    |   Returns:    void                                                                    |
    \*-------------------------------------------------------------------------------------*/
    #define LOG_FUNCT {if(debugMode){Serial.print(out);if(res)Serial.printf(": error 0x%04X", res);Serial.println("");}}
    #define LOG_FUNCT_CAST {if(debugMode){Serial.print((const char*)out);if(res)Serial.printf(": error 0x%04X", res);Serial.println("");}}
    void Log(const __FlashStringHelper* out, int16_t res)   LOG_FUNCT
    void Log(const char* out, int16_t res)                  LOG_FUNCT
    void Log(const uint8_t* out, int16_t res)               LOG_FUNCT_CAST
    void Log(char* out, int16_t res)                        LOG_FUNCT
    void Log(uint8_t* out, int16_t res)                     LOG_FUNCT_CAST
    void Log(const uint16_t out, int16_t res)               LOG_FUNCT
    void Log(const int16_t out, int16_t res)                LOG_FUNCT
    void Log(const float out, int16_t res)                  LOG_FUNCT

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
    |   Name:       getUnixSet                                                              |
    |   Purpose:    Returns whether UNIX timestamp is set and time-keeping has been enabled.|
    |   Returns:    bool                                                                    |
    \*-------------------------------------------------------------------------------------*/
    bool getUnixSet(void){
        return UnixSet;
    }
    
    /*-------------------------------------------------------------------------------------*\
    |   Name:       setUnixTime                                                             |
    |   Purpose:    Sets the current UNIX time and enables timekeeping if not yet enabled.  |
    |   Arguments:  uint32_t                                                                |
    |   Returns:    void                                                                    |
    \*-------------------------------------------------------------------------------------*/
    void setUnixTime(uint32_t timestamp){
        UnixSet = true;
        currentTime = timestamp;
        lastMillis = millis();
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getUnixTime                                                             |
    |   Purpose:    Gets the current UNIX time. If time-keeping not enabled, returns 0.     |
    |   Arguments:  void                                                                    |
    |   Returns:    uint32_t                                                                |
    \*-------------------------------------------------------------------------------------*/
    uint32_t getUnixTime(void){
        // Return 0 if UNIX epoch not set
        if(!UnixSet) return 0;

        // Find the new current time and return it
        currentTime += (uint32_t)((millis() - lastMillis)/1000);
        lastMillis = millis();
        return currentTime;
    }
    
    /*-------------------------------------------------------------------------------------*\
    |   Name:       setMode                                                                 |
    |   Purpose:    Sets the current operating mode.                                        |
    |   Arguments:  uint8_t                                                                 |
    |   Returns:    void                                                                    |
    \*-------------------------------------------------------------------------------------*/
    void setMode(uint8_t _mode){
        mode = mode;
    }

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getMode                                                                 |
    |   Purpose:    Gets the current operating mode.                                        |
    |   Arguments:  void                                                                    |
    |   Returns:    uint8_t                                                                 |
    \*-------------------------------------------------------------------------------------*/
    uint8_t getMode(void){
        return mode;
    }
    
    /*-------------------------------------------------------------------------------------*\
    |   Name:       getRepeaterMessage                                                      |
    |   Purpose:    Returns a pointer to the current repeater message.                      |
    |   Arguments:  void                                                                    |
    |   Returns:    uint8_t*                                                                |
    \*-------------------------------------------------------------------------------------*/
    uint8_t* getRepeaterMessage(void){
        return repeaterMessage;
    }


    /*-------------------------------------------------------------------------------------*\
    |   Name:       getModuleTemperature                                                    |
    |   Purpose:    Gets the temperature of a thermistor located on the module.             |
    |   Arguments:  void                                                                    |
    |   Returns:    float                                                                   |
    \*-------------------------------------------------------------------------------------*/
    float getModuleTemperature(void){
        uint16_t Vth = analogRead(THERMISTOR_PIN);
        float logR1 = log(R2_OHM * (ANALOG_MAX_VALUE / (float)Vth - 1.0));
        float Tc = (1.0 / (C1 + C2*logR1 + C3*logR1*logR1*logR1)) - KELVIN_CELCIUS_DIFFERENCE;
        return Tc;        
    }
