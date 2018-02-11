/*
A library for using Thermistors
Copyright (C) 2018  Technomancers

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "Arduino.h"
#include "thermistor.h"

Thermistor::Thermistor(int pin, float nominalResistance, float nominalTemperature, float b, float seriesResistor)
{
  _pin = pin;
  _nomRes = nominalResistance;
  _nomTemp = nominalTemperature;
  _b = b;
  _seriesResistor = seriesResistor;
}

Thermistor Thermistor::FromKelvin(int pin, float nominalResistance, float nominalTemperature, float b, float seriesResistor)
{
  return Thermistor(pin, nominalResistance, nominalTemperature, b, seriesResistor);
}

Thermistor Thermistor::FromCelsius(int pin, float nominalResistance, float nominalTemperature, float b, float seriesResistor)
{
  return Thermistor(pin, nominalResistance, nominalTemperature + 273.15, b, seriesResistor);
}

Thermistor Thermistor::FromFahrenheit(int pin, float nominalResistance, float nominalTemperature, float b, float seriesResistor)
{
  return Thermistor(pin, nominalResistance, (nominalTemperature + 459.67) * (5.0 / 9.0), b, seriesResistor);
}

float Thermistor::temperatureK()
{
  float res = _resistance();
  float sh = res / _nomRes;
  sh = log(sh);
  sh /= _b;
  sh += 1.0 / _nomTemp;
  return 1.0 / sh;
}

float Thermistor::temperatureC()
{
  return temperatureK() - 273.15;
}

float Thermistor::temperatureF()
{
  return temperatureK() * (9.0/5.0) - 459.67;
}

float Thermistor::_resistance()
{
  float average = 0;
  for (int i = 0; i < _numSamples; i++)
  {
    average += analogRead(_pin);
    if (i != _numSamples - 1)
    {
      delayMicroseconds(10);
    }
  }
  average /= (float)_numSamples;
  average = 1023.0 / average - 1.0;
  average = _seriesResistor / average;
  return average;
}

void Thermistor::setNumSamples(int numSamples)
{
  _numSamples = numSamples;
}
