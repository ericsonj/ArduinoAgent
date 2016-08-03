/* 
 * File:   SMSMessage.h
 * Author: ericson
 *
 * Created on July 28, 2016, 4:02 PM
 */

#ifndef SMSMESSAGE_H
#define	SMSMESSAGE_H
#include <Arduino.h>

class SMSMessage {
private:
    String id;
    String state;
    String phoneNum;
    String date;
    String message;
public:
    SMSMessage(String id,
            String state,
            String phoneNum,
            String date,
            String message);

    String GetDate() const {
        return date;
    }

    void SetDate(String date) {
        this->date = date;
    }

    String GetId() const {
        return id;
    }

    void SetId(String id) {
        this->id = id;
    }

    String GetMessage() const {
        return message;
    }

    void SetMessage(String message) {
        this->message = message;
    }

    String GetPhoneNum() const {
        return phoneNum;
    }

    void SetPhoneNum(String phoneNum) {
        this->phoneNum = phoneNum;
    }

    String GetState() const {
        return state;
    }

    void SetState(String state) {
        this->state = state;
    }

};

#endif	/* SMSMESSAGE_H */

