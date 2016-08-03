/* 
 * File:   Millis.cpp
 * Author: ericson
 * 
 * Created on July 22, 2016, 3:18 PM
 */

#include "Millis.h"

unsigned long global_high = 0;
unsigned long last_low = 0;

Millis::Millis() {
    low = millis();
    if (last_low > low) {
        global_high++;
    }
    last_low = low;
    high = global_high;
}

Millis::Millis(long millis) {
    high = 0;
    low = millis;
}

Millis operator+(Millis lhs, const Millis& rhs) {
    unsigned long initial_low = lhs.low;
    lhs.low += rhs.low;
    if (lhs.low < initial_low) {
        lhs.high++;
    }
    lhs.high += rhs.high;
    return lhs;
}

Millis operator-(Millis lhs, const Millis& rhs) {
    unsigned long initial_low = lhs.low;
    lhs.low -= rhs.low;
    if (lhs.low > initial_low) {
        lhs.high--;
    }
    lhs.high -= rhs.high;
    return lhs;
}

bool operator<(Millis lhs, const Millis& rhs) {
    if (lhs.high != rhs.high) {
        return lhs.high < rhs.high;
    }
    return lhs.low < rhs.low;

}

bool operator<=(Millis lhs, const Millis& rhs) {
    
    if (lhs.high != rhs.high) {
        return lhs.high <= rhs.high;
    }
    return lhs.low <= rhs.low;
}

bool operator>(Millis lhs, const Millis& rhs) {
    if (lhs.high != rhs.high) {
        return lhs.high > rhs.high;
    }
    return lhs.low > rhs.low;
}

bool operator>=(Millis lhs, const Millis& rhs) {
    if (lhs.high != rhs.high) {
        return lhs.high >= rhs.high;
    }
    return lhs.low >= rhs.low;
}

bool operator<=(Millis lhs, unsigned long tmillis) {
    if (lhs.high > 0) {
        return false;
    }
    return lhs.low <= tmillis;
}

bool operator<(Millis lhs, unsigned long tmillis) {
    if (lhs.high > 0) {
        return false;
    }
    return lhs.low < tmillis;
}

String Millis::toString() {
    String shigh = String(high, DEC);
    String slow = String(low, DEC);
    String resp = String("Hight: " + shigh + " Low: " + slow);
    return resp;
}



