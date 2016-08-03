/* 
 * File:   HelperSerial.h
 * Author: ericson
 *
 * Created on July 15, 2016, 4:08 PM
 */

#ifndef _ADVANCED_SERIAL_H_
#define	_ADVANCED_SERIAL_H_
#include <Arduino.h>

class AdvancedSerial {
private:
    HardwareSerial *serial;
    char buffer[512];
    unsigned long timeout;
    int baudrate;

public:
    AdvancedSerial();
    AdvancedSerial(HardwareSerial *obj);
    AdvancedSerial(HardwareSerial *obj, int baudrate);
    AdvancedSerial(HardwareSerial *obj, int baudrate, int timeout_millis);
    HardwareSerial* getSerial();
    String readUntil(char character);
    void waitDataBlocker();
    boolean waitDataWithTimeout();
    void cleanBuffer();
    int timeoutRead();
    String read();
    long getTimeout();
    void setTimeout(long timeout);
    int getBaudrate();
    void setBaudrate(int baudrate);

};



#endif	

