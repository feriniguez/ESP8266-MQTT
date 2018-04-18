
// V 5.0 For IF's configured for receiving data through MQTT.

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
// Update these with values suitable for your network.

const char* ssid = "iFL";
const char* password = "XxxxxxxxXxX";
const char* mqtt_server = "172.17.75.250";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
int GPIO2 = 2;
int D_1 = 5;
int D_2 = 4;
int D_5 = 14;
int D_6 = 12;

IPAddress ip(192, 168, 1, 113);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  pinMode(GPIO2, OUTPUT);
  pinMode(D_1, OUTPUT);
  pinMode(D_2, OUTPUT);
  pinMode(D_5, OUTPUT);
  pinMode(D_6, OUTPUT);
  digitalWrite(GPIO2,HIGH);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  ArduinoOTA.setPort(8266);
 // ArduinoOTA.setPassword("XxxxxxxxXxX");
  ArduinoOTA.onStart([] () {
  //      String type;
    //            if (ArduinoOTA.getCommand() == U_FLASH)
      //                  type = "sketch";
        //        else
          //              type ="filesystem";
        //Serial.println("Start updating " + type);
        });
  ArduinoOTA.onEnd([] () {
        Serial.printf("\nEnd");
        });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  ////////////////////////////////////////////////////
 if (strcmp(topic,"room/Testing")==0){
  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(D_1,HIGH);
        digitalWrite(GPIO2,LOW);
        delay (100);
        digitalWrite(GPIO2,HIGH);
  }
  if ((char)payload[0] == '3') {
    digitalWrite(D_1, LOW);
        digitalWrite(GPIO2,LOW);
        delay (50);
        digitalWrite(GPIO2,HIGH);
        delay (50);
        digitalWrite(GPIO2,LOW);
        delay (50);
        digitalWrite(GPIO2,HIGH);                
  }
  if ((char)payload[0] == '2') {
    digitalWrite(D_1,HIGH);
        digitalWrite(GPIO2,LOW);
        delay (100);
        digitalWrite(GPIO2,HIGH);
  }
  if ((char)payload[0] == '4') {
    digitalWrite(D_1, LOW);
        digitalWrite(GPIO2,LOW);
        delay (100);
        digitalWrite(GPIO2,HIGH);
        delay (50);
        digitalWrite(GPIO2,LOW);
        delay (50);
        digitalWrite(GPIO2,HIGH);
  }
  if ((char)payload[0] == '5') {
    digitalWrite(D_1,HIGH);
        digitalWrite(GPIO2,LOW);
        delay (100);
        digitalWrite(GPIO2,HIGH);
  }
  if ((char)payload[0] == '7') {
    digitalWrite(D_1, LOW);
        digitalWrite(GPIO2,LOW);
        delay (100);
        digitalWrite(GPIO2,HIGH);
        delay (50);
        digitalWrite(GPIO2,LOW);
        delay (50);
        digitalWrite(GPIO2,HIGH);
  }
  if ((char)payload[0] == '6') {
    digitalWrite(D_1,HIGH);
        digitalWrite(GPIO2,LOW);
        delay (100);
        digitalWrite(GPIO2,HIGH);
  }
  if ((char)payload[0] == '8') {
    digitalWrite(D_1, LOW);
        digitalWrite(GPIO2,LOW);
        delay (100);
        digitalWrite(GPIO2,HIGH);
        delay (50);
        digitalWrite(GPIO2,LOW);
        delay (50);
        digitalWrite(GPIO2,HIGH);
  }
 }
}
 ////////////////////////////////////////////////////////// This part is for fan and light. Check
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      // client.publish("outTopic", "hello world");
      client.publish("casa/despacho/temperatura", "Enviando el primer mensaje");
      // ... and resubscribe
      client.subscribe("room/Testing");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
  ArduinoOTA.handle();
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 75, "hello world #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("casa/despacho/temperatura", msg);
  }
}

