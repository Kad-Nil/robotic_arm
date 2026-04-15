#include <Servo.h>

Servo liftServo;
Servo clawServo;

// --- CALIBRATED ANGLES (logical values) ---
const int LIFT_REACH = 20;   
const int LIFT_UP = 0;
const int CLAW_OPEN = 0;
const int CLAW_CLOSED = 140;

// Function to invert servo direction
int convertAngle(int angle) {
  return 180 - angle;
}

void setup() {
  Serial.begin(9600);
  
  liftServo.attach(7);
  clawServo.attach(4);
  
  Serial.println("System Initializing...");
  
  // Initial position
  liftServo.write(convertAngle(LIFT_UP));
  clawServo.write(CLAW_OPEN);
  delay(2000);

  Serial.println("Type 'r' to run one cycle");
}

void loop() {

  if (Serial.available() > 0) {
    char cmd = Serial.read();

    if (cmd == 'r') {
      Serial.println("Running one full cycle...");

      // --- SEQUENCE START ---
      Serial.println("1. Lowering Arm...");
      liftServo.write(convertAngle(LIFT_REACH));
      delay(1500);

      Serial.println("2. Closing Claw (Gripping)...");
      clawServo.write(CLAW_CLOSED);
      delay(1000);

      Serial.println("3. Lifting Object...");
      liftServo.write(convertAngle(LIFT_UP));
      delay(2000);

      Serial.println("4. Releasing Object...");
      clawServo.write(CLAW_OPEN);
      delay(1500);
      // --- SEQUENCE END ---

      Serial.println("Cycle complete. Waiting...");
    }
  }
}