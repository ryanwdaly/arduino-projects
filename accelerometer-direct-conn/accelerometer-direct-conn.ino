// Sketch that detects acceleration, orientation, and records the highest g force on each
//axis

int x, y, z; //used to store the accelleration readings

int X_axis = A4;
int Y_axis = A3;
int Z_axis = A2;

double largest_x, largest_y, largest_z;

double x_volt, y_volt, z_volt;
double x_g, y_g, z_g;
double zero_g_voltage;

double sensitivity = 0.100; // 0.300 V/g

char outstr[5]; //char arrays used to format the final results into a num with 1 dec.

const int groundpin = A1;             // analog input pin 4 -- ground 
                                      // Analog pins can be treated as digital pins. 
                                      // Analog pin 4 corresponds to digital pin 18.
const int powerpin = A5;              // analog input pin 5 -- voltage
                                      // Analog pin 5 corresponds to digital pin 19
                                    

void setup()
{
  pinMode(groundpin, OUTPUT);
  pinMode(powerpin, OUTPUT);
  digitalWrite(groundpin, LOW); //Low Deffines GND pin
  digitalWrite(powerpin, HIGH); //HIGH Defines power pin

  largest_x = 0;
  largest_y = 0;
  largest_z = 0;
  
  Serial.begin(9600);      // sets the serial port to 9600

  delay(1000);
  x = analogRead(X_axis);
  zero_g_voltage = x;
}

void loop()
{
  x = analogRead(X_axis);       // read analog input pin 0
  y = analogRead(Y_axis);       // read analog input pin 1
  z = analogRead(Z_axis);       // read analog input pin 1

  x_volt = x * 3.3 / 1023;
  y_volt = y * 3.3 / 1023;
  z_volt = z * 3.3 / 1023;

  x_g = (x_volt-zero_g_voltage) / sensitivity;
  y_g = (y_volt-zero_g_voltage) / sensitivity;
  z_g = (z_volt-zero_g_voltage) / sensitivity;

  if (largest_x < x_g)
    largest_x = x_g;

  if (largest_y < y_g)
    largest_y = y_g;

  if (largest_z < z_g)
    largest_z = z_g;
  
  Serial.print("G-forces are x, y, z, largest x-y-z: ");
  Serial.print(x, DEC);    // print the acceleration in the X axis
  Serial.print(" ");       // prints a space between the numbers
  Serial.print(y, DEC);    // print the acceleration in the Y axis
  Serial.print(" ");       // prints a space between the numbers
  Serial.print(z, DEC);  // print the acceleration in the Z axis
  Serial.print(", ");
  dtostrf(largest_x,3, 1, outstr);
  Serial.print(outstr);
  Serial.print(" - ");
  dtostrf(largest_y,3, 1, outstr);
  Serial.print(outstr);
  Serial.print(" - ");
  dtostrf(largest_z,3, 1, outstr);
  Serial.print(outstr);
  Serial.print(", zero G: ");
  Serial.println(zero_g_voltage);
  delay(100);              // wait 100ms for next reading
}
