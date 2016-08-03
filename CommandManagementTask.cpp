/* 
 * File:   CommandManagementTask.cpp
 * Author: ericson
 * 
 * Created on July 25, 2016, 11:48 AM
 */

#include "CommandManagementTask.h"
#include "Logger.h"
#include "ExecuteCommand.h"

char prefix_command[] = "CT";
bool pCommand = false;
String commandComtor = "";

CommandManagementTask::CommandManagementTask(M95* deviceM95, HardwareSerial* obj) : Task(0) {
    this->deviceM95 = deviceM95;
    serialad = AdvancedSerial(obj);
}

void CommandManagementTask::run() {
    if (deviceM95->getSerial()->available()) {
        String tmp = deviceM95->read();
        if (!filterDevice(tmp)) {
            serialad.getSerial()->print(tmp);
        }
    }
    if (serialad.getSerial()->available()) {
        String tmp = serialad.read();
        deviceM95->getSerial()->print(tmp);
    }
}

bool CommandManagementTask::filterDevice(String string) {
    if (string.startsWith("RING", 2)) {
        deviceM95->printAT("ATH");
        deviceM95->read();
        return true;
    }
    if (string.startsWith("RECV", 2)) {
        TCPIPDate tcpipdate = deviceM95->getTCPIPData(string);
        Logger::Instance()->logi(tcpipdate.ipAddress + "|" + String(tcpipdate.port) + "|" + String(tcpipdate.numByte) + "|" + tcpipdate.data);
        ExecuteCommand exeCommand = ExecuteCommand(tcpipdate.data);
        exeCommand.runCommand();
        if(exeCommand.isResponse()){
            deviceM95->sendData(exeCommand.getResponse());
        }
        return true;
    }
    return false;
}

void CommandManagementTask::runCommand() {
    if (pCommand) {
        Logger::Instance()->active = true;
        Logger::Instance()->log("RUN COMTOR COMAND " + commandComtor);
        Logger::Instance()->active = false;
        commandComtor = "";
        pCommand = false;
    }
}






