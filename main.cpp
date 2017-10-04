#include <iostream>

#include "Serial.h"

using namespace std;

int main()
{
    char portName[] = "/dev/ttyACM0";

    Serial serial(portName);

    while (1) {
        if (serial.bytesAvailable() != 0) {
            cout << to_string(serial.readQueue()) << endl;
        } else {
            usleep(10000);
        }
    }

    return 0;
}
