//BIBLIOTECAS
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "DHTesp.h" 

//CONFIGUAÇÃO DA REDE
const char* ssid = "Wokwi-GUEST";
const char* password = "";

//CONFIGUAÇÃO MQTT NO QUBITRO (meu)
const char* mqtt_server = "broker.qubitro.com";
const int mqtt_port = 1883;
const char* mqtt_user = "7300729d-8b2c-42df-ae8e-64a1d00d8afd";
const char* mqtt_password = "174830626362457887007f42ec7d7594a22df9cced5b795013255ce1b271d0c39845247b3a52e116a396148c8c9f78d4512";
const char* mqtt_topic = "7300729d-8b2c-42df-ae8e-64a1d00d8afd";
const char* client_id = "7300729d-8b2c-42df-ae8e-64a1d00d8afd";

//DEFINE O PINO NO ESP32 entrada
   // sensor tanque
#define DHT_PIN 15 
DHTesp dht;

   //sensores plantação
#define DHT_PIN_1 16 
DHTesp dht1;

#define DHT_PIN_2 17 
DHTesp dht2;

#define DHT_PIN_3 18
DHTesp dht3;

#define DHT_PIN_4 19
DHTesp dht4;

//CONFIGUAÇÃO WIFI
WiFiClient espClient;
PubSubClient client(espClient);

//AJUSTE TEMPO DA MENSAGEM
unsigned long lastMsg = 0;
const long interval = 4000;

//CONFIGUAÇÃO WIFI
void setup_wifi() {
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado");
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());

  dht.setup(DHT_PIN, DHTesp::DHT22);
  dht1.setup(DHT_PIN_1, DHTesp::DHT22);
  dht2.setup(DHT_PIN_2, DHTesp::DHT22);
  dht3.setup(DHT_PIN_3, DHTesp::DHT22);
  dht4.setup(DHT_PIN_4, DHTesp::DHT22);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (client.connect(client_id, mqtt_user, mqtt_password)) {
      Serial.println("conectado!");
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > interval) {
    lastMsg = now;
  
    TempAndHumidity tempH = dht.getTempAndHumidity();
    TempAndHumidity tempH1 = dht1.getTempAndHumidity();
    TempAndHumidity tempH2 = dht2.getTempAndHumidity();
    TempAndHumidity tempH3 = dht3.getTempAndHumidity();
    TempAndHumidity tempH4 = dht4.getTempAndHumidity();
    
    const int length = 300;
    
    StaticJsonDocument<length> doc;
    StaticJsonDocument<length> doc2;
    /* sensor_tanque_PH, sensor_tanque_TEMP, sensor_plantacao_1_PH, PARA O PH É OUTRO SENOR
    sensor_plantacao_1_HUM,
     sensor_plantacao_2_PH, sensor_plantacao_2_HUM, sensor_plantacao_3_PH, sensor_plantacao_3_HUM,
     sensor_plantacao_4_PH, sensor_plantacao_4_HUM   
    */
    //tanque
    doc["sensor_tanque_TEMP"] = tempH.temperature;
    doc["sensor_tanque_HUM"] = tempH.humidity;

    //plantação
    doc["sensor_plantacao_1_TEMP"] = tempH1.temperature;
    doc["sensor_plantacao_1_HUM"] = tempH1.humidity;

    char buffer[length];
    serializeJson(doc, buffer);
    Serial.print("Enviando payload: ");
    Serial.println(buffer);
    client.publish(mqtt_topic, buffer);

    doc2["sensor_plantacao_2_TEMP"] = tempH2.temperature;
    doc2["sensor_plantacao_2_HUM"] = tempH2.humidity;

    doc2["sensor_plantacao_3_TEMP"] = tempH3.temperature;
    doc2["sensor_plantacao_3_HUM"] = tempH3.humidity;

    doc2["sensor_plantacao_4_TEMP"] = tempH4.temperature;
    doc2["sensor_plantacao_4_HUM"] = tempH4.humidity;

    char buffer2[length];
    serializeJson(doc2, buffer2);
    Serial.print("Enviando payload: ");
    Serial.println(buffer2);
    client.publish(mqtt_topic, buffer2);

    
  }
}