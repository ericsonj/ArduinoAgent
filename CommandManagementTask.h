/* 
 * File:   CommandManagementTask.h
 * Author: ericson
 *
 * Created on July 25, 2016, 11:48 AM
 */

#ifndef COMMANDMANAGEMENTTASK_H
#define	COMMANDMANAGEMENTTASK_H

#include "Task.h"
#include "M95.h"

class CommandManagementTask : public Task {
public:
    CommandManagementTask(M95 *deviceM95, HardwareSerial *obj);
    void  run();
private:
    M95 *deviceM95;
    AdvancedSerial serialad;
    bool filterDevice(String string);
    void runCommand();
};

#endif	/* COMMANDMANAGEMENTTASK_H */

