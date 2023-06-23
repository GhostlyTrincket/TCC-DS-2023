#include <WiFi.h>
//#include <ArduinoJson>

const char* wifi_name = "HOMERSIMPSON";
const char* wifi_password = "4D2A1BC2";
String header;

WiFiServer server(8080);

//http://10.1.1.100:8123/


void setup() {
  Serial.begin(9600);

  Serial.print("Conectando em: ");
  Serial.println(wifi_name);
  
  WiFi.begin(wifi_name,wifi_password);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print('.');
  }

  Serial.print("\nConectado a rede:");
  Serial.println(WiFi.localIP());
  
  server.begin();
}

void loop() {
  WiFiClient cliente = server.available();

    if(cliente) {
        Serial.println("Cliente novo.");

        String linhaAtual = "";
        while(cliente.connected()) {
          if(cliente.available()) {
              char character = cliente.read();

              Serial.write(character);
              header += character;
              /*
                se o caractere a ser lido for o fim de linha e o comprimento da linhaAtual
                for 0, então esse é o fim do pedido HTTP do cliente
              */
              if(character == '\n') {
                if(linhaAtual.length() == 0) {
                    cliente.println("HTTP/1.1 200 OK");
                    cliente.println("Content-type:text/html");
                    cliente.println("Connection: close");
                    cliente.println();

                    cliente.println("<!DOCTYPE html><html>");
                    cliente.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
                    cliente.println("<body><h1>ESP32 Web Server - Hello World!</h1></body></html>");
                    cliente.println();

                    cliente.println();
                    break;
                } else {
                  linhaAtual = "";
                }
              } else if(character == '\r') {
                  linhaAtual += character;
              }
          }
        }

        header = "";
        cliente.stop();

        Serial.println("Cliente desconectado!");
    } 
}
