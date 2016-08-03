/* 
 * File:   Task.cpp
 * Author: ericson
 * 
 * Created on July 22, 2016, 9:37 AM
 */
#include <Arduino.h>
#include "Task.h"


Task::Task(unsigned long crontime) {
    this->lastTime = Millis();
    this->crontime = crontime;
}


void Task::runTask() {
    Millis now;
    if ((now - lastTime) >= crontime) {
        lastTime = Millis();
        this->run();
    }
}




