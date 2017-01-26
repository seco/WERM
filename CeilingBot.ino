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

/*Method Definitions*/
#define TESTFORWARD 1
#define TESTBACKWARD 2
#define TESTYAWLEFT 3
#define TESTYAWRIGHT 4
/* FEED INFO (assuming using yomafacio's MQTT broker account):
 * testForward:
 *   controls motor 1 and 2
 *   both motors forward
 * testBackward:
 *   controls motor 1 and 2
 *   both motors backward
 * testYawLeft:
 *   controls motor 1 and 2
 *   motor 1 stop, motor 2 forward
 * testYawRight:
 *   controls motor 1 and 2
 *   motor 1 forward, motor 2 stop
 */

//METHOD TO RUN (refer above for constant names)
int method = 2;

void setup() {
  // initialize pins
  pinMode(PWM_MOTOR_PIN, OUTPUT);
  pinMode(LEG1_MOTOR1_PIN, OUTPUT);
  pinMode(LEG1_MOTOR2_PIN, OUTPUT);
  pinMode(COMMON_LEG2_PIN, OUTPUT);
  
  Serial.begin(9600);
  Serial.println(method);
}

void loop() { 
    if (method == 1) {
      Serial.println("testForward Initiating...");
      digitalWrite(LEG1_MOTOR1_PIN, HIGH);
      digitalWrite(LEG1_MOTOR2_PIN, HIGH);
      digitalWrite(COMMON_LEG2_PIN, LOW);
      analogWrite(PWM_MOTOR_PIN, 1000);
    } else if (method == 2) {
      Serial.println("testBackward Initiating...");
      digitalWrite(LEG1_MOTOR1_PIN, LOW);
      digitalWrite(LEG1_MOTOR2_PIN, LOW);
      digitalWrite(COMMON_LEG2_PIN, HIGH);
      analogWrite(PWM_MOTOR_PIN, 1000);
    } else if (method == 3) {
      Serial.println("testYawLeft Initiating...");
      digitalWrite(LEG1_MOTOR1_PIN, LOW);
      digitalWrite(LEG1_MOTOR2_PIN, HIGH);
      digitalWrite(COMMON_LEG2_PIN, LOW);
      analogWrite(PWM_MOTOR_PIN, 1000);
    } else if (method == 4) {
      Serial.println("testYawRight Initating...");
      digitalWrite(LEG1_MOTOR1_PIN, HIGH);
      digitalWrite(LEG1_MOTOR2_PIN, LOW);
      digitalWrite(COMMON_LEG2_PIN, LOW);
      analogWrite(PWM_MOTOR_PIN, 1000);
    }
    delay(100000);
}
