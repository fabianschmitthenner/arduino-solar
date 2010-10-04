#pragma once
#include "../wireless.h"
#include "Menu.h"

namespace Fernbedienung{

extern MyXBee xbee;
extern Dispatcher dispatcher;
extern Menu menu;


// Konstanten
const uint8_t LCD_RS = 12;
const uint8_t LCD_ENABLE = 11;
const uint8_t LCD_D0 = 5;
const uint8_t LCD_D1 = 4;
const uint8_t LCD_D2 = 3;
const uint8_t LCD_D3 = 2;

const uint8_t POT_SPEED = 0;
const uint8_t POT_TURN = 1;
const uint8_t BATTERY = 3;
const int MIN_BATTERY_VALUE = 570;

const uint8_t POT_STEUERUNG_X = 4;
const uint8_t POT_STEUERUNG_Y = 2;
const uint8_t STEUERUNG_PRESS = 10;


};