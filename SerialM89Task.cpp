/* 
 * File:   SerialM89Task.cpp
 * Author: ericson
 * 
 * Created on July 22, 2016, 11:36 AM
 */

#include "SerialM89Task.h"

extern HardwareSerial Serial;

SerialM89Task::SerialM89Task(M95* deviceM95, unsigned long crontime) : Task(crontime){
    this->deviceM95 = deviceM95;
}

void SerialM89Task::run() {
    if(deviceM95->getSerial()->available()){
        Serial.write(deviceM95->getSerial()->read());
    }
    if(Serial.available()){
        char r = Serial.read();
        deviceM95->getSerial()->write(r);
    }
}



