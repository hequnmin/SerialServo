#include "Util.hpp"

namespace ATE
{

    Util::Util(/* args */)
    {
    }
    
    Util::~Util()
    {
    }
    
    void Util::HexToByte(const char* source, unsigned char* dest)
    {
        short i;
        unsigned char highByte, lowByte;

        int sourceLen = strlen(source);

        for (i = 0; i < sourceLen; i += 2) {
            highByte = toupper(source[i]);
            lowByte = toupper(source[i + 1]);

            if (highByte > 0x39)
                highByte -= 0x37;
            else
                highByte -= 0x30;
            if (lowByte > 0x39)
                lowByte -= 0x37;
            else
                lowByte -= 0x30;

            dest[i / 2] = (highByte << 4) | lowByte;
        }
        return ;
    }

}

