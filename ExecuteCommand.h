/* 
 * File:   ExecuteCommand.h
 * Author: ericson
 *
 * Created on August 3, 2016, 9:48 AM
 */

#ifndef EXECUTECOMMAND_H
#define	EXECUTECOMMAND_H

#include <Arduino.h>

struct DigitalCommand{
    String command;
    String arg1;
    String arg2;
};

class ExecuteCommand {
private:
    bool status;
    String command;
    bool isResp;
    String response;
public:
    ExecuteCommand(String command);
    void runCommand();
    DigitalCommand getDigitalCommand();
    bool isResponse(){
        return isResp;
    }

    String getResponse() const {
        return response;
    }

};

#endif	/* EXECUTECOMMAND_H */

