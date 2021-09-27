/*
*   Author  :   Stephen Amey
*   Date    :   July 18, 2021
*/

#ifndef INC_LCOM_UTILITY_H_
#define INC_LCOM_UTILITY_H_

#include <Arduino.h>
#include "Serial_definitions.h"


/*-------------------------------------------------------------------------*\
|								  Definitions					   			|
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
|								   Functions					   			|
\*-------------------------------------------------------------------------*/


	boolean verifyPacket(const uint8_t *buf);
    void createPacket(uint8_t *buf, uint8_t type, uint8_t *payloadBuf, uint16_t bufLen);
    void createAckPacket(uint8_t *buf, uint16_t res, uint8_t *retDataBuf, uint16_t bufLen);
    uint32_t getCurrentTime();
	uint32_t extract_uint32_t(const uint8_t *buf, uint16_t pos);
	uint16_t extract_uint16_t(const uint8_t *buf, uint16_t pos);
	uint8_t extract_uint8_t(const uint8_t *buf, uint16_t pos);
	float extract_float(const uint8_t *buf, uint16_t pos);
    uint8_t getPacketID();

	
#endif /* INC_LCOM_UTILITY_H_ */
