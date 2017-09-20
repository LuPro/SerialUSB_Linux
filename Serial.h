#ifndef SERIAL_H
#define SERIAL_H

#endif //SERIAL_H

#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Serial {
public:
    Serial();

    bool open(const string &port);

    vector <uint8_t> read();

private:
    ifstream serial;

    bool readByte(uint8_t &data);
};
