#include "Serial.h"

Serial::Serial() {

}

Serial::~Serial() {
    delete readPortThread;
}

int Serial::setInterfaceAttribs(int fd, int speed, int parity)
{
    struct termios tty;
    memset (&tty, 0, sizeof tty);

    this->fd = fd;

    if (tcgetattr (this->fd, &tty) != 0)
    {
        cout << "Error from tcgetattr: " << strerror(errno);
        return -1;
    }

    cfsetospeed (&tty, speed);
    cfsetispeed (&tty, speed);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
    // disable IGNBRK for mismatched speed tests; otherwise receive break
    // as \000 chars
    tty.c_iflag &= ~IGNBRK;         // disable break processing
    tty.c_lflag = 0;                // no signaling chars, no echo,
    // no canonical processing
    tty.c_oflag = 0;                // no remapping, no delays
    tty.c_cc[VMIN]  = 0;            // read doesn't block
    tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

    tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
    // enable reading
    tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
    tty.c_cflag |= parity;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr (fd, TCSANOW, &tty) != 0)
    {
        cout << "Error from tcgetattr" << strerror(errno);
        return -1;
    }
    return 0;
}

void Serial::setBlocking (int fd, int should_block)
{
    struct termios tty;
    memset (&tty, 0, sizeof tty);

    if (tcgetattr (fd, &tty) != 0) {
        cout << "Error from tcgetattr: " << strerror(errno);
        return;
    }

    tty.c_cc[VMIN]  = should_block ? 1 : 0;
    tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    if (tcsetattr (fd, TCSANOW, &tty) != 0) {
        cout << "Error at setting term attributes" << strerror(errno);
    }
}

void Serial::startRead() {
    readPortThread = new thread(&Serial::readPort, this);
}

void Serial::readPort() {
    size_t nrBytesRead = 0;
    uint8_t *buffer;

    while (!readPortThreadStop) {
        nrBytesRead = read(fd, buffer, 50);

        for (unsigned int i = 0; i < (nrBytesRead * sizeof (buffer)); i += sizeof (buffer)) {
            data.push(buffer[i]);
        }
    }
}
