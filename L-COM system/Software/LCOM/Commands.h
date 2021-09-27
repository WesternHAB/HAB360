/*
*   Author  :   Stephen Amey
*   Date    :   Aug. 29, 2021
*/

#ifndef INC_COMMANDS_H_
#define INC_COMMANDS_H_

#include <Arduino.h>
#include "RadioController.h"
#include "Utility.h"


/*-------------------------------------------------------------------------*\
|                                  Definitions                               |
\*-------------------------------------------------------------------------*/


    //#define MAX_COMMAND_LEN                     (265)
    #define CMD_INDEX                           (0)

    /* Commands */
    #define SET_LORA_PARAMETERS                 0x00
    #define SET_UNIX                            0x01
    #define SET_MODE_MESSAGE                    0x02
    #define GET_LORA_PARAMETERS                 0x10
    #define GET_UNIX                            0x11
    #define GET_MODE_MESSAGE                    0x12
    #define GET_MODULE_STATUS                   0x13
    #define RADIO_RESET                         0x20
    #define SYSTEM_RESET                        0x21
    //#define NEGOTIATE_LORA_PARAMETERS           0X22

    /* Payload lengths (command and parameters) */
    #define SET_LORA_PARAMETERS_PAYLOAD_LEN     (19)
    #define SET_UNIX_PAYLOAD_LEN                (5)
    #define SET_MODE_MESSAGE_PAYLOAD_LEN        (257)
    #define GET_LORA_PARAMETERS_PAYLOAD_LEN     (1)
    #define GET_UNIX_PAYLOAD_LEN                (1)
    #define GET_MODE_MESSAGE_PAYLOAD_LEN        (1)
    #define GET_MODULE_STATUS_PAYLOAD_LEN       (1)
    #define RADIO_RESET_PAYLOAD_LEN             (1)
    #define SYSTEM_RESET_PAYLOAD_LEN            (1)

    /* Data return lengths */
    #define GET_LORA_PARAMETERS_RETURN_LEN      (18)
    #define GET_UNIX_RETURN_LEN                 (4)
    #define GET_MODE_MESSAGE_RETURN_LEN         (256)
    #define GET_MODULE_STATUS_RETURN_LEN        (18)

    /* Status codes */
    #define CMD_OK                              0x0000
    #define CMD_MALFORMED_PAYLOAD               0x0101
    #define CMD_UNKNOWN_COMMAND                 0X0102
    #define CMD_INVALID_FREQUENCY               0x0103
    #define CMD_INVALID_BANDWIDTH               0x0104
    #define CMD_INVALID_SPREADING_FACTOR        0x0105
    #define CMD_INVALID_CODING_RATE             0x0106
    #define CMD_INVALID_SYNC_WORD               0x0107
    #define CMD_INVALID_POWER                   0x0108
    #define CMD_INVALID_PREAMBLE_LENGTH         0x0109
    #define CMD_INVALID_CURRENT_LIMIT           0x0110
    

/*-------------------------------------------------------------------------*\
|                                  Functions                                |
\*-------------------------------------------------------------------------*/


    /*-------------------------------------------------------------------------------------*\
    |   Name:       getCommandBuffer                                                        |
    |   Purpose:    Returns a pointer to the command buffer.                                |
    |   Arguments:  void                                                                    |
    |   Returns:    uint8_t*                                                                |
    \*-------------------------------------------------------------------------------------*/
    //uint8_t* getCommandBuffer(void);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getCommandBufferLength                                                  |
    |   Purpose:    Returns the data length in bytes of returned data in the command buffer.|
    |   Arguments:  void                                                                    |
    |   Returns:    uint16_t                                                                |
    \*-------------------------------------------------------------------------------------*/
    //uint16_t getCommandBufferLength(void);
    uint16_t getReturnBufferLength(void);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       executeCommand                                                          |
    |   Purpose:    Executes the passed command.                                            |
    |   Arguments:  void                                                                    |
    |   Returns:    int16_t                                                                 |
    \*-------------------------------------------------------------------------------------*/
    int16_t executeCommand(const uint8_t* buf, uint16_t bufLen, uint8_t* retBuf);

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
    int16_t setLoRaParameters(const uint8_t* buf, uint16_t len);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       setUNIX                                                                 |
    |   Purpose:    Set the UNIX timestamp.                                                 |
    |   Arguments:  Via buf,                                                                |
    |               Bytes               Field                                               |
    |               -------------------------------------------                             |
    |               0                   Command                                             |
    |               1-4                 Timestamp                                           |
    |                                                                                       |
    |   Returns:    int16_t (error code)                                                    |
    \*-------------------------------------------------------------------------------------*/
    int16_t setUnix(const uint8_t* buf, uint16_t len);

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
    int16_t setModeMessage(const uint8_t* buf, uint16_t len);

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
    int16_t getLoRaParameters(const uint8_t* buf, uint16_t len, uint8_t* retBuf);

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
    int16_t getUnix(const uint8_t* buf, uint16_t len, uint8_t* retBuf);

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
    int16_t getModeMessage(const uint8_t* buf, uint16_t len, uint8_t* retBuf);

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
    int16_t getModuleStatus(const uint8_t* buf, uint16_t len, uint8_t* retBuf);

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
    int16_t radioReset(uint16_t len);
        
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
    int16_t systemReset(uint16_t len);


#endif /* INC_COMMANDS_H_ */
