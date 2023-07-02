#include <ArduinoJson.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  StaticJsonDocument<200> buffer;

//Em JSON numeros devem ter, também, aspas.
//Em JSON, também, se deve escapar certas letras.
 char message_to_parse[] = "{\"SensorType\": \"Dampness\", \"Value\": \"10\"}";

//para obter as informações do JSON utilize esta função.
//para transformar informações em JSON use serielazeJson.
  deserializeJson(buffer,message_to_parse);

  const char* value_to_read = buffer["SensorType"];

  Serial.println(value_to_read);

  StaticJsonDocument<200> buffer2;

//Para criar jsons basta fazer o seguinte:
  buffer2["jolyne"] = "kujo";

//para mostrar os dados que foram transformador em JSON, faça o seguinte: 
  serializeJson(buffer2,Serial);
}
