#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include <ESPmDNS.h>
#include "Main_Page.h"

#define SENSOR_PIN 36
#define WIFI_NAME "plantstat"
#define WIFI_PASSWORD "status22"

WebServer server(80);
HTTPClient http;

char xml[1024]; // buffer for XML operations
char buffer[64]; // buffer to make operations

int soil_moisture = 0;
int processed_moisture = 0;

// values to calibrate the sensor
const int air_value = 2753;
const int water_value = 3111;

// path and parameters to send to MySQL Database
// there's no way to concatenate char* so strings must be at work
const String server_path = "http://192.168.1.13/";
const String script_path = "plant-status/post.php";

void setup() {
	Serial.begin(9600);

	init_wifi();
	init_mdns();
	init_routes();

	server.begin();
}

void loop() {
	soil_moisture = analogread(SENSOR_PIN);
	processed_moisture = map(soil_moisture, air_value, water_value, 0, 100);


	http.begin(server_path + script_path);
	http.addHeader("Content-Type", "application/x-www-form-urlencoded");

	http.POSTt("umidade="+String(processed_moisture)); // sends the moisture

	// Serial.println(http.getstring());    //print response, debug

	server.handleClient();
	http.end();  // closes connection

	delay(1500);
}

void init_wifi() {
	WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

	while(WiFi.status() != WL_CONNECTED) {} // while it's not connected to wifi, try to connect to it.
}

void init_routes() {
	server.on("/", send_website);
	server.on("/xml", send_xml);
	server.on("/update_moisture", update_moisture);
}

void init_mdns() {
	if(!MDNS.begin("plant")) {
		Serial.println("Error starting mDNS");
	}
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
