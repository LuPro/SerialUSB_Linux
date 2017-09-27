#include <iostream>

#include "Serial.h"

using namespace std;

int main()
{
    Serial serial;

    char portName[] = "/dev/ttyACM0";

    int fd = open (portName, O_RDONLY | O_NOCTTY | O_SYNC);
    if (fd < 0)
    {
        cout << "Error opening " << portName << " error code: " << strerror(errno) << endl;
        return -1;
    }
    cout << "Successfully openend " << portName << endl;

    serial.setInterfaceAttribs(fd, B115200, 0);     // set speed to 115,200 bps, 8n1 (no parity)
    serial.setBlocking(fd, 0);                      // set no blocking

    //serial.startRead();
    serial.readPort();

    for (unsigned int i = 0; i < 50 || i < serial.data.size(); i++) {
        usleep(500);
        cout << i << ":\t" << to_string(serial.data.front()) << endl;
    }

    return 0;
}
