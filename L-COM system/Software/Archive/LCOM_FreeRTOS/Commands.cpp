/*
*   Author  :   Stephen Amey
*   Date    :   July 18, 2021
*/


#include "Commands.h"


/*-------------------------------------------------------------------------*\
|								   Variables					   			|
\*-------------------------------------------------------------------------*/

	//char manipBuf[100];

	// Holds error returns from transmission
	//uint8_t err = 0;


	//Better formatted...

	/* Holds next transmission frame data */
	//uint8_t transmissionBuffer[AX25_MAX_DATA_PAYLOAD_LEN+1];	// No null terminator


/*-------------------------------------------------------------------------*\
|								   Functions					   			|
\*-------------------------------------------------------------------------*/


	/* Setters------------------------------------------------------------------*/

		/*-------------------------------------------------------------------------------------*\
		| 	Name: 		setLoRaParameters														|
		|	Purpose: 	Set the LoRa parameters used by the EBYTE module.						|
		|	Arguments:	Via commandPtr,															|
		|				Bytes				Field												|
		|				-------------------------------------------								|
		|				0					Command												|
		|				1-4					Frequency											|
		|				5-8					Bandwidth											|
		|				9					Spreading factor									|
		|				10					Coding rate											|
		|				11					Sync word											|
		|				12					Power												|
		|				13-14				Preamble length										|
		|				15-18				Current limit										|
		|																						|
		|	Returns:	uint16_t (error code)													|
		\*-------------------------------------------------------------------------------------*/
			uint16_t setLoRaParameters(const uint8_t* commandPtr, const uint16_t bufLen){

				/* Check to make sure the payload is of the correct size */
				if(bufLen != SET_LORA_PARAMETERS_PAYLOAD_LEN) return CMD_MALFORMED_PAYLOAD;

				/* Parameters */			
                int8_t power;
				uint8_t spreadingFactor, codingRate, syncWord;
				uint16_t preambleLength;
				float frequency, bandwidth, currentLimit;

				/* Get the values from byte string */
				frequency 		= extract_float(commandPtr, 1);
				bandwidth		= extract_float(commandPtr, 5);
				spreadingFactor = extract_uint8_t(commandPtr, 9);
				codingRate		= extract_uint8_t(commandPtr, 10);
				syncWord 		= extract_uint8_t(commandPtr, 11);
				power 			= (int8_t)extract_uint8_t(commandPtr, 12);
				preambleLength 	= extract_uint16_t(commandPtr, 13);
				currentLimit 	= extract_float(commandPtr, 15);
				
				/* Validation checks on the parameters */
				if(frequency < 150.0 || frequency > 960.0) 			return CMD_INVALID_FREQUENCY;
				if(bandwidth < 0.0 || bandwidth > 510.0) 			return CMD_INVALID_BANDWIDTH;
				if(spreadingFactor < 5 || spreadingFactor > 12) 	return CMD_INVALID_SPREADING_FACTOR;
				if(codingRate < 5 || codingRate > 8) 				return CMD_INVALID_CODING_RATE;
				if(syncWord == 0x34) 								return CMD_INVALID_SYNC_WORD;
				if(power < -17 || power > 22) 						return CMD_INVALID_POWER;
				if(preambleLength < 6) 								return CMD_INVALID_PREAMBLE_LENGTH; 	// || preambleLength > 65535 (limited by data type)
				if(currentLimit < 0 || currentLimit > 140) 			return CMD_INVALID_CURRENT_LIMIT;

                // Set the LoRa radio values here? Pass into some config function

				/* Return successful */
				return CMD_OK;
			}
			
		/*-------------------------------------------------------------------------------------*\
		| 	Name: 		setUNIX																	|
		|	Purpose: 	Set the UNIX timestamp.													|
		|	Arguments:	Via commandPtr,															|
		|				Bytes				Field												|
		|				-------------------------------------------								|
		|				0					Command												|
		|				1-4					Timestamp											|
		|																						|
		|	Returns:	uint16_t (error code)													|
		\*-------------------------------------------------------------------------------------*/
			uint16_t setUNIX(const uint8_t* commandPtr, const uint16_t bufLen){

				/* Check to make sure the payload is of the correct size */
				if(bufLen != SET_UNIX_PAYLOAD_LEN) return CMD_MALFORMED_PAYLOAD;

				/* Parameters */			
				uint32_t timestamp;

				/* Get the values from byte string */			
				timestamp = extract_uint32_t(commandPtr, 1);

				/* Return successful */
				return CMD_OK;
			}
			
		/*-------------------------------------------------------------------------------------*\
		| 	Name: 		setModeMessage															|
		|	Purpose: 	Set the mode and repeater message.										|
		|	Arguments:	Via commandPtr,															|
		|				Bytes				Field												|
		|				-------------------------------------------								|
		|				0					Command												|
		|				1					Mode												|
		|				2-256				Message												| // It's a radio lib limit of 255 bytes (instead of normal 8-bit 256)
		|																						|
		|	Returns:	uint16_t (error code)													|
		\*-------------------------------------------------------------------------------------*/
			uint16_t setModeMessage(const uint8_t* commandPtr, const uint16_t bufLen){

				/* Check to make sure the payload is of the correct size */
				if(bufLen != SET_MODE_MESSAGE_LEN) return CMD_MALFORMED_PAYLOAD;

				/* Parameters */			
				uint8_t mode;
				//uint8_t[LORA_MAX_PAYLOAD_SIZE] message;

				/* Get the values from byte string */			
				mode = extract_uint8_t(commandPtr, 1);
				//memcpy(message...);

				/* Return successful */
				return CMD_OK;
			}


	/* Getters------------------------------------------------------------------*/

		/*-------------------------------------------------------------------------------------*\
		| 	Name: 		getLoRaParameters														|
		|	Purpose: 	Returns the currently set LoRa parameters.								|
		|	Arguments:	Via commandPtr,															|
		|				Bytes				Field												|
		|				-------------------------------------------								|
		|				0-254				Return data											|
		|																						|
		|	Returns:	uint16_t (error code)													|
		\*-------------------------------------------------------------------------------------*/
			uint16_t getLoRaParameters(uint8_t* retBuf, uint16_t* retLen){

				// Assumes the buffer is big enough

                // Buffer for the float->uint32_t bytes conversion
                uint32_t fBytes;
             
                /* Parameters */            
                int8_t power = 1;
                uint8_t spreadingFactor = 1, codingRate = 1, syncWord = 1;
                uint16_t preambleLength = 1;
                float frequency = 1, bandwidth = 1, currentLimit = 1;

                // Would get these from yet another file. This file holds all the settings and interfaces with RadioLib by providing set (to set radio) and get functions (to return values from the class)

                //
                // THESE PARAMETERS DON'T ACTUALLY GO HERE, SHOULD BE TAKEN FROM THE RADIO SETTINGS
                //        

                // Clear the buffer       
                for(uint16_t i = 0; i != PKT_MAX_DATA_PAYLOAD_LEN; i++) retBuf[i] = 0;

                // Frequency
                fBytes = *((uint32_t *) &frequency);
                retBuf[0] = (fBytes & 0xFF000000) >> 24;
                retBuf[1] = (fBytes & 0x00FF0000) >> 16;
                retBuf[2] = (fBytes & 0x0000FF00) >> 8;
                retBuf[3] = (fBytes & 0x000000FF);

                // Bandwidth
                fBytes = *((uint32_t *) &bandwidth);
                retBuf[4] = (fBytes & 0xFF000000) >> 24;
                retBuf[5] = (fBytes & 0x00FF0000) >> 16;
                retBuf[6] = (fBytes & 0x0000FF00) >> 8;
                retBuf[7] = (fBytes & 0x000000FF);

                // Spreading factor
                retBuf[8] = spreadingFactor;

                // Coding rate
                retBuf[9] = codingRate;

                // Sync word           
                retBuf[10] = syncWord;
                
                // Power
                retBuf[11] = power;
                
                // Preamble length
                retBuf[12] = (preambleLength & 0xFF00) >> 8;
                retBuf[13] = (preambleLength & 0x00FF);

                // Current limit
                fBytes = *((uint32_t *) &currentLimit);
                retBuf[14] = (fBytes & 0xFF000000) >> 24;
                retBuf[15] = (fBytes & 0x00FF0000) >> 16;
                retBuf[16] = (fBytes & 0x0000FF00) >> 8;
                retBuf[17] = (fBytes & 0x000000FF);

				return CMD_OK;
			}
			
		/*-------------------------------------------------------------------------------------*\
		| 	Name: 		getUNIX																	|
		|	Purpose: 	Returns the currently set UNIX timestamp.								|
		|	Arguments:	Via commandPtr,															|
		|				Bytes				Field												|
		|				-------------------------------------------								|
		|				0					Command												|
		|																						|
		|	Returns:	uint16_t (error code)													|
		\*-------------------------------------------------------------------------------------*/
			uint16_t getUNIX(uint8_t* retBuf, uint16_t* retLen){
                // From LCOM_utility
                //epoch = val;
                //currentTime = epoch;
                //UNIXSet = true;
				
				return CMD_OK;
			}
			
		/*-------------------------------------------------------------------------------------*\
		| 	Name: 		getModeMessage															|
		|	Purpose: 	Returns the currently set mode and repeater message.					|
		|	Arguments:	Via commandPtr,															|
		|				Bytes				Field												|
		|				-------------------------------------------								|
		|				0					Command												|
		|																						|
		|	Returns:	uint16_t (error code)													|
		\*-------------------------------------------------------------------------------------*/
			uint16_t getModeMessage(uint8_t* retBuf, uint16_t* retLen){

				
				return CMD_OK;
			}
			
		/*-------------------------------------------------------------------------------------*\
		| 	Name: 		getStatus																|
		|	Purpose: 	Returns the status (e.g. temperature, operation) of the L-COM module.	|
		|	Arguments:	Via commandPtr,															|
		|				Bytes				Field												|
		|				-------------------------------------------								|
		|				0					Command												|
		|																						|
		|	Returns:	uint16_t (error code)													|
		\*-------------------------------------------------------------------------------------*/
			uint16_t getStatus(uint8_t* retBuf, uint16_t* retLen){

				
				return CMD_OK;
			}
			
			
	/* Miscellaneous------------------------------------------------------------*/

		/*-------------------------------------------------------------------------------------*\
		| 	Name: 		radioReset																|
		|	Purpose: 	Perform a reset of the radio module.									|
		|	Arguments:	Via commandPtr,															|
		|				Bytes				Field												|
		|				-------------------------------------------								|
		|				0					Command												|
		|																						|
		|	Returns:	uint16_t (error code)													|
		\*-------------------------------------------------------------------------------------*/
			uint16_t radioReset(void){

				
				return CMD_OK;
			}
			
		/*-------------------------------------------------------------------------------------*\
		| 	Name: 		systemReset																|
		|	Purpose: 	Perform a system reset of the L-COM module.								|
		|	Arguments:	Via commandPtr,															|
		|				Bytes				Field												|
		|				-------------------------------------------								|
		|				0					Command												|
		|																						|
		|	Returns:	uint16_t (error code)													|
		\*-------------------------------------------------------------------------------------*/
			uint16_t systemReset(void){

				
				return CMD_OK;
			}
