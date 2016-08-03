/* 
 * File:   M95.h
 * Author: ericson
 *
 * Created on July 15, 2016, 6:07 PM
 */

#ifndef M95_H
#define	M95_H

#include "AdvancedSerial.h"
#include "SMSMessage.h"

enum StatusResponse {
    RESPONSE_OK,
    RESPONSE_TIMEOUT
};

struct TAresponse {
    StatusResponse status;
    String text;
    String code;
};

struct TCPIPDate {
    String ipAddress;
    long port;
    int numByte;
    String protocol;
    String data;
};

struct SMS{
    String id;
    String state;
    String phoneNum;
    String date;
    String message;
};


class M95 : public AdvancedSerial {
private:
    int pinPwrKey;
    int pinStatus;
    int pinRstGps;
public:
    M95();
    M95(HardwareSerial *serial, int pinPwrkey, int pinStatus, int pinRstGps);
    boolean powerOnM95();
    TAresponse disableEco();
    TAresponse M95Ready();
    TAresponse SimCarOk();
    TAresponse ConfigAudio();
    TAresponse ConfigMIC();
    TAresponse ConfigTextMode();
    TAresponse InfoGPSL80();
    TAresponse initGPS();
    TAresponse startConnection(String type, String ipAddress, int port);
    TAresponse sendData(String data);
    TAresponse getGPSLocation();
    TAresponse printATwithResponse(String atcommand);
    void initM95();
    void resetGPS();
    void printInSoutAtResponse(struct TAresponse response, String feacture);
    void ATZ();
    void printlnAT(String command);
    void printlnAT(int command);
    void printAT(String command);
    String readResponseATNoBlocker();
    void readSMSUnread(SMSMessage *arraysms[20]);
    SMS getSMSMessage(String string);
    TCPIPDate readTCPIPData();
    TCPIPDate getTCPIPData(String string);
    TAresponse readVerboseCodeResponseAT();
};


#endif	/* M95_H */

