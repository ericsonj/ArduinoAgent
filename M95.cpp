#include <Arduino.h>
#include "M95.h"
#include "Logger.h"

M95::M95() {

}

M95::M95(HardwareSerial* serial, int pinPwrkey, int pinStatus, int pinRstGps) : AdvancedSerial(serial) {
    this->pinPwrKey = pinPwrkey; //7
    this->pinStatus = pinStatus; //6
    this->pinRstGps = pinRstGps; //8
}

boolean M95::powerOnM95() {

    pinMode(pinRstGps, OUTPUT);
    //    digitalWrite(pinRstGps, HIGH); // reset del GPS en 1 se reinicia y en 0 funcionamiento normal //Reset GPS
    pinMode(pinPwrKey, OUTPUT);
    digitalWrite(pinPwrKey, LOW); //salida que opera el terminal PWRKEY del M95
    pinMode(pinStatus, INPUT_PULLUP); //entrada con pullup para censar el STATUS del M95

    delay(5000);

    if ((digitalRead(pinStatus)) == LOW) { //revisar si el M95 esta apagado
        digitalWrite(pinPwrKey, HIGH);
        int count = 0;
        int twait = 50;
        while (digitalRead(pinStatus) == LOW) { //prender el M95, acciona pwrkey hasta que status sea 1                            
            delay(100);
            count++;
        }
        if (count >= twait) {
            return false;
            Logger::Instance()->log("MODULE M95 OFF");
        }
        digitalWrite(pinPwrKey, LOW);
    }
    delay(100);
    Logger::Instance()->log("MODULE M95 ON");
    return true;

}

void M95::printlnAT(String command) {
    //    read();
    getSerial()->println(command);
}

void M95::printlnAT(int command) {
    getSerial()->println(command);
}

void M95::printAT(String command) {
    getSerial()->print(command);
}

TAresponse M95::disableEco() {
    printlnAT("ATE0");
    return readVerboseCodeResponseAT();
}

String M95::readResponseATNoBlocker() {
    if (waitDataWithTimeout()) {
        return read();
    }
    return "";
}

TAresponse M95::readVerboseCodeResponseAT() {
    TAresponse resp;
    StatusResponse status1 = RESPONSE_TIMEOUT;
    String text1 = "";
    String code1 = "";
    String r = readResponseATNoBlocker();
    if (r != "") {
        status1 = RESPONSE_OK;
        char brResp[r.length()];
        r.toCharArray(brResp, r.length());
        int i = r.length() - 2;
        while (brResp[i] == '\r' || brResp[i] == '\n') {
            i = i - 1;
        }
        while (brResp[i] != '\r' && brResp[i] != '\n') {
            code1 = (char) brResp[i] + code1;
            i--;
        }
        while (brResp[i] == '\r' || brResp[i] == '\n') {
            i--;
        }
        while (i >= 0) {
            if (brResp[i] != '\r' && brResp[i] != '\n') {
                text1 = (char) brResp[i] + text1;
            } else {
                text1 = (char) ' ' + text1;
            }
            i--;
        }
    }
    resp.status = status1;
    resp.text = text1;
    resp.code = code1;
    return resp;
}

TAresponse M95::M95Ready() {
    printlnAT("AT+CFUN?");
    return readVerboseCodeResponseAT();
}

TAresponse M95::SimCarOk() {
    printlnAT("AT+CPIN?");
    return readVerboseCodeResponseAT();
}

TAresponse M95::ConfigAudio() {
    printlnAT("AT+QAUDCH=2");
    return readVerboseCodeResponseAT();
}

TAresponse M95::ConfigMIC() {
    printlnAT("AT+QMIC=2,12");
    return readVerboseCodeResponseAT();
}

TAresponse M95::ConfigTextMode() {
    printlnAT("AT+CMGF=1");
    return readVerboseCodeResponseAT();
}

TAresponse M95::InfoGPSL80() {
    printlnAT("AT+QGPSCFG?");
    return readVerboseCodeResponseAT();
}

TAresponse M95::initGPS() {
    printlnAT("AT+QGPSCFG=\"GPSINIT\",1");
    return readVerboseCodeResponseAT();
}

TAresponse M95::startConnection(String type, String ipAddress, int port) {
    printAT("AT+QIOPEN=\"");
    printAT(type);
    printAT("\",\"");
    printAT(ipAddress);
    printAT("\",");
    printlnAT(port);
    return readVerboseCodeResponseAT();
}

TAresponse M95::sendData(String data) {
    printlnAT("AT+QISEND");
    String a = readResponseATNoBlocker();
    if (a != "") {
        printAT(data);
        getSerial()->print("\x1A");
    }
    return readVerboseCodeResponseAT();
}

TAresponse M95::printATwithResponse(String atcommand) {
    printlnAT(atcommand);
    return readVerboseCodeResponseAT();
}

TAresponse M95::getGPSLocation() {
    return printATwithResponse("AT+QGPSRD=\"NMEA/RMC\"");
}

