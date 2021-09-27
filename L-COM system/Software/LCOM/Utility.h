/*
*   Author  :   Stephen Amey
*   Date    :   Aug. 28, 2021
*/

#ifndef INC_UTILITY_H_
#define INC_UTILITY_H_

#include <Arduino.h>


/*-------------------------------------------------------------------------*\
|								  Definitions					   			|
\*-------------------------------------------------------------------------*/


    /* Modes */
    #define NORMAL_MODE                     0x00
    #define REPEATER_MODE                   0x01
    #define MAX_REPEATER_MESSAGE_SIZE       255

    /* Temperature */
    #define THERMISTOR_PIN                  A0
    #define ANALOG_MAX_VALUE                1023.0
    #define KELVIN_CELCIUS_DIFFERENCE       273.15  
    #define R2_OHM                          10000               // Ohms
    #define C1                              1.009249522e-03
    #define C2                              2.378405444e-04
    #define C3                              2.019202697e-07    


/*-------------------------------------------------------------------------*\
|								   Functions					   			|
\*-------------------------------------------------------------------------*/


    /*-------------------------------------------------------------------------------------*\
    |   Name:       enableDebug                                                             |
    |   Purpose:    Allows outputting of debug messages on the serial interface.            |
    |   Arguments:  void                                                                    |
    |   Returns:    void                                                                    |
    \*-------------------------------------------------------------------------------------*/
    void enableDebug(void);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       Log                                                                     |
    |   Purpose:    Debug message logging. If debugMode enabled, outputs messages on serial.|
    |   Arguments:  Compatible data type, int16_t                                           |
    |   Returns:    void                                                                    |
    \*-------------------------------------------------------------------------------------*/

    void Log(const __FlashStringHelper* out, int16_t res = 0);
    void Log(const char* out, int16_t res = 0);
    //void Log(const uint8_t* out, int16_t res = 0);
    void Log(char* out, int16_t res = 0);   
    void Log(uint8_t* out, int16_t res = 0);  
    void Log(const uint16_t out, int16_t res = 0);
    void Log(const int16_t out, int16_t res = 0);
    void Log(const float out, int16_t res = 0);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       extract_<data type>                                                     |
    |   Purpose:    Extracts a variable of a given data type from a byte array.             |
    |               These functions are used to deal with byte-alignment and endianess.     |
    |               If using printf(), remember to use the long-type identifiers if needed. |
    |   Arguments:  uint8_t *buffer, uint16_t position                                      |
    |   Returns:    <data type>                                                             |
    \*-------------------------------------------------------------------------------------*/
    uint32_t extract_uint32_t(const uint8_t *buf, uint16_t pos);
    uint16_t extract_uint16_t(const uint8_t *buf, uint16_t pos);
    uint8_t extract_uint8_t(const uint8_t *buf, uint16_t pos);
    float extract_float(const uint8_t *buf, uint16_t pos);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getUnixSet                                                              |
    |   Purpose:    Returns whether UNIX timestamp is set and time-keeping has been enabled.|
    |   Returns:    bool                                                                    |
    \*-------------------------------------------------------------------------------------*/
    bool getUnixSet(void);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       setUnixTime                                                             |
    |   Purpose:    Sets the current UNIX time and enables timekeeping if not yet enabled.  |
    |   Arguments:  uint32_t                                                                |
    |   Returns:    void                                                                    |
    \*-------------------------------------------------------------------------------------*/
    void setUnixTime(uint32_t timestamp);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getUnixTime                                                             |
    |   Purpose:    Gets the current UNIX time. If time-keeping not enabled, returns 0.     |
    |   Arguments:  void                                                                    |
    |   Returns:    uint32_t                                                                |
    \*-------------------------------------------------------------------------------------*/
    uint32_t getUnixTime(void);
    
    /*-------------------------------------------------------------------------------------*\
    |   Name:       setMode                                                                 |
    |   Purpose:    Sets the current operating mode.                                        |
    |   Arguments:  uint8_t                                                                 |
    |   Returns:    void                                                                    |
    \*-------------------------------------------------------------------------------------*/
    void setMode(uint8_t _mode);
    
    /*-------------------------------------------------------------------------------------*\
    |   Name:       getMode                                                                 |
    |   Purpose:    Gets the current operating mode.                                        |
    |   Arguments:  void                                                                    |
    |   Returns:    uint8_t                                                                 |
    \*-------------------------------------------------------------------------------------*/
    uint8_t getMode(void);
    
    /*-------------------------------------------------------------------------------------*\
    |   Name:       getRepeaterMessage                                                      |
    |   Purpose:    Returns a pointer to the current repeater message.                      |
    |   Arguments:  void                                                                    |
    |   Returns:    uint8_t*                                                                |
    \*-------------------------------------------------------------------------------------*/
    uint8_t* getRepeaterMessage(void);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getModuleTemperature                                                    |
    |   Purpose:    Gets the temperature of a thermistor located on the module.             |
    |   Arguments:  void                                                                    |
    |   Returns:    float                                                                   |
    \*-------------------------------------------------------------------------------------*/
    float getModuleTemperature(void);

#endif /* INC_UTILITY_H_ */
