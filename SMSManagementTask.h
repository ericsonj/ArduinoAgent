/* 
 * File:   SMSManagementTask.h
 * Author: ericson
 *
 * Created on July 27, 2016, 11:11 AM
 */

#ifndef SMSMANAGEMENTTASK_H
#define	SMSMANAGEMENTTASK_H
#include "Task.h"
#include "M95.h"

class SMSManagementTask : public Task {
private:
    M95 *deviceM95;
public:
    SMSManagementTask(M95 *deviceM95);
    void run();
};

#endif	/* SMSMANAGEMENTTASK_H */

