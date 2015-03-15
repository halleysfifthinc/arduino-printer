// arduino-printer
//
// Copyright (c) 2013 Allen Hill (halleysfifthinc)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef Printer_h
#define Printer_h

#include <Arduino.h>
#include <Servo.h>

class Printer
{
public:
	Printer();
	void X_motor(byte enablePin, byte dirPin, byte stepPin);
	void Y_motor(byte enablePin, byte dirPin, byte stepPin);
	void init();
	void Pulse(byte motorPin, byte dirPin, boolean Dir, int stepperSpeed);
	void Step(char motor, int units, boolean direction, int Speed);
	void Return();
	void Print(char myletters[17]);
	void PrintHead_Set(byte state);
	void Writer(byte);

	byte X_enablePin;
	byte Y_enablePin;

	Servo _PrintHead;

private:

	byte _X_stepPin;
	byte _X_dirPin;
	byte _X_direction;

	byte _Y_stepPin;
	byte _Y_dirPin;
	byte _Y_direction;

	byte _X_stepperCalibrationConstant;
	byte _Y_stepperCalibrationConstant;

	byte _Servo_Up;
	byte _Servo_Down;
};

#endif
