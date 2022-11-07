#include <Arduino.h>
#include <UbidotsESPMQTT.h>
#include <PubSubClient.h>
#define TOKEN "BBFF-B7JDnpp3jZ8xyxXPIJ6J9LbGEdWyVc"
#define WIFINAME "Luigi"
#define WIFIPASS "fuvo8846"

Ubidots client(TOKEN);

void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Mensagem Recebida [");
  Serial.print(topic);Serial.print("] ");
  for (int i=0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setup() {
  // put your setup code here, to run once:
  client.setDebug(true);
  Serial.begin(9600);
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected())
  {
    client.reconnect();
  }
  float pot = analogRead(A0);
  client.add("temperatura", pot);
  client.ubidotsPublish("Potenciometro");
  client.loop();
  delay(400);

}