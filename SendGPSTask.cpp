/* 
 * File:   sendGPSTask.cpp
 * Author: ericson
 * 
 * Created on July 22, 2016, 10:57 AM
 */
#include <Arduino.h>
#include "SendGPSTask.h"
#include "Logger.h"
#include "Millis.h"

SendGPSTask::SendGPSTask(M95* deviceM95, unsigned long crontime) : Task(crontime) {
    this->deviceM95 = deviceM95;
}

void SendGPSTask::run() {

    TAresponse response = deviceM95->getGPSLocation();
    deviceM95->printInSoutAtResponse(response, "GPS LOCATION: ");
    this->sendDataUDP(response.text, 5000);
}

void SendGPSTask::sendDataUDP(String data, unsigned long timeout) {

    Millis ctime = Millis();
    Millis now;

    digitalWrite(12, LOW);
    TAresponse response;
    do {
        response = deviceM95->printATwithResponse("AT+QISTAT");
        deviceM95->printInSoutAtResponse(response, "TCP STATUS: ");
        if (response.code != "STATE: CONNECT OK") {
            response = deviceM95->startConnection("UDP", "192.241.166.230", 9000);
            Logger::Instance()->log("TRY START CONNECT TO SERVER UDP");
            now = Millis();

            if ((now - ctime) >= timeout) {
                Logger::Instance()->log("CONNECTION TIMEOUT");
                return;
            }
        }
    } while (response.code == "CONNECT FAIL");
    deviceM95->printInSoutAtResponse(response, "INIT CONNECTION: ");

    ctime = Millis();

    do {

        response = deviceM95->sendData(data);
        deviceM95->printInSoutAtResponse(response, "SEND DATA: ");
        now = Millis();
        if ((now - ctime) >= timeout) {
            Logger::Instance()->log("SEND TIMEOUT");
            return;
        }
    } while (response.code != "SEND OK");
    digitalWrite(12, HIGH);
    //    TCPIPDate tcpdata = deviceM95->readTCPIPData();
    //    Logger::Instance()->logi("SERVER RESPONSE: ");
    //    Logger::Instance()->logi(tcpdata.data);
    //    return tcpdata.data;
    //    response = deviceM95->printATwithResponse("AT+QICLOSE");
    //    deviceM95->printInSoutAtResponse(response, "CLOSE CONNECTION: ");
}



