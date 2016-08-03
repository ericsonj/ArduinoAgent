/* 
 * File:   Task.h
 * Author: ericson
 *
 * Created on July 22, 2016, 9:37 AM
 */

#ifndef TASK_H
#define	TASK_H

#include "Millis.h"


class Task {
public:
//    Task(unsigned long lastTime);
    Task(unsigned long crontime);
    virtual void run() = 0;
    unsigned long getCrontime(){
        return crontime;
    }

    void setCrontime(unsigned long crontime) {
        this->crontime = crontime;
    }

    void runTask();
private:
    unsigned long crontime;
    Millis lastTime;
    
};

#endif	/* TASK_H */

