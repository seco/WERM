/* CLIP CONNECTIONS
 * row Y: common ground
 * row W: 4.5V DC in
 * row Z: 12V DC in
 * column 31, lower: DC motor 1, negative
 * column 31, upper: DC motor 2, negative
 * column 33, lower: DC motor 1, positive
 * column 33, upper: DC motor 2, positive
 */

/*libraries*/
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/*Wifi*/
#define WLAN_SSID       "guest-SDUHSD"
#define WLAN_PASS       ""
//#define WLAN_SSID       "NETGEAR47"
//#define WLAN_PASS       "unusualearth866"

/*MQTT*/
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "CeilingBot"
#define AIO_KEY         "f93aa0c6bcd04926b790004d481e3000"

/*Pin Definitions*/
#define PWM_MOTOR_PIN 0 //GPIO0, or D3
#define LEG1_MOTOR1_PIN 2 //GPIO2, or D4
#define LEG1_MOTOR2_PIN 5 //GPIO5, or D1
#define COMMON_LEG2_PIN 13 //GPIO13, or D7

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_USERNAME, AIO_KEY);

/*Feed*/
Adafruit_MQTT_Subscribe testForward = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/testForward");
Adafruit_MQTT_Subscribe testBackward = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/testBackward");
Adafruit_MQTT_Subscribe testYawLeft = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/testYawLeft");
Adafruit_MQTT_Subscribe testYawRight = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/testYawRight");
/* FEED INFO (assuming using yomafacio's MQTT broker account):
 * testForward:
 *   slider that ranges from the values 0 to 10000
 *   values represent duration (milliseconds) of action
 *   controls motor 1 and 2
 *   both motors forward
 * testBackward:
 *   slider that ranges from the values 0 to 10000
 *   values represent duration (milliseconds) of action
 *   controls motor 1 and 2
 *   both motors backward
 * testYawLeft:
 *   slider that ranges from the values 0 to 1000
 *   values represent duration (milliseconds) of action
 *   controls motor 1 and 2
 *   motor 1 backward, motor 2 forward
 * testYawRight:
 *   slider that ranges from the values 0 to 1000
 *   values represent duration (milliseconds) of action
 *   controls motor 1 and 2
 *   motor 1 forward, motor 2 backward
 */

void setup() {
  
  // initialize pins
  pinMode(PWM_MOTOR_PIN, OUTPUT);
  pinMode(LEG1_MOTOR1_PIN, OUTPUT);
  pinMode(LEG1_MOTOR2_PIN, OUTPUT);
  pinMode(COMMON_LEG2_PIN, OUTPUT);
  
  Serial.begin(9600);

  // Connect to WiFi access point.
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
  
  //Setup the MQTT subscription
  mqtt.subscribe(&testForward);
  mqtt.subscribe(&testBackward);
  mqtt.subscribe(&testYawLeft);
  mqtt.subscribe(&testYawRight);
}

void loop() { 

  //ensure the connection to the MQTT server is alive
  MQTT_connect();

  //wait for incoming subscription packets subloop
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    //note: using a switch loop does not work, must use if/else
    if (subscription == &testForward) {
      Serial.print(F("testForward update duration: "));
      Serial.println((char *)testForward.lastread);
      int duration_forward = atoi((const char *)testForward.lastread);
      digitalWrite(LEG1_MOTOR1_PIN, HIGH); //low
      digitalWrite(LEG1_MOTOR2_PIN, HIGH); //low
      digitalWrite(COMMON_LEG2_PIN, HIGH); //high
      analogWrite(PWM_MOTOR_PIN, 1000);
      delay(duration_forward);
      analogWrite(PWM_MOTOR_PIN, 0);
      bufferNull();
    } else if (subscription == &testBackward) {
      Serial.print(F("testBackward update duration: "));
      Serial.println((char *)testBackward.lastread);
      int duration_backward = atoi((const char *)testBackward.lastread);
      digitalWrite(LEG1_MOTOR1_PIN, LOW); //high
      digitalWrite(LEG1_MOTOR2_PIN, LOW); //high
      digitalWrite(COMMON_LEG2_PIN, LOW); //low
      analogWrite(PWM_MOTOR_PIN, 1000);
      delay(duration_backward);
      analogWrite(PWM_MOTOR_PIN, 0);
      bufferNull();
    } else if (subscription == &testYawLeft) {
      Serial.print(F("testYawLeft update duration: "));
      Serial.println((char *)testYawLeft.lastread);
      int duration_left = atoi((const char *)testYawLeft.lastread);
      digitalWrite(LEG1_MOTOR1_PIN, HIGH); //low
      digitalWrite(LEG1_MOTOR2_PIN, LOW);  //high
      digitalWrite(COMMON_LEG2_PIN, LOW);  //low
      analogWrite(PWM_MOTOR_PIN, 1000);
      delay(duration_left);
      analogWrite(PWM_MOTOR_PIN, 0);
      bufferNull();
    } else if (subscription == &testYawRight) {
      Serial.print(F("testYawRight update duration: "));
      Serial.println((char *)testYawRight.lastread);
      int duration_right = atoi((const char *)testYawRight.lastread);
      digitalWrite(LEG1_MOTOR1_PIN, LOW);  //high
      digitalWrite(LEG1_MOTOR2_PIN, HIGH); //low
      digitalWrite(COMMON_LEG2_PIN, LOW);  //low
      analogWrite(PWM_MOTOR_PIN, 1000);
      delay(duration_right);
      analogWrite(PWM_MOTOR_PIN, 0);
      bufferNull();
    }
  }
  
  // ping the server to keep the mqtt connection alive
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }

} //end loop()

//function to null output values as necessary to prevent short circuits
void bufferNull() {
  Serial.println("buffering");
  digitalWrite(LEG1_MOTOR1_PIN, HIGH); //low
  digitalWrite(LEG1_MOTOR2_PIN, HIGH); //low
  digitalWrite(COMMON_LEG2_PIN, LOW); //low
  analogWrite(PWM_MOTOR_PIN, 0);
  delay(2000);
  Serial.println("end buffering");
  
}

// function to connect and reconnect as necessary to the MQTT server.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
