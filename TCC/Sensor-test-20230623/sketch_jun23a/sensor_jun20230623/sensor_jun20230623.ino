#define PIN_AOUT_PLACE 36

void setup() {
  Serial.begin(9600);
}

void loop() {
  int moisture_value = analogRead(PIN_AOUT_PLACE);

  Serial.print("The moisture: ");
  Serial.println(moisture_value);

  delay(500);
}
