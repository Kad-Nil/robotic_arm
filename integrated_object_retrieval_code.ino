#include <Servo.h>

const int liftPin = 7;     // Main shoulder lift
const int gripperPin = 4;   // The claw
const int trigPin = 12;
const int echoPin = 13;

Servo liftServo;
Servo gripperServo;

int distanceThreshold = 10; 
bool hasObject = false; // Tracks if we are currently transporting

void setup() {
  Serial.begin(9600);
  liftServo.attach(liftPin);
  gripperServo.attach(gripperPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initial State
  liftServo.write(45);      
  gripperServo.write(90); 
}

void loop() {
  // If we don't have an object, look for one
  if (!hasObject) {
    long distance = getDistance();
    
    if (distance > 0 && distance <= distanceThreshold) {
      Serial.println("Object Found! Picking up...");
      performRetrieval();
      hasObject = true; // Lock the state so we don't repeat pickup
    } else {
      // Keep searching/driving
      liftServo.write(90);
      gripperServo.write(90);
    }
  } 
  // If we HAVE an object, stay in transport mode
  else {
    Serial.println("Transporting to Dock... Sensor ignored.");
    liftServo.write(90);     // Keep arm at transport height
    gripperServo.write(180); // Keep grip tight
    
    // Logic for dropping at the dock
    if (Serial.read() == 'd') { 
       performDrop();
       hasObject = false; // Reset to searching
    }
  }
}

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return (duration * 0.034) / 2;
}

void performRetrieval() {
  liftServo.write(160); // Reach down
  delay(800);
  gripperServo.write(180); // Close claw
  delay(1000);
  liftServo.write(90); // Lift to transport height
  delay(800);
}

void performDrop() {
  Serial.println("At Dock. Releasing object...");
  liftServo.write(160); // Lower to ground
  delay(800);
  gripperServo.write(90); // Open claw
  delay(1000);
  liftServo.write(45); // Return to search pose
  delay(800);
}