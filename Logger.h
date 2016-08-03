/* 
 * File:   Logger.h
 * Author: ericson
 *
 * Created on July 22, 2016, 5:27 PM
 */

#ifndef LOGGER_H
#define	LOGGER_H
#include <Arduino.h>
#include "AdvancedSerial.h"

class Logger {
public:

    static Logger* Instance();
    void init(HardwareSerial *obj, int baudrate);
    void log(String message);
    void logi(String message);
    bool active = false;
    
private:

    Logger() {
    };

    Logger(Logger const&) {
    };

    Logger& operator=(Logger const&) {
    };

    static Logger* m_pInstance;
    AdvancedSerial _serial;
};

#endif	/* LOGGER_H */

