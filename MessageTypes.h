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

#pragma once
#include "MessageData.h"

namespace Message
{

namespace FromSolarboat {

const char DATA_FROM_SOLARBOAT = 'd';
const char BATTERY = 'b';
const char SEND_MPPT = '1';
const char RESPONSE_MPPT_INTERVAL = 'I';
};

MESSAGE_DATA_3(FromSolarboat::DATA_FROM_SOLARBOAT, unsigned int, strom, unsigned int, spannung, char, mpptType);
MESSAGE_DATA_1(FromSolarboat::BATTERY, unsigned int, data);
MESSAGE_DATA_2(FromSolarboat::SEND_MPPT, const char, subtype, char, data);

namespace ToSolarboat {

const char REQUEST_BATTERY = 'B';
const char POTI_DATA = 'P';
const char CHANGE_MPPT_TYPE = 'M';
const char REQUEST_MPPT = 'm';
const char REQUEST_MPPT_INTERVAL = 'i';
const char SET_MPPT_INTERVAL = '8';

};


// MPPT types

namespace MPPT
{

const char NOMPPT = 0;
const char PERTURBEANDOBSERVE = 1;
const char ESTIMATEPERTURB = 2;
const char ESTIMATEESTIMATEPERTURB = 3;
const char COUNT = 4;
const char UNKNOWN = 255;

};


};