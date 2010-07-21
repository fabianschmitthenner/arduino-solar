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


#include <XBee/XBee.h>
#include "Dispatcher.h"

#ifdef USE_XBEE_API

class MyXBee: public Dispatcheable
{ 
  public:
    const static int MAX_TIME_BETWEEN_TWO_REQUESTS = 100;
    
    MyXBee (const XBeeAddress64 &receiverAddress);
    /**
     this method has to be called repeatly, often enough,
     so that there doesn't happen a buffer overrun
    */
    void readPackages ();
    bool isConnected ()
    {
      return !connectionError && lastConnection;
    }
    
    void writeData (uint8_t *data, uint8_t length);        
    
    
  protected:
    virtual void error(uint8_t arg1) = 0;
    virtual void readData (uint8_t *data, uint8_t length) = 0;
    virtual void connectionInterrupted () = 0;
    
  private:
    XBeeAddress64 receiver;
    XBee xbee;
    unsigned long lastConnection;
    bool waitAck;
    bool connectionError;
};

#else

#undef START_BYTE
#undef ESCAPE
#define MyXBeeSerial MyXBee

class MyXBeeSerial: public Dispatcheable
{
  public:
    enum SpecialCharacters
    {
      START_BYTE = 200,
      ESCAPE = 201
    };
    
    enum ErrorMessages
    {
      NO_START_BYTE = 100,
      START_BYTE_INSIDE_MESSAGE = 101
    };
    
    const static int MAX_TIME_BETWEEN_TWO_REQUESTS = 100;
    
    MyXBeeSerial ();
    MyXBeeSerial (const XBeeAddress64 &);
    
    void readPackages();
    bool isConnected ();
    
    void writeData (uint8_t *data, uint8_t length);
    void writeEscaped(uint8_t arg1);
    
  protected:
    virtual void error(uint8_t arg1) = 0;
    virtual void readData (uint8_t *data, uint8_t length) = 0;
    virtual void connectionInterrupted () = 0;
    
  private:
    
    uint8_t package[100];
    int alredyRead;
    long unsigned int lastPackageRead;
    
    bool _isConnected;
};

#endif