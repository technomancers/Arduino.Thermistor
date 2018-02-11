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
#ifndef thermistor_h
#define thermistor_h

#include "Arduino.h"

class Thermistor
{
public:
  static Thermistor FromKelvin(int pin, float nominalResistance, float nominalTemperature, float b, float seriesResistor);
  static Thermistor FromCelsius(int pin, float nominalResistance, float nominalTemperature, float b, float seriesResistor);
  static Thermistor FromFahrenheit(int pin, float nominalResistance, float nominalTemperature, float b, float seriesResistor);
  float temperatureK();
  float temperatureC();
  float temperatureF();
  void setNumSamples(int numSamples);
protected:
  Thermistor(int pin, float nominalResistance, float nominalTemperature, float b, float seriesResistor);
private:
  float _resistance();
  int _pin;
  float _seriesResistor;
  float _nomRes;
  float _nomTemp;
  float _b;
  int _numSamples = 5;
};

#endif
