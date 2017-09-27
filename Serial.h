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

using namespace std;

class Serial {
public:
    Serial();
    ~Serial();

    queue<uint8_t> data;

    int setInterfaceAttribs (int fd, int speed, int parity);
    void setBlocking (int fd, int should_block);

    void startRead();

private:
    int fd;

    void readPort();
    thread *readPortThread;
    bool readPortThreadStop = false;
};