void M95::initM95() {

    TAresponse response;

    powerOnM95();

    do {
        response = this->disableEco();
    } while (response.status == RESPONSE_TIMEOUT);
    printInSoutAtResponse(response, "DISABLE ECO: ");

    do {
        response = this->M95Ready();
    } while (response.status == RESPONSE_TIMEOUT);
    printInSoutAtResponse(response, "M95 READY: ");

    response = this->SimCarOk();
    printInSoutAtResponse(response, "SIM CARD: ");

    response = this->ConfigAudio();
    printInSoutAtResponse(response, "AUDIO: ");

    response = this->ConfigMIC();
    printInSoutAtResponse(response, "MIC: ");

    response = this->ConfigTextMode();
    printInSoutAtResponse(response, "TEXT MODE:  ");

    response = this->InfoGPSL80();
    printInSoutAtResponse(response, "INFO GPS: ");

    response = this->initGPS();
    printInSoutAtResponse(response, "INIT GPS: ");

    response = this->printATwithResponse("AT+QIDEACT=?");
    printInSoutAtResponse(response, "DESACTIVE  GPRS/CSD PDP: ");

    do {
        response = this->printATwithResponse("AT+QIDEACT");
    } while (response.status == RESPONSE_TIMEOUT || response.code == "ERROR");
    printInSoutAtResponse(response, "DESACTIVE GPRS/CSD PDP: ");

    response = this->printATwithResponse("AT+QISHOWRA=1");
    printInSoutAtResponse(response, "SHOW ADDRESS SENDER: ");

    response = this->printATwithResponse("AT+QIHEAD=1");
    printInSoutAtResponse(response, "ADD IP HEAD: ");

    response = this->printATwithResponse("AT+QISHOWPT=1");
    printInSoutAtResponse(response, "SHOW PROTOCOL: ");

    resetGPS();

}

void M95::printInSoutAtResponse(TAresponse response, String feacture) {
    if (response.status == RESPONSE_OK) {
        String res = feacture + response.text + " -- " + response.code;
        Logger::Instance()->log(res);
    } else {
        Logger::Instance()->log("RESPONSE FAIL");
    }

}

void M95::resetGPS() {
    digitalWrite(pinRstGps, LOW);
    delay(1000);
    digitalWrite(pinRstGps, HIGH);
    delay(100);
}

TCPIPDate M95::readTCPIPData() {
    String aux = readResponseATNoBlocker();
    return getTCPIPData(aux);
}

TCPIPDate M95::getTCPIPData(String string) {
    TCPIPDate tcpipdata;
    String aux = string;
    bool showProtocol = true;
    String ipAddress = "";
    String port = "";
    String numByte = "";
    String protocol = "";
    String data = "";

    int index = aux.indexOf("RECV FROM:");
    if (index > 0) {
        ipAddress = aux.substring(index + 10, index + 25);
        port = aux.substring(index + 26, aux.indexOf('\n', index + 26));
        index = aux.indexOf("IPD");
        int auxIndex = aux.indexOf("UDP", index + 3);
        if (auxIndex < 0) {
            auxIndex = aux.indexOf("TCP", index + 3);
            if (auxIndex < 0) {
                showProtocol = false;
                auxIndex = aux.indexOf(':', index + 3);
            }
        }
        numByte = aux.substring(index + 3, auxIndex);

        if (showProtocol) {
            protocol = aux.substring(auxIndex, auxIndex + 3);
            data = aux.substring(auxIndex + 4, auxIndex + 4 + numByte.toInt());
        } else {
            data = aux.substring(auxIndex + 1, auxIndex + numByte.toInt() + 1);
        }
    }
    tcpipdata.ipAddress = ipAddress;
    tcpipdata.port = port.toInt();
    tcpipdata.numByte = numByte.toInt();
    tcpipdata.protocol = protocol;
    tcpipdata.data = data;

    return tcpipdata;
}

void M95::readSMSUnread(SMSMessage *arraysms[20]) {

//    SMSMessage *arraysms[50];
    int pos = 0;
    printlnAT("AT+CMGL=\"REC UNREAD\"");
    String res = readResponseATNoBlocker();
    bool next = true;
    String line = "";
    int idx;
    int idx2 = 0;
    if (res != "") {
        while (next) {
            idx = res.indexOf("+CMGL: ", idx2);
            idx2 = res.indexOf("+CMGL: ", idx + 7);
            if (idx2 < 0) {
                next = false;
                line = res.substring(idx, res.length());
            } else {
                line = res.substring(idx, idx2);
            }
            SMS rsms = getSMSMessage(line);
            arraysms[pos++] = new SMSMessage(rsms.id, rsms.state, rsms.phoneNum, rsms.date, rsms.message);
        }
    }
    arraysms[pos++] = NULL;
}

SMS M95::getSMSMessage(String string) {
    SMS resp;
    int index = string.indexOf("+CMGL: ");
    int auxIndex = string.indexOf(',');
    resp.id = string.substring(index + 7, auxIndex);

    index = string.indexOf(',', auxIndex + 1);
    resp.state = string.substring(auxIndex + 2, index - 1);

    auxIndex = string.indexOf(',', index + 1);
    resp.phoneNum = string.substring(index + 2, auxIndex - 1);

    index = string.indexOf(',', auxIndex + 1);
    auxIndex = string.indexOf('"', index + 2);
    resp.date = string.substring(index + 2, auxIndex);

    index =  string.indexOf('\n', auxIndex + 3); 
    resp.message = string.substring(auxIndex + 3, index);

    return resp;
}



