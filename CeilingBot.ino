/* CLIP CONNECTIONS
 * row Y: common ground
 * row W: 4.5V DC in
 * row Z: 12V DC in
 * column 31, lower: DC motor 1, negative
 * column 31, upper: DC motor 2, negative
 * column 33, lower: DC motor 1, positive
 * column 33, upper: DC motor 2, positive
 */
 
/*Pin Definitions*/
#define PWM_MOTOR_PIN 0 //GPIO0, or D3
#define LEG1_MOTOR1_PIN 2 //GPIO2, or D4
#define LEG1_MOTOR2_PIN 5 //GPIO5, or D1
#define COMMON_LEG2_PIN 13 //GPIO13, or D7

void setup() {
  // initialize pins
  pinMode(PWM_MOTOR_PIN, OUTPUT);
  pinMode(LEG1_MOTOR1_PIN, OUTPUT);
  pinMode(LEG1_MOTOR2_PIN, OUTPUT);
  pinMode(COMMON_LEG2_PIN, OUTPUT);
  
  Serial.begin(9600);
}

void loop() { 
  Serial.println("testForward Initiating...");
  digitalWrite(LEG1_MOTOR1_PIN, HIGH);
  digitalWrite(LEG1_MOTOR2_PIN, HIGH);
  digitalWrite(COMMON_LEG2_PIN, LOW);
  analogWrite(PWM_MOTOR_PIN, 1000);
  delay(5000);
  bufferNull();
  Serial.println("testBackward Initiating...");
  digitalWrite(LEG1_MOTOR1_PIN, LOW);
  digitalWrite(LEG1_MOTOR2_PIN, LOW);
  digitalWrite(COMMON_LEG2_PIN, HIGH);
  analogWrite(PWM_MOTOR_PIN, 1000);
  delay(5000);
  bufferNull();
  Serial.println("testYawLeft Initiating...");
  digitalWrite(LEG1_MOTOR1_PIN, LOW);
  digitalWrite(LEG1_MOTOR2_PIN, HIGH);
  digitalWrite(COMMON_LEG2_PIN, LOW);
  analogWrite(PWM_MOTOR_PIN, 1000);
  delay(5000);
  bufferNull();
  Serial.println("testYawRight Initating...");
  digitalWrite(LEG1_MOTOR1_PIN, HIGH);
  digitalWrite(LEG1_MOTOR2_PIN, LOW);
  digitalWrite(COMMON_LEG2_PIN, LOW);
  analogWrite(PWM_MOTOR_PIN, 1000);
  delay(5000);
  bufferNull();
}

void bufferNull() {
  Serial.println("buffering...");
  digitalWrite(LEG1_MOTOR1_PIN, LOW);
  digitalWrite(LEG1_MOTOR2_PIN, LOW);
  digitalWrite(COMMON_LEG2_PIN, LOW);
  analogWrite(PWM_MOTOR_PIN, 0);
  delay(2000);
}

