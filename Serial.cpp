#include "Serial.h"

Serial::Serial(){

}

bool Serial::open(const string &port) {
    serial.open(port, ios_base::in | ios_base::binary);

    return serial.is_open();
}

bool Serial::readByte(uint8_t &data) {
    if (serial.peek() == EOF) {
        return false;
    }

    char c;
    serial.get(c);
    data = c;

    return true;
}
