void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop() {
  // read teh input on analog pin 0;
  int sensorValue = analogRead(A0);

  //calculate the actual voltage at sensor out
  float voltage = sensorValue * (5.0 / 1023.0);

  //Print the value of the analog input
  Serial.print(sensorValue);
  Serial.print(",");

  //Print the UV index value. As per the specifications for the sensor,
  //this is done by dividing the sensor output voltage by 0.1
  Serial.println(voltage/0.1);
  delay(100); //delay inbetween for stability 
}
