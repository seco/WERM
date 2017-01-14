/* CLIP CONNECTIONS
 * column 1, lower: common ground
 * column 23, upper: 4.5V DC in
 * column 39, lower: 12V DC in
 * column 45, lower: DC motor 1, negative
 * column 45, upper: DC motor 2, negative
 * column 50, lower: DC motor 1, positive
 * column 50, upper: DC motor 2, positive
 */

/* NOTES
 * yellow wire: REPLACE with resistor!!!
 * GREEN LED: PWM strength of MOTOR 1
 * RED LED: PWM strength of MOTOR 2
 */

/*libraries*/
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/*Wifi*/
#define WLAN_SSID       "NETGEAR47"
#define WLAN_PASS       "unusualearth866"

//#define WLAN_SSID       "Amauro4848147"
//#define WLAN_PASS       "ms0ynfgmymyzs"

/*MQTT*/
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "yomafacio"
#define AIO_KEY         "29cc2bb000f14985a994cb093d27d779"

/*Pin Definitions*/
#define PWM_MOTOR1_PIN 4 //GPIO4, or D2
#define LEG1_MOTOR1_PIN 5 //GPIO5, or D1
#define LEG2_MOTOR1_PIN 16 //GPIO16, or D0
#define PWM_MOTOR2_PIN 14 //GPIO14, or D5
#define LEG1_MOTOR2_PIN 2 //GPIO2, or D4
#define LEG2_MOTOR2_PIN 0 //GPIO0, or D3

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_USERNAME, AIO_KEY);

/*Feed*/
Adafruit_MQTT_Subscribe testMotor1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/testMotor1");
Adafruit_MQTT_Subscribe testMotor2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/testMotor2");
/* FEED INFO (assuming using yomafacio's MQTT broker account):
 * testMotor1:
 *   slider that ranges from the values -1000 to 1000
 *   controls motor 1
 *   direction dictated by value
 * testMotor2:
 *   slider that ranges from the values -1000 to 1000
 *   controls motor 2
 *   direction dictated by value
 * testForward:
 *   toggle between ON and OFF
 *   controls motor 1 and 2
 *   both motors forward
 * testBackward:
 *   toggle between ON and OFF
 *   controls motor 1 and 2
 *   both motors backward
 * testYawLeft:
 *   toggle between ON and OFF
 *   controls motor 1 and 2
 *   motor 1 backward, motor 2 forward
 * testYawRight:
 *   toggle between ON and OFF
 *   controls motor 1 and 2
 *   motor 1 forward, motor 2 backward
 */

void setup() {
  // initialize pins
  pinMode(PWM_MOTOR1_PIN, OUTPUT);
  pinMode(LEG1_MOTOR1_PIN, OUTPUT);
  pinMode(LEG1_MOTOR1_PIN, OUTPUT);
  pinMode(PWM_MOTOR2_PIN, OUTPUT);
  pinMode(LEG1_MOTOR2_PIN, OUTPUT);
  pinMode(LEG1_MOTOR2_PIN, OUTPUT);
  
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
  mqtt.subscribe(&testMotor1);
  mqtt.subscribe(&testMotor2);
}

void loop() { 

  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // this is our 'wait for incoming subscription packets' busy subloop
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    // Check if it's the testMotor1 feed
    if (subscription == &testMotor1) {
      Serial.print(F("Motor1: "));
      Serial.println((char *)testMotor1.lastread);
      
      int speed_motor1 = atoi((const char *)testMotor1.lastread);
      if(speed_motor1 > 0) {
        digitalWrite(LEG1_MOTOR1_PIN, LOW);
        digitalWrite(LEG2_MOTOR1_PIN, HIGH);
      }/* else {
        digitalWrite(LEG1_MOTOR1_PIN, HIGH);
        digitalWrite(LEG2_MOTOR1_PIN, LOW);
        speed_motor1 = -speed_motor1;
      }*/
      analogWrite(PWM_MOTOR1_PIN,speed_motor1);
    }
    
    // Check if it's the testMotor2 feed
    if (subscription == &testMotor2) {
      Serial.print(F("Motor2: "));
      Serial.println((char *)testMotor2.lastread);
      
      int speed_motor2 = atoi((const char *)testMotor2.lastread);
      if(speed_motor2 > 0) {
        digitalWrite(LEG1_MOTOR2_PIN, LOW);
        digitalWrite(LEG2_MOTOR2_PIN, HIGH);
      }/* else {
        digitalWrite(LEG1_MOTOR2_PIN, HIGH);
        digitalWrite(LEG2_MOTOR2_PIN, LOW);
        speed_motor2 = -speed_motor2;
      }*/
      analogWrite(PWM_MOTOR2_PIN,speed_motor2);
    }

    //add more feeds
  }
  
  // ping the server to keep the mqtt connection alive
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }

} //end loop()


// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
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
