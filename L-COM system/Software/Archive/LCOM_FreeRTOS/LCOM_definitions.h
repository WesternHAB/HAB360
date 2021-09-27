//#define RADIOLIB_DEBUG
//#define RADIOLIB_VERBOSE

/* Pins------------------------------------------------------------------------*/
	/* LoRa module */
	#define NSS                             10
	#define DIO1                            2
	#define NRST                            9
	#define BUSY                            8
	
	/* Thermistor */
	#define THERMISTOR_PIN                  A0

/* Temperature-----------------------------------------------------------------*/
	#define ANALOG_MAX_VALUE                1023.0
	#define KELVIN_CELCIUS_DIFFERENCE       273.15  
	#define R2_OHM                          10000               // Ohm
	#define C1                              1.009249522e-03
	#define C2                              2.378405444e-04
	#define C3                              2.019202697e-07

/* Communication---------------------------------------------------------------*/
	/* LoRa */
	#define LORA_MAX_PAYLOAD_SIZE           255
	#define FREQUENCY                       915.0                   // Canadian unlicensed band
	#define BANDWIDTH                       125.0
	#define SPREADING_FACTOR                9
	#define CODING_RATE                     7
	#define SYNC_WORD                       0x12                    // (private network)
	#define OUTPUT_POWER                    14                      // (max 22 dBm)
    #define PREAMBLE_LENGTH                 8
	#define CURRENT_LIMIT                   60.0                    // (max 140 mA)
	// Nyquist formula: bit_rate = 2*BANDWIDTH*log(CODING_RATE)/LOG(2)

	//#define MAX_MESSAGE_PAYLOAD_LEN			237
