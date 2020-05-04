#include "convertData.h"
using namespace std;

void test_1()
{
    char *hexValue = new char[5];
    int out = 0;
    int in = 0;
    encode(in, hexValue);
    out = decode(0x40, 0x00);
    if (in == out)
        cout << "success\n";
    else
        cout << "fail\n";
}

void test_2()
{
    char *hexValue = new char[5];
    int out;
    int in = -8192;
    encode(in, hexValue);
    out = decode(0x00, 0x00);
    if (in == out)
        cout << "success\n";
    else
        cout << "fail\n";
}

void test_3()
{
    char *hexValue = new char[5];
    int out;
    int in = 8191;
    encode(in, hexValue);
    out = decode(0x7f, 0x7F);
    if (in == out)
        cout << "success\n";
    else
        cout << "fail\n";
}

void test_4()
{
    char *hexValue = new char[5];
    int out;
    int in = 2048;
    encode(in, hexValue);
    out = decode(0x50, 0x00);
    if (in == out)
        cout << "success\n";
    else
        cout << "fail\n";
}

void test_5()
{
    char *hexValue = new char[5];
    int out;
    int in = -4096;
    encode(in, hexValue);
    out = decode(0x20, 0x00);
    if (in == out)
        cout << "success\n";
    else
        cout << "fail\n";
}

void test_6()
{
    char *hexValue = new char[5];
    int in = 6111;
    encode(in, hexValue);
    cout << "encode value for "<< in << " -> " << hexValue << endl;
    in = 340;
    encode(in, hexValue);
    cout << "encode value for "<< in << " -> " << hexValue << endl;
    in = -2628;
    encode(in, hexValue);
    cout << "encode value for "<< in << " -> " << hexValue << endl;
    in = -255;
    encode(in, hexValue);
    cout << "encode value for "<< in << " -> " << hexValue << endl;
    in = 7550;
    encode(in, hexValue);
    cout << "encode value for "<< in << " -> " << hexValue << endl;
}

void test_7()
{
    int out;
    out = decode(0x0A, 0x0A);
    cout << "decode value for "<< "0A0A" << " -> " << out << endl;
    out = decode(0x00, 0x29);
    cout << "decode value for "<< "0029" << " -> " << out << endl;
    out = decode(0x3F, 0x0F);
    cout << "decode value for "<< "3F0F" << " -> " << out << endl;
    out = decode(0x44, 0x00);
    cout << "decode value for "<< "4400" << " -> " << out << endl;
    out = decode(0x5E, 0x7F);
    cout << "decode value for "<< "5E7F" << " -> " << out << endl;
}



int main()
{

    test_1();
    test_2();
    test_3();
    test_4();
    test_5();
    test_6();
    test_7();

}
