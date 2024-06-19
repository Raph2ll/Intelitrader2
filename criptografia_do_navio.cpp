#include <iostream>
#include <string>
#include <bitset>
#include <stdexcept>

using namespace std;

char swapHalfBytes(char byte)
{
    return ((byte & 0xF0) >> 4) | ((byte & 0x0F) << 4);
}

char swapLastTwoBits(char byte)
{
    return byte ^ 0b11;
}

string binaryToAscii(const string &binaryStr)
{
    string asciiStr;
    int bitCount = 0;
    char chr = 0;

    for (char bit : binaryStr)
    {
        chr <<= 1;
        chr |= (bit - '0');

        ++bitCount;
        if (bitCount == 8)
        {
            asciiStr += swapHalfBytes(swapLastTwoBits(chr));
            bitCount = 0;
            chr = 0;
        }
    }

    return asciiStr;
}

int main(int argc, char *argv[])
{

    for (int i = 1; i < argc; ++i)
    {
        string binaryStr = argv[i];

        string asciiStr = binaryToAscii(binaryStr);
        cout << asciiStr;
    }

    return 0;
}