//Bare wiznet functions: http://www.ermicro.com/blog/?p=1773
// Perhaps try those later?
// Then someone seems to have cut it down to what they needed: https://forum.arduino.cc/t/lightweight-ethernet/149487/13
// Try that ^^^ !!!


/*
  echo.pde:
  echo incoming packets back to the wire after changing their mac addresses
*/

#include <SPI.h>         // needed for Ethernet library communication with the W5100 (Arduino ver>0018)
#include <Ethernet.h>
#include <utility/w5100.h>

SOCKET s; // our socket that will be opened in RAW mode
byte rbuf[1500+14]; // receive buffer (1500 not 150 for both)
//byte sbuf[150+14]; // send buffer 
int rbuflen; // length of data to receive
//int sbuflen; // length of data to send

void setup() {
 Serial.begin(115200);
 Serial.println("Started up");
  // initialize the w5100 chip and open a RAW socket  
  W5100.init();
  Serial.println("Finished init");
  W5100.writeSnMR(s, SnMR::MACRAW); 
  Serial.println("Finished writeSnMR");
  W5100.execCmdSn(s, Sock_OPEN);
  Serial.println("Finished execCmdSn. Looping");
  
}

void loop() {
  // check if we have received something
  rbuflen = W5100.getRXReceivedSize(s);
  
  if (rbuflen>0) {
    // receive packet 
    W5100.recv_data_processing(s, rbuf, rbuflen);
    W5100.execCmdSn(s, Sock_RECV);
   
    // offset 2 ... because the first two bytes in 'rbuf' contain the packet length
    //sbuflen=rbuflen-2; // we will be sending 'sbuflen' bytes across the wire 
    
    //for (int i=0; i<= 5; i++) sbuf[i]=255; // changing dst mac address to broadcast 
    //for (int i=6; i<=11; i++) sbuf[i]=random(256); // changing src mac address to a random address 


    // filling send buffer with some data from the receive buffer ...
    Serial.println("Received: ");
    for (int i=0; i<rbuflen; i++) {
        Serial.write(rbuf[i]);
      //sbuf[i]=rbuf[i+2]; // offset 2 !!!   
    }
  
    // sending packet (this would be done for data received via serial)
    //W5100.send_data_processing(s, sbuf, sbuflen);
    //W5100.execCmdSn(s, Sock_SEND_MAC);
  }
  
}
