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

#include <Printer.h>
#include <Servo.h>
#include <avr/pgmspace.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define X_AXIS    A0  //Joystick pin connections
#define Y_AXIS    A1
#define Z_AXIS    11

Printer iprint = Printer();

const byte _A_array[96] PROGMEM = //sets write or no write for each point
{
	0, 0, 1, 1, 0, 0,
	0, 1, 1, 1, 1, 0,
	0, 1, 1, 1, 1, 0,
	0, 1, 0, 0, 1, 0,
	0, 1, 0, 0, 1, 0,
	1, 1, 0, 0, 1, 1,
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1
};

const byte _B_array[96] PROGMEM = 
{
	1, 1, 1, 1, 0, 0,
	1, 1, 0, 1, 1, 0,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 1, 1, 0,
	1, 1, 1, 1, 0, 0,
	1, 1, 0, 1, 1, 0,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 1, 1, 0,
	1, 1, 1, 1, 0, 0
};

const byte _C_array[96] PROGMEM = 
{
	0, 0, 1, 1, 0, 0,
	0, 1, 1, 1, 1, 0,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 0, 1,
	1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 1,
	1, 1, 0, 0, 1, 1,
	0, 1, 1, 1, 1, 0,
	0, 0, 1, 1, 0, 0
};

const byte _D_array[96] PROGMEM = 
{
	1, 1, 1, 1, 0, 0,
	1, 1, 1, 1, 1, 0,
	1, 1, 0, 0, 1, 0,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 0,
	1, 1, 1, 1, 1, 0,
	1, 1, 1, 1, 0, 0
};

const byte _E_array[96] PROGMEM = 
{
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
	1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 0,
	1, 1, 1, 1, 1, 0,
	1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1
};

const byte _F_array[96] PROGMEM = 
{
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
	1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 0,
	1, 1, 1, 1, 1, 0,
	1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0
};

const byte _G_array[96] PROGMEM = 
{
	0, 0, 1, 1, 0, 0,
	0, 1, 1, 1, 1, 0,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 0, 1,
	1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0,
	1, 1, 0, 1, 1, 1,
	1, 1, 0, 1, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	0, 1, 1, 1, 1, 0,
	0, 0, 1, 1, 0, 0
};

const byte _H_array[96] PROGMEM = 
{
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1
};

const byte _I_array[96] PROGMEM = 
{
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
	0, 0, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0,
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1
};

const byte _J_array[96] PROGMEM = 
{
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
	0, 0, 0, 1, 1, 0,
	0, 0, 0, 1, 1, 0,
	0, 0, 0, 1, 1, 0,
	0, 0, 0, 1, 1, 0,
	0, 0, 0, 1, 1, 0,
	0, 0, 0, 1, 1, 0,
	1, 1, 0, 1, 1, 0,
	1, 1, 0, 1, 1, 0,
	0, 1, 1, 1, 1, 0,
	0, 0, 1, 1, 0, 0
};

const byte _K_array[96] PROGMEM = 
{
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 1, 1, 1,
	1, 1, 0, 1, 1, 1,
	1, 1, 0, 1, 1, 0,
	1, 1, 1, 1, 1, 0,
	1, 1, 1, 1, 0, 0,
	1, 1, 1, 1, 0, 0,
	1, 1, 0, 1, 1, 0,
	1, 1, 0, 1, 1, 0,
	1, 1, 0, 1, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1
};

const byte _L_array[96] PROGMEM = 
{
	1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1
};

const byte _M_array[96] PROGMEM = 
{
	1, 0, 0, 0, 0, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 1, 1, 1, 1,
	1, 0, 1, 1, 0, 1,
	1, 0, 1, 0, 0, 1,
	1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1
};

const byte _N_array[96] PROGMEM = 
{
	1, 0, 0, 0, 0, 1,
	1, 1, 0, 0, 0, 1,
	1, 1, 0, 0, 0, 1,
	1, 1, 1, 0, 0, 1,
	1, 1, 1, 0, 0, 1,
	1, 1, 1, 1, 0, 1,
	1, 0, 1, 1, 0, 1,
	1, 0, 1, 1, 1, 1,
	1, 0, 0, 1, 1, 1,
	1, 0, 0, 1, 1, 1,
	1, 0, 0, 0, 1, 1,
	1, 0, 0, 0, 1, 1
};

const byte _O_array[96] PROGMEM = 
{
	0, 0, 1, 1, 0, 0,
	0, 1, 1, 1, 1, 0,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	0, 1, 1, 1, 1, 0,
	0, 0, 1, 1, 0, 0
};

const byte _P_array[96] PROGMEM = 
{
	1, 1, 1, 1, 0, 0,
	1, 1, 1, 1, 1, 0,
	1, 1, 0, 0, 1, 0,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 0,
	1, 1, 1, 1, 1, 0,
	1, 1, 1, 1, 0, 0,
	1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0
};

