// Statuses
#define STATUS_OK						0x00
// Add all the RadioLib ones here, then my own after

// Command identifier
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

// Modes
#define NORMAL_MODE					0x00
#define REPEATER_MODE				0x01

// Messages and commands
#define MAX_LORA_MESSAGE_LENGTH		255

// LoRa parameters
#define DEFAULT_FREQUENCY 			915.0
#define DEFAULT_BANDWIDTH           125.0
#define DEFAULT_SPREADING_FACTOR    9
#define DEFAULT_CODING_RATE         7
#define DEFAULT_SYNC_WORD           0x12                    // (private network)
#define DEFAULT_POWER        		14                      // (max 22 dBm)
#define DEFAULT_CURRENT_LIMIT       60.0                    
#define DEFAULT_PREAMBLE_LENGTH     8
#define DEFAULT_CURRENT_LIMIT     	60.0                    // (max 140 mA)
