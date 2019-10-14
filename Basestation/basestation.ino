#include <stdio.h>

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on 
  sendTelemetry("Led", "ON");
  Serial.println("asdad");
  delay(100);                       // wait for half a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off 
  delay(100);                       // wait for half a second
}

// Sends the telemetry to Serial with nice logging
void sendTelemetry(String key, String value) {
  String messageLog = (String) "[" + millis() + "] " + key + ": " + value;
  Serial.println(messageLog);
}
