#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

const char* ssid = "arduino-stat";
const char* password = "status22";
String server_name = "http://192.168.137.142:8080/update-sensor";

void setup() {
  Serial.begin(9600);

  Serial.print("Conectando em: ");
  Serial.println(ssid);
  
  WiFi.begin(ssid,password);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print('.');
  }

  Serial.print("\nConectado a rede:");
  Serial.println(WiFi.localIP());
}

void loop() {
//192.168.137.142
  if(WiFi.status() == WL_CONNECTED) {
     Serial.println("Cliente novo.");

     HTTPClient http;

     String server_path = server_name + "?temperature=24.66";

     http.begin(server_path.c_str());
     int response_code = http.GET();

     if (response_code > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(response_code);
        
        String payload = http.getString();
        Serial.println(payload);
      } else {
        Serial.print("Error code: ");
        Serial.println(response_code);
      }

      http.end();
  } else {
    Serial.println("Wifi desconnected");
  }
}
//     while(cliente.connected()) {
//       if(cliente.available()) {
//           char character = cliente.read();
//
//              Serial.write(character);
//              header += character;
//              
//              /*
//                se o caractere a ser lido for o fim de linha e o comprimento da linhaAtual
//                for 0, então esse é o fim do pedido HTTP do cliente
//              */
//
//              if(character == '\n') {
//                if(linhaAtual.length() == 0) {
//                    cliente.println("HTTP/1.1 200 OK");
//                    cliente.println("Content-type:text/html");
//                    cliente.println("Connection: close");
//                    cliente.println();
//
//                    //aqui vai ser aonde o sensor entra.
//
//                    cliente.println();
//                    break;
//                } else {
//                  linhaAtual = "";
//                }
//              } else if(character == '\r') {
//                  linhaAtual += character;
//              }
//          }
//        }
//
//        header = "";

//        Serial.println("Cliente desconectado!");
