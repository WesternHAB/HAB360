/*
   RadioLib SX126x Transmit with Interrupts Example

   This example transmits LoRa packets with one second delays
   between them. Each packet contains up to 256 bytes
   of data, in the form of:
    - Arduino String
    - null-terminated char array (C-string)
    - arbitrary binary data (byte array)

   Other modules from SX126x family can also be used.

   For default module settings, see the wiki page
   https://github.com/jgromes/RadioLib/wiki/Default-configuration#sx126x---lora-modem

   For full API reference, see the GitHub Pages
   https://jgromes.github.io/RadioLib/


   Transmit digitalReads the IRQ pin until it is set.
   TransmitInterrupt attaches the function to it. Doesn't seem to trigger?
*/

// include the library
#include <RadioLib.h>

// SX1262 has the following connections:
#define NSS                             10
#define DIO1                            2
#define NRST                            9
#define BUSY                            8
SX1262 radio = new Module(NSS, DIO1, NRST, BUSY);

// or using RadioShield
// https://github.com/jgromes/RadioShield
//SX1262 radio = RadioShield.ModuleA;

// save transmission state between loops
int transmissionState = ERR_NONE;

void setup() {
  Serial.begin(115200);

  // Sometimes it requires this?
  //pinMode(DIO1, INPUT_PULLUP);        

  // initialize SX1262 with default settings
  Serial.print(F("[SX1262] Initializing ... "));
  int state = radio.begin(915.0, 125.0, 9, 7, 0x12, 14);
  //int state = radio.begin(915.0, 7.8, 12, 7, 0x12, 22);
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }

  // Set the current limit
  Serial.print(F("[SX1262] Setting current limit ... "));
  //radio.setCurrentLimit(240.0);
  radio.setCurrentLimit(60.0);
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }

  // Set RF switch pins
  //radio.setRfSwitchPins(4, 7);
  radio.setRfSwitchPins(7,6);

  // set the function that will be called
  // when packet transmission is finished
  radio.setDio1Action(setFlag);

  // start transmitting the first packet
  Serial.print(F("[SX1262] Sending first packet ... "));

  // you can transmit C-string or Arduino string up to
  // 256 characters long
  transmissionState = radio.startTransmit("Hello World!");

  // you can also transmit byte array up to 256 bytes long
  /*
    byte byteArr[] = {0x01, 0x23, 0x45, 0x67,
                      0x89, 0xAB, 0xCD, 0xEF};
    state = radio.startTransmit(byteArr, 8);
  */
}

// flag to indicate that a packet was sent
volatile bool transmittedFlag = false;

// disable interrupt when it's not needed
volatile bool enableInterrupt = true;

// this function is called when a complete packet
// is transmitted by the module
// IMPORTANT: this function MUST be 'void' type
//            and MUST NOT have any arguments!
void setFlag(void) {
  // check if the interrupt is enabled
  if(!enableInterrupt) {
    return;
  }

  // we sent a packet, set the flag
  transmittedFlag = true;
}

void loop() {
  // check if the previous transmission finished
  if(transmittedFlag) {
    // disable the interrupt service routine while
    // processing the data
    enableInterrupt = false;

    // reset flag
    transmittedFlag = false;

    if (transmissionState == ERR_NONE) {
      // packet was successfully sent
      Serial.println(F("transmission finished!"));

      // NOTE: when using interrupt-driven transmit method,
      //       it is not possible to automatically measure
      //       transmission data rate using getDataRate()

    } else {
      Serial.print(F("failed, code "));
      Serial.println(transmissionState);

    }

    // wait a second before transmitting again
    delay(1000);

    // send another one
    Serial.print(F("[SX1262] Sending another packet ... "));

    // you can transmit C-string or Arduino string up to
    // 256 characters long
    transmissionState = radio.startTransmit("Hello World!");

    // you can also transmit byte array up to 256 bytes long
    /*
      byte byteArr[] = {0x01, 0x23, 0x45, 0x67,
                        0x89, 0xAB, 0xCD, 0xEF};
      int state = radio.startTransmit(byteArr, 8);
    */

    // we're ready to send more packets,
    // enable interrupt service routine
    enableInterrupt = true;
  }
}
