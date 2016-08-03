#include <Arduino.h>
#include "AdvancedSerial.h"
#include "M95.h"
#include "Task.h"
#include "SendGPSTask.h"
#include "SerialM89Task.h"
#include "Millis.h"
#include "Logger.h"
#include "CommandManagementTask.h"
#include "SMSManagementTask.h"

extern HardwareSerial Serial;
extern HardwareSerial Serial1;

#define MAX_TASK 100

M95 *deviceM95;
Task *arrayTask[MAX_TASK];

void initUPDConnection() {
    Millis ctime = Millis();
    Millis now;
    TAresponse response;
    do {
        response = deviceM95->startConnection("UDP", "192.241.166.230", 9000);
        Logger::Instance()->logi("TRY START CONNECT TO SERVER UDP");
        now = Millis();
        if ((now - ctime) >= 10000) {
            Logger::Instance()->logi("CONNECTION TIMEOUT");
            return;
        }
    } while (response.code == "CONNECT FAIL");
}

void setup() {

    //INIT SYSTEM
    Logger::Instance()->init(&Serial, 9600);
    Logger::Instance()->active = true;
    deviceM95 = new M95(&Serial1, 7, 6, 8);
    deviceM95->initM95();
    initUPDConnection();
    pinMode(12, OUTPUT);
    digitalWrite(12,HIGH);
    Logger::Instance()->active = false;
    
    //TASK
    int pos = 0;
    //    arrayTask[pos++] = new SerialM89Task(deviceM95, 0);
    arrayTask[pos++] = new CommandManagementTask(deviceM95, &Serial);
    arrayTask[pos++] = new SendGPSTask(deviceM95, 10000);
    arrayTask[pos++] = new SMSManagementTask(deviceM95);
    arrayTask[pos++] = NULL;

}

void loop() {
    for (int i = 0; arrayTask[i] != NULL; i++) {
        arrayTask[i]->runTask();
    }
}

