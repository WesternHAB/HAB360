/*
*   Author  :   Stephen Amey
*   Date    :   Aug. 28, 2021
*/

#ifndef INC_RADIOCONTROLLER_H_
#define INC_RADIOCONTROLLER_H_

#include <Arduino.h>
#include <RadioLib.h>
#include "Utility.h"
//#include "Status_codes.h"


/*-------------------------------------------------------------------------*\
|								  Definitions					   			|
\*-------------------------------------------------------------------------*/


    /* LoRa module pins */
    #define NSS                             10
    #define DIO1                            2
    #define NRST                            9
    #define BUSY                            8
    #define RX                              6 //7 (had these swapped by accident?)
    #define TX                              7 //6

    /* Default parameters */
    // Nyquist formula: bit_rate = 2*BANDWIDTH*log(CODING_RATE)/LOG(2)
    #define DEFAULT_FREQUENCY               915.0                   // Canadian unlicensed band
    #define DEFAULT_BANDWIDTH               125.0
    #define DEFAULT_SPREADING_FACTOR        9
    #define DEFAULT_CODING_RATE             7
    #define DEFAULT_SYNC_WORD               0x12                    // (private network)
    #define DEFAULT_OUTPUT_POWER            14                      // (max 22 dBm)
    #define DEFAULT_PREAMBLE_LENGTH         8
    #define DEFAULT_CURRENT_LIMIT           60.0                    // (max 140 mA)

    /* Message */
    #define MAX_LORA_MESSAGE_SIZE           255

    /* Status codes */
    //#define NEW_RADIO_DATA_BUFFERED         0x0200
    #define NO_NEW_RADIO_DATA               0x0201
    

/*-------------------------------------------------------------------------*\
|								   Functions					   			|
\*-------------------------------------------------------------------------*/


    /*-------------------------------------------------------------------------------------*\
    |   Name:       initializeRadio                                                         |
    |   Purpose:    Initializes the LoRa radio pins, current limit, and starts listening.   |
    |   Arguments:  void                                                                    |
    |   Returns:    void                                                                    |
    \*-------------------------------------------------------------------------------------*/
    int16_t initializeRadio(void);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       receiveCallback                                                         |
    |   Purpose:    Handles the interrupt from the LoRa module.                             |
    |   Arguments:  void                                                                    |
    |   Returns:    void                                                                    |
    \*-------------------------------------------------------------------------------------*/
    void receiveCallback(void);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       readRadioData                                                           |
    |   Purpose:    Check if there is radio data available, and reads it into the buffer.   |
    |   Arguments:  void                                                                    |
    |   Returns:    int16_t                                                                 |
    \*-------------------------------------------------------------------------------------*/
    int16_t readRadioData(void);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getRadioData                                                            |
    |   Purpose:    Returns a pointer to the radio data buffer.                             |
    |   Arguments:  void                                                                    |
    |   Returns:    uint8_t*                                                                 |
    \*-------------------------------------------------------------------------------------*/
    uint8_t* getRadioData(void);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getRadioDataLength                                                      |
    |   Purpose:    Returns the data length in bytes of the last received radio data.       |
    |   Arguments:  void                                                                    |
    |   Returns:    uint16_t                                                                |
    \*-------------------------------------------------------------------------------------*/
    uint16_t getRadioDataLength(void);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       transmitRadio                                                           |
    |   Purpose:    Transmits the data in the buffer over the radio.                        |
    |   Arguments:  uint8_t*, uint16_t                                                      |
    |   Returns:    int16_t                                                                 |
    \*-------------------------------------------------------------------------------------*/
    int16_t transmitRadio(uint8_t* buf, uint16_t len);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       setRadioParameters                                                      |
    |   Purpose:    Sets the radio parameters.                                              |
    |   Arguments:  void                                                                    |
    |   Returns:    int16_t                                                                 |
    \*-------------------------------------------------------------------------------------*/
    int16_t setRadioParameters(
        float _frequency, float _bandwidth, uint8_t _spreadingFactor, uint8_t _codingRate,
        uint8_t _syncWord, int8_t _power, uint16_t _preambleLength, float _currentLimit
    );

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getLoRaSet                                                              |
    |   Purpose:    Returns whether LoRa parameters have been changed from the default.     |
    |   Returns:    bool                                                                    |
    \*-------------------------------------------------------------------------------------*/
    bool getLoRaSet(void);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       radioReset                                                              |
    |   Purpose:    Resets the radio.                                                       |
    |   Returns:    int16_t                                                                 |
    \*-------------------------------------------------------------------------------------*/
    int16_t resetRadio(void);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getFrequency                                                            |
    |   Purpose:    Returns the current frequency of the radio.                             |
    |   Returns:    float                                                                   |
    \*-------------------------------------------------------------------------------------*/
    float getFrequency(void);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getBandwidth                                                            |
    |   Purpose:    Returns the current bandwidth of the radio.                             |
    |   Returns:    float                                                                   |
    \*-------------------------------------------------------------------------------------*/
    float getBandwidth(void);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getSpreadingFactor                                                      |
    |   Purpose:    Returns the current spreading factor of the radio.                      |
    |   Returns:    uint8_t                                                                 |
    \*-------------------------------------------------------------------------------------*/
    uint8_t getSpreadingFactor(void);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getCodingRate                                                           |
    |   Purpose:    Returns the current coding rate of the radio.                           |
    |   Returns:    uint8_t                                                                 |
    \*-------------------------------------------------------------------------------------*/
    uint8_t getCodingRate(void);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getSyncWord                                                             |
    |   Purpose:    Returns the current sync word of the radio.                             |
    |   Returns:    uint8_t                                                                 |
    \*-------------------------------------------------------------------------------------*/
    uint8_t getSyncWord(void);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getPower                                                                |
    |   Purpose:    Returns the current power of the radio.                                 |
    |   Returns:    uint8_t                                                                 |
    \*-------------------------------------------------------------------------------------*/
    uint8_t getPower(void);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getPreambleLength                                                       |
    |   Purpose:    Returns the current preamble length of the radio.                       |
    |   Returns:    uint16_t                                                                |
    \*-------------------------------------------------------------------------------------*/
    uint16_t getPreambleLength(void);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getCurrentLim                                                           |
    |   Purpose:    Returns the current current limit of the radio.                         |
    |   Returns:    float                                                                   |
    \*-------------------------------------------------------------------------------------*/
    float getCurrentLim(void);


    /*-------------------------------------------------------------------------------------*\
    |   Name:       getTOA                                                                  |
    |   Purpose:    Returns the estimated time on air for the current LoRa parameters.      |
    |   Returns:    uint32_t                                                                |
    \*-------------------------------------------------------------------------------------*/
    uint32_t getTOA(void);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getLoRaDataRate                                                         |
    |   Purpose:    Returns the data rate of the last packet transmitted.                   |
    |   Returns:    float                                                                   |
    \*-------------------------------------------------------------------------------------*/
    float getLoRaDataRate(void);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getMessageRSSI                                                          |
    |   Purpose:    Returns the RSSI of the last packet transmitted.                        |
    |   Returns:    float                                                                   |
    \*-------------------------------------------------------------------------------------*/
    float getMessageRSSI(void);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getMessageSNR                                                           |
    |   Purpose:    Returns the SNR of the last packet transmitted.                         |
    |   Returns:    float                                                                   |
    \*-------------------------------------------------------------------------------------*/
    float getMessageSNR(void);
    
#endif /* INC_RADIOCONTROLLER_H_ */
