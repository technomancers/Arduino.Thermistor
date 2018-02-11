#include <thermistor.h>

Thermistor thermistor = Thermistor::FromCelsius(A0, 10000, 25, 4300, 10000);

void setup()
{
  Serial.begin(9600);
  analogReference(EXTERNAL);  //Reduce the noise on the analog read
}

void loop()
{
  Serial.print(thermistor.temperatureC());
  delay(250);
}
