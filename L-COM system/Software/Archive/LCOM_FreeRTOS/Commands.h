/*
*   Author  :   Stephen Amey
*   Date    :   July 18, 2021
*/

#ifndef INC_COMMANDS_H_
#define INC_COMMANDS_H_

#include <Arduino.h>
#include "LCOM_utility.h"
#include "Status_codes.h"


/*-------------------------------------------------------------------------*\
|								  Definitions					   			|
\*-------------------------------------------------------------------------*/


	/* Commands */
	#define SET_LORA_PARAMETERS			0x00
	#define SET_UNIX					0x01
	#define SET_MODE_MESSAGE			0x02

	#define GET_LORA_PARAMETERS			0x10
	#define GET_UNIX					0x11
	#define GET_MODE_MESSAGE			0x12
	#define GET_STATUS					0x13

	#define RADIO_RESET					0x20
	#define SYSTEM_RESET				0x21
	#define NEGOTIATE_LORA_PARAMETERS	0X22
	
	/* Payload lengths (command and parameters) */
	#define SET_LORA_PARAMETERS_PAYLOAD_LEN		(19)
	#define SET_UNIX_PAYLOAD_LEN				(5)
	#define SET_MODE_MESSAGE_LEN				(257)

	/* Modes */
	#define NORMAL_MODE					0x00
	#define REPEATER_MODE				0x01
	

/*-------------------------------------------------------------------------*\
|								   Functions					   			|
\*-------------------------------------------------------------------------*/


	/* Setters------------------------------------------------------------------*/
		uint16_t setLoRaParameters(const uint8_t* commandPtr, const uint16_t bufLen);
		uint16_t setUNIX(const uint8_t* commandPtr, const uint16_t bufLen);
		uint16_t setModeMessage(const uint8_t* commandPtr, const uint16_t bufLen);
		
	/* Getters------------------------------------------------------------------*/
		uint16_t getLoRaParameters(uint8_t* retBuf, uint16_t* retLen);
		uint16_t getUNIX(uint8_t* retBuf, uint16_t* retLen);
		uint16_t getModeMessage(uint8_t* retBuf, uint16_t* retLen);
		uint16_t getStatus(uint8_t* retBuf, uint16_t* retLen);

	/* Miscellaneous------------------------------------------------------------*/
		uint16_t radioReset(void);
		uint16_t systemReset(void);
		//int16_t negotiateLoRaParameters(void);


#endif /* INC_COMMANDS_H_ */
