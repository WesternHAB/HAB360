#include <MPU9250.h>

/*
*   Author  :   Stephen Amey
*   Date    :   Aug. 28, 2021
*/

#ifndef INC_SERIALINTERFACE_H_
#define INC_SERIALINTERFACE_H_

#include <Arduino.h>
#include "Utility.h"


/*-------------------------------------------------------------------------*\
|                                  Definitions                               |
\*-------------------------------------------------------------------------*/


    #define SERIAL_BAUD                 115200
    #define SERIAL_PACKET_TIMEOUT       500

    // Signify the beginning and end of the packet
    #define START_FLAG                  0x7E
    #define END_FLAG                    0x7F
    
    // Packet, header, and payload lengths
    #define PKT_HEADER_LEN              8
    #define PKT_TRAILER_LEN             1
    #define PKT_HEADER_TRAILER_LEN      (PKT_HEADER_LEN + PKT_TRAILER_LEN)
    //#define PKT_MAX_DATA_PAYLOAD_LEN  265
    #define PKT_MAX_LEN                 274
    
    // Field locations
    #define TYPE_CYCLIC_FIELD_INDEX     1
    #define LENGTH_INDEX                2
    #define UNIX_TIME_INDEX             4
    #define PAYLOAD_INDEX               8
    #define MESSAGE_INDEX               18      // There are 10 bytes at the start of a message packet payload dedicated to RSSI, SNR, and result
    
    // Packet type (Most-significant 3 bits identify type, last 5 bits are for cyclic frame count)
    #define ACK_PACKET                  0b00000000 
	#define COMMAND_PACKET              0b00100000
    #define MESSAGE_PACKET              0b01000000

    /* Status codes */
    #define PACKET_COMPLETE             0x0300
    #define MALFORMED_PACKET            0x0301
    #define NO_NEW_SERIAL_DATA          0x0302
    #define NEW_PARTIAL_SERIAL_DATA     0x0303
    #define MISPLACED_START_FLAG        0x0304
    #define MISPLACED_END_FLAG          0x0305
    

/*-------------------------------------------------------------------------*\
|                                  Functions                                |
\*-------------------------------------------------------------------------*/


    // Create packet, create Ack packet, verify packet
    // Get next packet ID

    /*-------------------------------------------------------------------------------------*\
    |   Name:       readSerial                                                              |
    |   Purpose:    Checks for new serial data and reads it into the buffer.                |
    |   Arguments:  void                                                                    |
    |   Returns:    int16_t                                                                 |
    \*-------------------------------------------------------------------------------------*/
    int16_t readSerialData(void);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getSerialSendBuffer                                                     |
    |   Purpose:    Returns a pointer to the outgoing serial data buffer.                   |
    |   Arguments:  void                                                                    |
    |   Returns:    int16_t                                                                 |
    \*-------------------------------------------------------------------------------------*/
    //uint8_t* getSerialSendBuffer(void);
    
    /*-------------------------------------------------------------------------------------*\
    |   Name:       getSerialReadBuffer                                                     |
    |   Purpose:    Returns a pointer to the incoming serial data buffer.                   |
    |   Arguments:  void                                                                    |
    |   Returns:    uint8_t*                                                                |
    \*-------------------------------------------------------------------------------------*/
    uint8_t* getSerialReadBuffer(void);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       getSerialReadBufferLength                                               |
    |   Purpose:    Returns the data length in bytes of the last received serial data.      |
    |   Arguments:  void                                                                    |
    |   Returns:    uint16_t                                                                |
    \*-------------------------------------------------------------------------------------*/
    uint16_t getSerialReadBufferLength(void);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       verifyPacket                                                            |
    |   Purpose:    Verifies a packet by checking for the start and end flags.              |
    |               Does not check the rest of the packet content, e.g. packet type.        |
    |   Arguments:  uint8_t* buf                                                            |
    |   Returns:    boolean                                                                 |
    \*-------------------------------------------------------------------------------------*/
    bool verifyPacket(uint8_t* buf);

	/*-------------------------------------------------------------------------------------*\
    |   Name:       createPacket                                                            |
    |   Purpose:    Creates a serial packet with a given payload.              				|
    |   Arguments:  uint8_t, uint8_t*, uint16_t                                             |
    |   Returns:    uint8_t*                                                                |
    \*-------------------------------------------------------------------------------------*/
    uint8_t* createPacket(uint8_t type, uint8_t* payloadBuf, uint16_t bufLen);
	
    /*-------------------------------------------------------------------------------------*\
    |   Name:       createAckPacket                                                         |
    |   Purpose:    Creates an Ack serial packet with the given result and return data.		|
    |   Arguments:  int16_t, uint8_t*, uint16_t                                             |
    |   Returns:    uint8_t*                                                                |
    \*-------------------------------------------------------------------------------------*/
    uint8_t* createAckPacket(int16_t res, uint8_t* retBuf, uint16_t bufLen);

    /*-------------------------------------------------------------------------------------*\
    |   Name:       createMessagePacket                                                     |
    |   Purpose:    Creates a message serial packet with the given result and return data.  |
    |   Arguments:  uint16_t, float, float, uint8_t*, uint16_t                              |
    |   Returns:    uint8_t*                                                                |
    \*-------------------------------------------------------------------------------------*/
    uint8_t* createMessagePacket(int16_t res, float RSSI, float SNR, uint8_t* retBuf, uint16_t bufLen);
	
	/*-------------------------------------------------------------------------------------*\
    |   Name:       getPacketID                                                             |
    |   Purpose:    Returns a cyclic 5-bit packet ID.                                       |
    |   Arguments:  void                                                                    |
    |   Returns:    uint8_t                                                                 |
    \*-------------------------------------------------------------------------------------*/
	uint8_t getPacketID();
	
    /*-------------------------------------------------------------------------------------*\
    |   Name:       getSendBufferLen                                                        |
    |   Purpose:    Returns the length of the last packet data in the send buffer.          |
    |   Arguments:  void                                                                    |
    |   Returns:    uint16_t                                                                |
    \*-------------------------------------------------------------------------------------*/
    uint16_t getSendBufferLen();

    
#endif /* INC_SERIALINTERFACE_H_ */
