#ifndef UTIL_h
#define UTIL_h

#include <stdio.h>
#include <iostream>
using namespace std;
#include <cstring>
#include <math.h>


namespace ATE 
{

    class Util
    {
    private:
        /* data */
    public:
        Util(/* args */);
        ~Util();

        static void HexToByte(const char* source, unsigned char* dest);
    };
    

}

#endif