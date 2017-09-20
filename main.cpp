#include <iostream>

#include "Serial.h"

using namespace std;

int main()
{
    Serial serial;

    serial.open("/dev/sda1337");

    return 0;
}
