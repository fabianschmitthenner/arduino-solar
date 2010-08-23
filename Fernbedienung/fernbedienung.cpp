/*
    Copyright (C) 2010 Fabian Schmitthenner

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
#include "fernbedienung.h"
#include <pins_arduino.h>
#include <MessageTypes.h>

Fernbedienung::Fernbedienung()
: lcd (LCD_RS, LCD_ENABLE, LCD_D0, LCD_D1, LCD_D2, LCD_D3), menu(lcd, *this)
{
  addMethod(this, &Fernbedienung::readPackages, 0);
  addMethod(this, &Fernbedienung::sendData, 1000);
  addMethod(this, &Fernbedienung::checkBatteryState, 60000);
  addMethod(&menu, &Menu::interval, 2000);
  addMethod(this, &Fernbedienung::controlButtons, 0);
  lcd.begin(16, 2);
  lcd.print ("Initialisiere");
}

void Fernbedienung::error(uint8_t arg1)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print ("Fehler XBee Nr.");
  lcd.setCursor(0,1);
  lcd.print (arg1, DEC);
}



void Fernbedienung::readData(uint8_t* data, uint8_t length)
{
  menu.setConnection(true);
  if (data[0] == Message::FromSolarboat::DATA_FROM_SOLARBOAT && length == 6)
  {
    // show data
    unsigned long strom = data[1] | (data[2] << 8);
    //FIXME: set correct factor
    strom *= 26394;
    strom /= 1000;
    unsigned long spannung = data[3] | (data[4] << 8);
    // 0 = 0V, 1024=(5V*(14,7)/4,7)=3.127*5=15,635
    // ==> 0,015267V pro Stelle
    spannung *= 15271;
    spannung /= 1000; // spannung in mV
    menu.setActualMPPTType (data[5]);
    menu.writeStromAndSpannung(spannung, strom);
  }
  else if (data[0] == Message::FromSolarboat::BATTERY)
  {
    int value = data[1] | (data[2] << 8);
    menu.setSolarBattery(value);
  }
  else if (data[0] == Message::FromSolarboat::SEND_MPPT) // NOWLOOK
  {
    if (data[1] == 'r')
      menu.setMPPTDiff (data[2]);
  }
  else if (data[0] == Message::FromSolarboat::RESPONSE_MPPT_INTERVAL)
  {
    unsigned int interval = data[1] | (data[2] << 8);
  }
#ifndef REALLY_WORLD
  else if (data[0] == '-')
    menu.setAction(-1);
  else if (data[0] == '+')
    menu.setAction(+1);
  else if (data[0] == 'R')
    menu.setExecute();
#endif
}

void Fernbedienung::connectionInterrupted()
{
  menu.setConnection(false);
}

void Fernbedienung::sendData()
{
  uint8_t data[3];
  
  data[0] = Message::ToSolarboat::POTI_DATA;
  data[1] = menu.getPotiValue(Menu::SPEED);
  data[2] = menu.getPotiValue(Menu::TURN);
  writeData(data, sizeof(data));
}

void Fernbedienung::checkBatteryState()
{
  int value = analogRead (BATTERY);
  if (value < MIN_BATTERY_VALUE)
    menu.setFernBattery();
}

void Fernbedienung::setMPPT(char mpptType)
{
  uint8_t data[2];
  data[0] = Message::ToSolarboat::CHANGE_MPPT_TYPE;
  data[1] = mpptType;
  writeData (data, 2);
}


void Fernbedienung::controlButtons()
{
  if (menu.isStarted())
  {
    steuerungX.control();
    if (steuerungX.isUp())
      menu.setAction(1);
    else if (steuerungX.isDown())
      menu.setAction(-1);
    
    steuerungY.control();
    if (steuerungY.isUp())
      menu.goUp();
    
    if (steuerungPress.isPressed())
      menu.setExecute();
  }
  else
  {
    if (steuerungPress.isPressed())
      menu.start();
    else
    {
      steuerungX.control();
      if (steuerungX.isUp())
      {
	setMPPT ((menu.getActualMPPTType() + 1) % Message::MPPT::COUNT);
	menu.setActualMPPTType(Message::MPPT::UNKNOWN);
      }
    }
  }
}
