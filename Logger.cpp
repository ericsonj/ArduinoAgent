/* 
 * File:   Logger.cpp
 * Author: ericson
 * 
 * Created on July 22, 2016, 5:27 PM
 */
#include "Logger.h"

Logger* Logger::m_pInstance = NULL;

Logger* Logger::Instance() {
    if (!m_pInstance)
        m_pInstance = new Logger;
    return m_pInstance;
}

void Logger::init(HardwareSerial *obj, int baudrate) {
    this->_serial = AdvancedSerial(obj, baudrate);
}

void Logger::log(String message) {
    if (active) {
        _serial.getSerial()->println(message);
    }
}

void Logger::logi(String message) {
    _serial.getSerial()->println(message);
}







