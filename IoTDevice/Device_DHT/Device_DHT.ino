
#include "DHT.h"
#include <stdio.h>

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

class MessageFormat {
  public:
  struct DHT_Message {
    float humidity;
    float temperature;
  };

  struct Telemetry {
    String key;
    float value;
  };
};

MessageFormat::DHT_Message readSensor(DHT dht) {
  MessageFormat::DHT_Message data = {dht.readHumidity(), dht.readTemperature()};
  if (isnan(data.humidity) || isnan(data.temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return {0, 0};
  } else {
    return data;
  }
}

void sendTelemetry(MessageFormat::Telemetry t) {
  Serial.println((String) t.key + ": " + t.value);

  // TODO implement RF logic
}


void setup() {
  Serial.begin(9600);

  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Read Sensor 
  MessageFormat::DHT_Message sensorData = readSensor(dht);

  // Send humidity data as telemetry
  MessageFormat::Telemetry humidityTelemetry = {
    "Humidity",
    sensorData.humidity
  };
  sendTelemetry(humidityTelemetry);

  // Send temperature data as telemetry
  MessageFormat::Telemetry temperatureTelemetry = {
    "Temperature",
    sensorData.temperature
  };
  sendTelemetry(temperatureTelemetry);
}





