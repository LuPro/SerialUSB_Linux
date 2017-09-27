#include <iostream>

#include "Serial.h"

using namespace std;

int main()
{
    Serial serial;

    char *portName = "/dev/ttyUSB1";

    int fd = open (portName, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0)
    {
        cout << "Error opening " << portName << " error code: " << strerror(errno);
        return;
    }

    serial.setInterfaceAttribs(fd, B115200, 0);  // set speed to 115,200 bps, 8n1 (no parity)
    serial.setBlocking(fd, 0);                // set no blocking

    return 0;
}
