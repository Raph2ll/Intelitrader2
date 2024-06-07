#include <iostream>
#include <string>
#include <bitset>
#include <stdexcept>

std::string binaryToAscii(const std::string &binaryStr) {
    std::string asciiStr;
    int bitCount = 0;
    char chr = 0;

    for (char bit : binaryStr) {
        chr <<= 1;
        if (bit == '1') {
            chr |= 1;
        }

        ++bitCount;
        if (bitCount == 8) {
            asciiStr += chr;
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
        std::string binaryStr = argv[i];
        try
        {
            std::string asciiStr = binaryToAscii(binaryStr);
            std::cout << asciiStr;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Please enter a valid value" << std::endl;
            return 1;
        }
    }

    return 0;
}