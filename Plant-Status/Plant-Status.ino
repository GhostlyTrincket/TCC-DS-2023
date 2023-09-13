#include <WiFi.h>
#include <WebServer.h>
//#include <HTTPClient.h>
#include "Main_Page.h"

#define SENSOR_PIN 36
#define WIFI_NAME "plant-status"
#define WIFI_PASSWORD "status22"

WebServer server(80);
//HTTPClient http; // to make POST request from esp32

char xml[2048]; // buffer for XML operationschar
char buffer[64]; // buffer to make operations

int soil_moisture = 0;
int processed_moisture = 0;

// values to calibrate the sensor
const int air_value = 2753;
const int water_value = 3111;

// path and parameters to send to MySQL Database
// since there is no operator+ to const char*, Strings must do
// const String path_name = "http://192.168.1.109/"
// const String script_name = "send_moisture.php";
// const String load = "moisture="

void setup() {
	Serial.begin(9600);

	init_wifi();
	init_routes();

	server.begin();
}

void loop() {
	soil_moisture = analogRead(SENSOR_PIN);
	processed_moisture = map(soil_moisture, air_value, water_value, 0, 100);

	server.handleClient();
}

void init_wifi() {
	WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

	while(WiFi.status() != WL_CONNECTED) {} // while it's not connected to wifi, try to connect to it.

	Serial.print("\nGo to: ");
	Serial.println(WiFi.localIP());
}

void init_routes() {
	server.on("/", send_website);
	server.on("/xml", send_xml);
	server.on("/update_moisture", update_moisture);
}

void send_website() {
	server.send(200, "text/html", MAIN_PAGE);
}

void send_xml() {
	strcpy(xml, "<?xml version = '1.0'?>\n<Data>\n"); // xml header

	sprintf(buffer, "<Moisture>%d</Moisture>", processed_moisture);
	strcat(xml, buffer);

	strcat(xml, "</Data>\n");

	server.send(200, "text/xml", xml);
}

void update_moisture() {
	String server_arg = server.arg("value"); // argument to be used in the URL

	strcpy(buffer, "");
	sprintf(buffer, "%d", processed_moisture);
	sprintf(buffer, buffer);

	server.send(200, "text/plain", buffer);
}
