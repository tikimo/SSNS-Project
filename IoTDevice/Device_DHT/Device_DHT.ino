
#include "DHT.h"
#include <XBee.h>
#include <stdio.h>

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

// Xbee init
XBee xbee = XBee();
// Payload is {hwid, t|h|p, value, value, unit}
uint8_t payload[5] = {0,0,0,0,0};
// SH + SL Address of receiving XBee
XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x414ea696);
ZBTxStatusResponse txStatus = ZBTxStatusResponse();


class MessageFormat {
  public:
  struct DHT_Message {
    float humidity;
    float temperature;
  };

  struct Telemetry {
    char key;
    float value;
    char unit;
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
  Serial.println((String) t.key + ": " + t.value + " " + t.unit);

  // Payload edit
  payload[0] = 1; // HWid
  payload[1] = t.key; 
  payload[2] = (int) t.value / 10;
  payload[3] = (int) t.value % 10;
  payload[4] = t.unit;

  // RF Logic
  ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
  xbee.send(zbTx);
}

void setup() {
  Serial.begin(9600);

  dht.begin();
  xbee.setSerial(Serial);
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Read Sensor 
  MessageFormat::DHT_Message sensorData = readSensor(dht);

  // Send humidity data as telemetry
  MessageFormat::Telemetry humidityTelemetry = {
    'h',
    sensorData.humidity,
    '%'
  };
  sendTelemetry(humidityTelemetry);

  // Send temperature data as telemetry
  MessageFormat::Telemetry temperatureTelemetry = {
    't',
    sensorData.temperature,
    'C'
  };
  sendTelemetry(temperatureTelemetry);
}





