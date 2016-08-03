/* 
 * File:   sendGPSTask.h
 * Author: ericson
 *
 * Created on July 22, 2016, 10:57 AM
 */

#ifndef SENDGPSTASK_H
#define	SENDGPSTASK_H

#include "Task.h"
#include "M95.h"

class SendGPSTask : public Task {
public:
    SendGPSTask(M95 *deviceM95,unsigned long crontime);
    void run();
private:
    M95 *deviceM95;
    void sendDataUDP(String data, unsigned long timeout);
};

#endif	/* SENDGPSTASK_H */

