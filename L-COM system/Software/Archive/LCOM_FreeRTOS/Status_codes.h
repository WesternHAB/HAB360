/*
*   Author  :   Stephen Amey
*   Date    :   July 18, 2021
*/

#ifndef INC_STATUS_CODES_H_
#define INC_STATUS_CODES_H_


/*-------------------------------------------------------------------------*\
|								  Definitions					   			|
\*-------------------------------------------------------------------------*/


	// Status codes utilize a uint16_t variable			
	#define STATUS_OK						0x0000	
	
	/* RadioLib */	
	
	/* LCOM */
	#define CMD_MALFORMED_PAYLOAD			0x0100
	
	
	#define CMD_OK							0x0000
	#define CMD_INVALID_FREQUENCY			0x0101
	#define CMD_INVALID_BANDWIDTH			0x0102
	#define CMD_INVALID_SPREADING_FACTOR	0x0103
	#define CMD_INVALID_CODING_RATE			0x0104
	#define CMD_INVALID_SYNC_WORD			0x0105
	#define CMD_INVALID_POWER				0x0106
	#define CMD_INVALID_PREAMBLE_LENGTH		0x0107
	#define CMD_INVALID_CURRENT_LIMIT		0x0108


#endif /* INC_STATUS_CODES_H_ */
