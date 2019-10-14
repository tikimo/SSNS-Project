// defines pins numbers
const int trigPin = 6;
const int echoPin = 5;

// defines variables
long duration;
int distance;

class MessageFormat {
  public:
  struct Telemetry {
    String key;
    float value;
    String unit;
  };
};

void sendTelemetry(MessageFormat::Telemetry t) {
  Serial.println((String) t.key + ": " + t.value + " " + t.unit);

  // TODO implement RF logic
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
    "Distance",
    (float) distance,
    "cm"
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