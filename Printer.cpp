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


#include <Arduino.h>
#include <Printer.h>
#include <Servo.h>

Printer::Printer() {  /*Nothing to construct. */ }

void Printer::X_motor(byte enablePin, byte dirPin, byte stepPin)
{
	X_enablePin = enablePin;
	_X_dirPin = dirPin;
	_X_stepPin = stepPin;
}

void Printer::Y_motor(byte enablePin, byte dirPin, byte stepPin)
{
	Y_enablePin = enablePin;
	_Y_dirPin = dirPin;
	_Y_stepPin = stepPin;
}

void Printer::init()
{
	_PrintHead.attach(9);
	_Servo_Up = 100;
	_Servo_Down = 89;

	pinMode(X_enablePin, OUTPUT);
	pinMode(_X_stepPin, OUTPUT);
	pinMode(_X_dirPin, OUTPUT);
	pinMode(Y_enablePin, OUTPUT);
	pinMode(_Y_stepPin, OUTPUT);
	pinMode(_Y_dirPin, OUTPUT);
	pinMode(13, OUTPUT);

	digitalWrite(X_enablePin, HIGH);
	digitalWrite(Y_enablePin, HIGH);

	_X_stepperCalibrationConstant = 11;
	_Y_stepperCalibrationConstant = 12;
}

void Printer::Pulse(byte motorPin, byte dirPin, boolean Dir, int stepperSpeed)  //Make sure to first enable the motor if directly 
{																				//using this command.
	digitalWrite(dirPin, Dir);
	digitalWrite(motorPin, HIGH);
	delayMicroseconds(stepperSpeed);
	digitalWrite(motorPin, LOW);
	delayMicroseconds(stepperSpeed);
}

void Printer::Step(char motor, int units, boolean direction, int Speed)
{
	switch (motor)
	{
	case 'X':
		digitalWrite(X_enablePin, LOW);
		for(int i = 0; i<(units*_X_stepperCalibrationConstant); i++)
		{
			Pulse(_X_stepPin, _X_dirPin, direction, Speed);
		}
		digitalWrite(X_enablePin, HIGH);
		break;
	case 'Y':
		digitalWrite(Y_enablePin, LOW);
		for(int i = 0; i<(units*_Y_stepperCalibrationConstant); i++)
		{
			Pulse(_Y_stepPin, _Y_dirPin, direction, Speed);
		}
		digitalWrite(Y_enablePin, HIGH);
		break;
	}
}

void Printer::PrintHead_Set(byte state)
{
	if (state > 0)
	{
		_PrintHead.write(_Servo_Down);
	}
	if(state == 0)
	{
		_PrintHead.write(_Servo_Up);
	}

}

/************************************************************************/
/*    Sets the print head and advances the motors one unit forward.     */
/************************************************************************/
void Printer::Writer(byte current)
{
	if(current > 0)
	{
		_PrintHead.write(_Servo_Down);
	}
	if(current == 0)
	{
		_PrintHead.write(_Servo_Up);
	}
	Step('X', 1, true, 750);
	delay(100);
}
