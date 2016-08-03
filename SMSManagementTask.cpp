/* 
 * File:   SMSManagementTask.cpp
 * Author: ericson
 * 
 * Created on July 27, 2016, 11:11 AM
 */

#include "SMSManagementTask.h"
#include "Logger.h"

SMSManagementTask::SMSManagementTask(M95* deviceM95) : Task(10000) {
    this->deviceM95 = deviceM95;
}

void SMSManagementTask::run() {

    SMSMessage * array[20];
    this->deviceM95->readSMSUnread(array);
    for (int i = 0; array[i] != NULL; i++) {
        if (array[i]->GetMessage() != "") {
            Logger::Instance()->logi(array[i]->GetMessage());
        }
        delete array[i];
    }

}



