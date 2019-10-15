
#include <XBee.h>

// defines pins numbers
const int trigPin = 6;
const int echoPin = 5;

// Xbee init
XBee xbee = XBee();
// Payload is {hwid, t|h|p, tens, ones, unit}
unsigned char payload[5] = {0,0,0,0,0};
// SH + SL Address of receiving XBee
XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x414ea696);
ZBTxStatusResponse txStatus = ZBTxStatusResponse();


// defines variables
long duration;
int distance;

class MessageFormat {
  public:
  struct Telemetry {
    char key;
    float value;
    char unit;
  };
};

void sendTelemetry(MessageFormat::Telemetry t) {
  Serial.println((String) t.key + ": " + t.value + " " + t.unit);

  t.value = t.value > 99 ? 99 : t.value;

  int first_digit = ((int) t.value) / 10;
  int second_digit = ((int) t.value) % 10;

  // Payload edit
  payload[0] = '2'; // HWid
  payload[1] = t.key;
  payload[2] = '0' + first_digit;
  payload[3] = '0' + second_digit;
  payload[4] = t.unit;

  // RF Logic
  ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
  xbee.send(zbTx);
}

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}

void loop() {
  delay(2000);
  int distance = getDistanceInCm();

  MessageFormat::Telemetry telemetry = {
    'p',
    (float) distance,
    'c'
  };
  
  sendTelemetry(telemetry);
}

// Reads the proximity sensor 
int getDistanceInCm() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration*0.034/2;
  
  return distance;
}