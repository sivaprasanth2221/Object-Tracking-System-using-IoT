// Adjust these values to reflect the position of the X and Y ultrasonic sensors.
const int A = 20; // cm - Distance range for X sensor
const int B = 15; // cm - Distance range for Y sensor

// Hardware connections
const int trigPinX = 2, echoPinX = 3;
const int trigPinY = 5, echoPinY = 6;
const int servoPinL = 8;
const int servoPinR = 10;

// Function to measure distance using ultrasonic sensor
float measureDist(int trigPin, int echoPin) {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH) / 2.0 * 0.0343;  
}

// Function to control servo motor angles
void servoControl(int servoPin, int angle) {
  unsigned int duration;
  duration = map(angle, 0, 180, 544, 2400); // Map angle to servo pulse width
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(duration);
  digitalWrite(servoPin, LOW);
}

// Setup function to initialize pins and set servos to 90 degrees initially
void setup() {
  Serial.begin(9600);
  pinMode(trigPinX, OUTPUT);
  pinMode(echoPinX, INPUT);
  pinMode(trigPinY, OUTPUT);
  pinMode(echoPinY, INPUT);
  pinMode(servoPinL, OUTPUT);
  pinMode(servoPinR, OUTPUT);

  // Set both servos to the default 90-degree position
  servoControl(servoPinL, 90);
  servoControl(servoPinR, 90);
}

// Main loop function
void loop() {
  float distX = measureDist(trigPinX, echoPinX);
  float distY = measureDist(trigPinY, echoPinY);
  

  // Constrain distance values and map them to servo positions
  int limDistX = (int)constrain(distX, 4, 2 * A);
  int pos = map(limDistX, 4, 2 * A, 45, 135);
  Serial.println(distX);
  Serial.println(distX);

  int limDistY = (int)constrain(distY, 4, B);
  int diff = map(limDistY, 4, B, 40, 0);

  // If object is out of range, keep servos in default position
  if (distX > 2 * A || distY > B) {
    pos = 90;
    diff = 0;
  }

  // Control servo motors based on calculated positions
  servoControl(servoPinL, pos - diff);
  servoControl(servoPinR, pos + diff);

  delay(60); // Delay for stability
}
