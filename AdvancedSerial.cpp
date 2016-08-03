#include "AdvancedSerial.h"
#include "Millis.h"

AdvancedSerial::AdvancedSerial() {
}

AdvancedSerial::AdvancedSerial(HardwareSerial* obj, int baudrate, int timeout_millis) {
    this->serial = obj;
    this->baudrate = baudrate;
    this->serial->begin(baudrate);
    this->timeout = timeout_millis;
    memset(buffer, 0, sizeof (buffer));
}

AdvancedSerial::AdvancedSerial(HardwareSerial* obj, int baudrate) {
    this->serial = obj;
    this->baudrate = baudrate;
    this->serial->begin(baudrate);
    this->timeout = 10000;
    memset(buffer, 0, sizeof (buffer));
}

AdvancedSerial::AdvancedSerial(HardwareSerial *obj) {
    this->serial = obj;
    this->baudrate = 9600;
    this->serial->begin(9600);
    this->timeout = 10000;
    memset(buffer, 0, sizeof (buffer));
}

HardwareSerial* AdvancedSerial::getSerial() {
    return serial;
}

String AdvancedSerial::readUntil(char character) {
    memset(buffer, -1, sizeof (buffer));
    serial->readBytesUntil(character, buffer, sizeof (buffer));
    String res;
    int i = 0;
    int c = buffer[i];
    while (c >= 0) {
        res += (char) c;
        i++;
        c = buffer[i];
    }
    return res;
}

void AdvancedSerial::waitDataBlocker() {
    while (serial->available() == 0) {
    }
}

boolean AdvancedSerial::waitDataWithTimeout() {
    Millis ctime = Millis();
    Millis now;
    boolean flag = false;
    while (serial->available() == 0 && flag == false) {
        now = Millis();
        if ((now - ctime) > timeout) {
            flag = true;
            return false;
        }
    }
    return true;
}

int AdvancedSerial::timeoutRead() {
    int c;
    Millis _startMillis = Millis();
    Millis now;
    do {
        c = serial->read();
        if (c >= 0) {
            return c;
        }
        now = Millis();
    } while (now - _startMillis < 10);
    return -1;
}

String AdvancedSerial::read() {
    String ret;
    int c = timeoutRead();
    while (c >= 0) {
        ret += (char) c;
        c = timeoutRead();
    }
    return ret;
}

long AdvancedSerial::getTimeout() {
    return this->timeout;
}

void AdvancedSerial::setTimeout(long timeout) {
    this->timeout = timeout;
}

void AdvancedSerial::cleanBuffer() {
    this->serial->flush();
    this->read();
}