const byte _Q_array[96] PROGMEM = 
{
	0, 0, 1, 1, 0, 0,
	0, 1, 1, 1, 1, 0,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 1, 0, 1,
	0, 1, 1, 0, 1, 0,
	0, 0, 1, 1, 0, 1
};

const byte _R_array[96] PROGMEM = 
{
	1, 1, 1, 1, 0, 0,
	1, 1, 1, 1, 1, 0,
	1, 1, 0, 0, 1, 0,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 0,
	1, 1, 1, 1, 1, 0,
	1, 1, 1, 1, 0, 0,
	1, 1, 0, 1, 1, 0,
	1, 1, 0, 1, 1, 0,
	1, 1, 0, 1, 1, 0,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1
};

const byte _S_array[96] PROGMEM = 
{
	0, 1, 1, 1, 1, 0,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	0, 1, 1, 0, 1, 0,	
	0, 1, 1, 0, 0, 0,
	0, 0, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0,
	0, 0, 0, 1, 1, 0,
	0, 1, 0, 1, 1, 0,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	0, 1, 1, 1, 1, 0
};

const byte _T_array[96] PROGMEM = 
{
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
	0, 0, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0
};

const byte _U_array[96] PROGMEM = 
{
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	0, 1, 1, 1, 1, 0,
	0, 0, 1, 1, 0, 0
};

const byte _V_array[96] PROGMEM = 
{
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	0, 1, 0, 0, 1, 0,
	0, 1, 0, 0, 1, 0,
	0, 1, 0, 0, 1, 0,
	0, 1, 1, 1, 1, 0,
	0, 0, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0
};

const byte _W_array[96] PROGMEM = 
{
	1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1,
	1, 0, 0, 1, 0, 1,
	1, 0, 1, 1, 0, 1,
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 1
};

const byte _X_array[96] PROGMEM = 
{
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	0, 1, 0, 0, 1, 0,
	0, 1, 1, 1, 1, 0,
	0, 0, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0,
	0, 1, 1, 1, 1, 0,
	0, 1, 0, 0, 1, 0,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1
};
const byte _Y_array[96] PROGMEM = 
{
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	1, 1, 0, 0, 1, 1,
	0, 1, 1, 1, 1, 0,
	0, 0, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0
};

const byte _Z_array[96] PROGMEM = 
{
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 1, 1,
	0, 0, 0, 1, 1, 1,
	0, 0, 1, 1, 1, 0,
	0, 0, 1, 1, 0, 0,
	0, 0, 1, 1, 0, 0,
	0, 1, 1, 1, 0, 0,
	1, 1, 1, 0, 0, 0,
	1, 1, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1
};

int  Xvalue = 0;           
int  Yvalue = 0;
boolean Zvalue = 0;
boolean Z;

byte select = 0;	//value of the current letter
byte column = 0;	//value of the letter slot
const char cur = '^';	//cursor to put under current character
const byte D = 150;

char letterArray[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ ";		//characters to display (and print)
char printArray[17];	       //length of lcd +1
byte printArray_length = 1;

void setup(){
  iprint.X_motor(2, 4, 3);     //sets motors to printer library
  iprint.Y_motor(5, 7, 6);
  iprint.init();
  lcd.init();                  //start up the lcd
  lcd.backlight();
  lcd.clear(); 
  pinMode(Z_AXIS, INPUT);
  digitalWrite(Z_AXIS, HIGH);  //pull up resistor on
}

void loop(){
	iprint.PrintHead_Set(false);  //raises pen
	while(Z == false)              //sets LCD letter selection function
	{
		lcd_select();
	}
	print(printArray, printArray_length);
	Z = false;
  
}

void lcd_select()
{
	lcd.setCursor(column,1);        //print the cursor under the letter space
  lcd.print(cur);                 //and then move the cursor to that letter space
  lcd.setCursor(0,0);
  
  Xvalue = analogRead(X_AXIS);
  Yvalue = analogRead(Y_AXIS);
  Zvalue = digitalRead(Z_AXIS);
  
  Display();
  
  if(Yvalue > 600)  // Changes letter if Y Axis is moved up or down
  {
    select++;
    Display();
  }
  if(Yvalue < 400)  
  {
    select--;
    Display();
  }  
  if(select > 27)  // If moved past "Z", go to "A"
  {
    select = 1;
    Display();
  }
  if(select < 1)  // If moved behind "A", go to "Z"
  {
    select = 27;
    Display();
  }
  
  
  if((Xvalue > 600) && (column < 16))    // when stick moved right, move to next letter
  {                                      // but only if it isn't already on the far right
      select = 1;
	  printArray_length++;
      column++;
      constrain(column,0,15);
      Display();
  }
  if((Xvalue < 400) && (column > 0))    // when stick moved left, move back a letter
  {                                      // but only if it isn't already on the far left
      select = 1;
	  printArray_length++;
      column--;
      constrain(column,0,15);
      Display();
  }
  
  if(Zvalue == true)                   //sends letter string when joystick is clicked
  {  
    sender();
    Z = true;
  }
}

void Display()                         //prints characters on LCD screen
{
    delay(D);
    lcd.setCursor(column-1,1);
    lcd.print(" ");
    lcd.setCursor(column+1,1);
    lcd.print(" ");
    lcd.setCursor(column, 1);
    lcd.print(cur);
    lcd.setCursor(column, 0);
    lcd.print(letterArray[select]);
    printArray[column] = letterArray[select]; 
    
}

void sender()   //sends the string to motors and verifies that it was sent
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Now Printing...");
  delay(5000);
  lcd.clear();                    //clears LCD Screen
  lcd.setCursor(0,0);
  select=1;
  column=0;
}

