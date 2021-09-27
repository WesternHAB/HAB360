// Signify the beginning and end of the packet
#define START_FLAG					0x7E
#define END_FLAG					0x7F

// Packet, header, and payload lengths
#define PKT_MAX_LEN					274
#define PKT_HEADER_LEN				8
#define PKT_TRAILER_LEN             1
#define PKT_MAX_DATA_PAYLOAD_LEN	265 // PKT_MAX_LEN - PKT_HEADER_LEN - PKT_TRAILER_LEN # 8(common header) + LoRa max size(255) + 10 (message header)
#define SERIAL_BAUD                 115200 

// Field locations
#define TYPE_CYCLIC_FIELD_INDEX		1
#define LENGTH_INDEX				2
#define UNIX_TIME_INDEX				4
#define PAYLOAD_INDEX				8

// Packet type (Most-significant 3 bits identify type, last 5 bits are for cyclic frame count)
#define STATUS_PACKET 				0b00000000
#define COMMAND_PACKET 				0b00100000
#define ACK_PACKET 					0b01000000
#define MESSAGE_PACKET 				0b01100000
