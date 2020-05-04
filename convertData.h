/********************************************************************
 *
 * File                 : convertData.h
 * Language             : CPP
 * Name                 : Shashank Tomar
 * Email                : shashanktomar86@gmail.com
 * 
 * Description          : This header file contains declaration of
 *                        functions which performs operation to
 *                        encode and decode the input data.
 *
 *******************************************************************/


#ifndef CONVERT_DATA_H_
#define CONVERT_DATA_H_

#include<iostream>
#include<cstring>

typedef enum
{
    ERROR = -1,
    SUCCESS = 0

}E_CODE;


/* Function declarations */
void packData(unsigned short int & data);
int countSetBits(unsigned short int data);
void unpackData(unsigned short int & data);
E_CODE convertToHex(unsigned short int data, char* output, short int numByte);
E_CODE hexStringToInt(unsigned short int & data, char* inputStr);
E_CODE reverseString(char *string);
E_CODE encode(short int inputData, char* output);
signed short int decode(unsigned char hiByte, unsigned char loByte);



#endif // CONVERT_DATA_H_