void print(char myletter[], byte length)              //Organizes and starts pen movement based on 1s and 0s
{
	for(byte y = 0; y<=11; y++)
	{
		for(byte currentchar = 0; currentchar <= length; currentchar++)
		{
			for(byte x = 0; x<=5; x++)
			{
				switch(myletter[currentchar])
  				{
				case 'A':
					iprint.Writer(pgm_read_byte(&(_A_array[((6 * y)+x)])));
					break;
				case 'B':
					iprint.Writer(pgm_read_byte(&(_B_array[((6 * y)+x)])));
					break;
				case 'C':
					iprint.Writer(pgm_read_byte(&(_C_array[((6 * y)+x)])));
					break;
				case 'D':
					iprint.Writer(pgm_read_byte(&(_D_array[((6 * y)+x)])));
					break;
				case 'E':
					iprint.Writer(pgm_read_byte(&(_E_array[((6 * y)+x)])));
					break;
				case 'F':
					iprint.Writer(pgm_read_byte(&(_F_array[((6 * y)+x)])));
					break;
				case 'G':
					iprint.Writer(pgm_read_byte(&(_G_array[((6 * y)+x)])));
					break;
				case 'H':
					iprint.Writer(pgm_read_byte(&(_H_array[((6 * y)+x)])));
					break;
				case 'I':
					iprint.Writer(pgm_read_byte(&(_I_array[((6 * y)+x)])));
					break;
				case 'J':
					iprint.Writer(pgm_read_byte(&(_J_array[((6 * y)+x)])));
					break;
				case 'K':
					iprint.Writer(pgm_read_byte(&(_K_array[((6 * y)+x)])));
					break;
				case 'L':
					iprint.Writer(pgm_read_byte(&(_L_array[((6 * y)+x)])));
					break;
				case 'M':
					iprint.Writer(pgm_read_byte(&(_M_array[((6 * y)+x)])));
					break;
				case 'N':
					iprint.Writer(pgm_read_byte(&(_N_array[((6 * y)+x)])));
					break;
				case 'O':
					iprint.Writer(pgm_read_byte(&(_O_array[((6 * y)+x)])));
					break;
				case 'P':
					iprint.Writer(pgm_read_byte(&(_P_array[((6 * y)+x)])));
					break;
				case 'Q':
					iprint.Writer(pgm_read_byte(&(_Q_array[((6 * y)+x)])));
					break;
				case 'R':
					iprint.Writer(pgm_read_byte(&(_R_array[((6 * y)+x)])));
					break;
				case 'S':
					iprint.Writer(pgm_read_byte(&(_S_array[((6 * y)+x)])));
					break;
				case 'T':
					iprint.Writer(pgm_read_byte(&(_T_array[((6 * y)+x)])));
					break;
				case 'U':
					iprint.Writer(pgm_read_byte(&(_U_array[((6 * y)+x)])));
					break;
				case 'V':
					iprint.Writer(pgm_read_byte(&(_V_array[((6 * y)+x)])));
					break;
				case 'W':
					iprint.Writer(pgm_read_byte(&(_W_array[((6 * y)+x)])));
					break;
				case 'X':
					iprint.Writer(pgm_read_byte(&(_X_array[((6 * y)+x)])));
					break;
				case 'Y':
					iprint.Writer(pgm_read_byte(&(_Y_array[((6 * y)+x)])));
					break;
				case 'Z':
					iprint.Writer(pgm_read_byte(&(_Z_array[((6 * y)+x)])));
					break;
				case ' ':
					iprint.Step('X', 1, true, 750);
					break;
				default:
					digitalWrite(13, HIGH);
				}
			}
			iprint.PrintHead_Set(false);         //continues to next letter
			delay(75);
			iprint.Step('X',3,true,750);
		}
		iprint.PrintHead_Set(false);                 //returns to first point and goes down to next row
		iprint.Step('X',(12+((length-1)*9)),false,750);
		delay(250);
		iprint.Step('Y',1,false,750);
	}
	iprint.Step('Y',2,false,750);                        //moves to next row of letters
}
