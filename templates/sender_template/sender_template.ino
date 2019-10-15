#include<XBee.h>

XBee xbee = XBee();
//uint8_t payload[]={0,0,0,0,0};
//XBeeAddress64 addr64 = XBeeAddress64(0x0013a200,0x414ea696);
//ZBTxRequest tx = ZBTxRequest(addr64,payload,sizeof(payload));

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  xbee.setSerial(Serial);
}

void loop() {
  
// Create an array for holding the data you want to send.
uint8_t payload[] = { 'H', 'i' };

// Specify the address of the remote XBee (this is the SH + SL)
XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x414ea696);

// Create a TX Request
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));

// Send your request
xbee.send(zbTx);
delay(1000);
}
