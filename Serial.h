#ifndef SERIAL_H
#define SERIAL_H

#endif //SERIAL_H

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <queue>
#include <thread>
#include <iostream>

using namespace std;

class Serial {
public:
    Serial();
    Serial(char *portName, int speed = B115200, int parity = 0, int shouldBlock = 0);

    ~Serial();

    ///these should not be used, except when the object got initialized with default constructor,
    ///because the overloaded constructor does all this automagically
        int setInterfaceAttribs (int speed, int parity);
        void setBlocking (int should_block);

        void startRead();
    ///

    unsigned short bytesAvailable();

    uint8_t readQueue();
    vector <uint8_t> readQueue (const uint8_t &nrBytes);

private:
    int fd;
    queue<uint8_t> data;

    thread *readPortThread;
    bool readPortThreadStop = false;

    void readPort();
};
