#include <stdio.h>

void setup() {
  Serial.begin(9600);

  // Setup inputs
  
}

// the loop function runs over and over again forever
void loop() {

}

// Sends the telemetry to Serial with nice logging
void sendTelemetry(String key, String value) {
  String messageLog = (String) "[ INFO ] " + key + ": " + value;
  Serial.println(messageLog);
}
