#include <WiFi.h>

const char* wifi_name = "WIFI_NAME";
const char* wifi_password = "WIFI_PASSWORD";

WiFiServer server(8080);

void setup() {
  Serial.begin(115200);
  
  Serial.println("Conectando em " +String(wifi_name));
  WiFi.begin(wifi_name,wifi_password);
  
  while(WiFi.status() != WL_CONNECTED) {
    delay(500); //wait half second to try to connect to the wifi again
    Serial.print('.');
  }
  
  Serial.println("WiFi conectado! Vá para " +String(WiFi.localIP()));
  
  //server.begin();
}

void loop() {

}
