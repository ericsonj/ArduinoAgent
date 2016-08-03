/* 
 * File:   Millis.h
 * Author: ericson
 *
 * Created on July 22, 2016, 3:18 PM
 */

#ifndef MILLIS_H
#define	MILLIS_H

#include <Arduino.h>

extern unsigned long global_high;
extern unsigned long last_low;

class Millis {
private:
    
public:
    unsigned long high;
    unsigned long low;
    Millis();
    Millis(long millis);

    String toString();
};
Millis operator+(Millis lhs, const Millis& rhs);
Millis operator-(Millis lhs, const Millis& rhs);
bool operator<(Millis lhs, const Millis& rhs);
bool operator<=(Millis lhs, const Millis& rhs);
bool operator<(Millis lhs,  unsigned long tmillis);
bool operator<=(Millis lhs, unsigned long tmillis);
bool operator>(Millis lhs, const Millis& rhs);
bool operator>=(Millis lhs, const Millis& rhs);


#endif	/* MILLIS_H */

