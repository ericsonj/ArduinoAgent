/* 
 * File:   SMSMessage.cpp
 * Author: ericson
 * 
 * Created on July 28, 2016, 4:02 PM
 */

#include "SMSMessage.h"


SMSMessage::SMSMessage(String id, String state, String phoneNum, String date, String message) {
    this->id = id;
    this->state = state;
    this->phoneNum = phoneNum;
    this->date = date;
    this->message = message;
}

