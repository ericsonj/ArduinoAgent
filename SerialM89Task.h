/* 
 * File:   SerialM89Task.h
 * Author: ericson
 *
 * Created on July 22, 2016, 11:36 AM
 */

#ifndef SERIALM89TASK_H
#define	SERIALM89TASK_H

#include "Task.h"
#include "M95.h"

class SerialM89Task : public Task {
public:
    SerialM89Task(M95 *deviceM95, unsigned long crontime);
    void run();
private:
    M95 *deviceM95;
};

#endif	/* SERIALM89TASK_H */

