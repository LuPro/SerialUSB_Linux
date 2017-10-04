#include <iostream>

#include "Serial.h"

using namespace std;

int main()
{
    char portName[] = "/dev/ttyACM0";

    Serial serial(portName);

    /*int fd = open (portName, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0)
    {
        cout << "Error opening " << portName << " error code: " << strerror(errno) << endl;
        return -1;
    }
    cout << "Successfully openend " << portName << endl;

    serial.setInterfaceAttribs(fd, B115200, 0);     // set speed to 115,200 bps, 8n1 (no parity)
    serial.setBlocking(fd, 0);                      // set no blocking

    serial.startRead();*/

    while (1) {
        if (serial.bytesAvailable() != 0) {
            cout << to_string(serial.readQueue()) << endl;
        } else {
            usleep(10000);
        }
    }

    return 0;
}
