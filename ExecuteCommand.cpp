/* 
 * File:   ExecuteCommand.cpp
 * Author: ericson
 * 
 * Created on August 3, 2016, 9:48 AM
 */

#include "ExecuteCommand.h"
#include "Logger.h"
#include <EEPROM.h>

#define MAX_GUID 32

ExecuteCommand::ExecuteCommand(String command) {
    this->isResp = false;
    this->command = command;
}

void ExecuteCommand::runCommand() {

    DigitalCommand dc = getDigitalCommand();

    if (dc.command == "DIGITALWRITE") {
        pinMode(dc.arg1.toInt(), OUTPUT);
        digitalWrite(dc.arg1.toInt(), dc.arg2.toInt());
    }

    if (dc.command == "READDIGITAL") {
        this->isResp = true;
        int resp = digitalRead(dc.arg1.toInt());
        this->response = "READDIGITAL\t" + dc.arg1 + "\t" + String(resp);
    }

    if (dc.command == "ANALOGREAD") {
        this->isResp = true;
        int resp = analogRead(dc.arg1.toInt());
        this->response = "ANALOGREAD\t" + dc.arg1 + "\t" + String(resp);
    }

    if (dc.command == "ANALOGWRITE") {
        analogWrite(dc.arg1.toInt(), dc.arg2.toInt());
    }

    if (dc.command == "EEPROMWRITE") {
        EEPROM.write(dc.arg1.toInt(), dc.arg2.toInt());
        delay(100);
    }

    if (dc.command == "EEPROMREAD") {
        this->isResp = true;
        byte a = EEPROM.read(dc.arg1.toInt());
        this->response = "EEPROMREAD\t" + dc.arg1 + "\t" + String((int) a);
    }

    if (dc.command == "SETGUID") {
        this->isResp = true;
        char buffer[MAX_GUID];
        dc.arg1.toCharArray(buffer, MAX_GUID, 0);
        for (int i = 0; i < sizeof (buffer); i++) {
            EEPROM.write(i, buffer[i]);
        }
    }

    if (dc.command == "GETGUID") {
        this->isResp = true;
        char buffer[MAX_GUID];
        for (int i = 0; i < sizeof(buffer); i++) {
            buffer[i] = EEPROM.read(i);
        }
        this->response = "EEPROMREAD\t" + String(buffer);
    }

}

DigitalCommand ExecuteCommand::getDigitalCommand() {
    DigitalCommand resp;
    int index = command.indexOf('\t');
    int endIndex = command.indexOf('\n');
    if (index > 0) {
        int auxIndex = command.indexOf('\t', index + 1);
        if (auxIndex < 0) {
            resp.command = command.substring(0, index);
            resp.arg1 = command.substring(index + 1, endIndex);
            resp.arg2 = "";
        } else {
            resp.command = command.substring(0, index);
            resp.arg1 = command.substring(index + 1, auxIndex);
            resp.arg2 = command.substring(auxIndex + 1, endIndex);
        }
    } else {
        resp.command = command.substring(0, endIndex);
            resp.arg1 = "";
            resp.arg2 = "";
    }
    return resp;
}


