/********************************************************************
 *
 * File                 : convertData.cpp
 * Language             : CPP
 * Name                 : Shashank Tomar
 * Email                : shashanktomar86@gmail.com
 * 
 * Description          : This source file contains implementation of
 *                        functions which performs operation to
 *                        encode and decode the input data.
 *
 *******************************************************************/

#include "convertData.h"
using namespace std;

/********************************************************************
 * Function    : packData()
 * Input       : unsigned short int &
 * Returns     : void
 * Description : This function pack the input data into two bytes with
 *               clearing the last two MSBs
 ********************************************************************/
void packData(unsigned short int & data)
{
    bool msb1 = data & (1 << 7);  // get the MSB bit of first byte
    int mask  = ~ (1 << 7);       // mask value to unset the MSB of first byte
    data = data & mask;           // clear MSB of first byte 
    data = data | (msb1 << 14);   // set the 15th bit with the MSB value of first byte

    /* if 8th bit is not set, then multiply the number by 2 */
    if (!msb1)
    {
        data = data << 1;
    }
}

/********************************************************************
 * Function    : countSetBits()
 * Input       : unsigned short int
 * Returns     : int
 * Description : This function count the number of bits in the input
 ********************************************************************/
int countSetBits(unsigned short int data)
{
    int setBits = 0;
    int i = 0;
    int result = 0;
    while (i < 14)
    {
        result = data & (1 << i);
        if (result)
        {
            ++setBits;
        }
        
        ++i;
    }

    return setBits;
}

/********************************************************************
 * Function    : unPackData()
 * Input       : unsigned short int &
 * Returns     : void
 * Description : This function unpack the input data into two bytes.
 ********************************************************************/
void unpackData(unsigned short int & data)
{
    bool bit15 = (data) & (1 << 14); // get the MSB bit of first byte
    int mask  = ~ (1 << 14);         // mask value to unset the MSB of first byte
    int setBits = 0;

    // count the number of bits in number
    setBits = countSetBits(data);

    /* if number of bits is less than or equal to 1,
       then just divide the num by 2, else if 15th bit is
       set then set the 8th bit and unset the 15th bit  */
    if(setBits <= 1)
    {
        data = data >> 1;
    }
    else if (bit15)
    {
        data = data | (1 << 7);
        data = data & mask;
    }
}

/********************************************************************
 * Function    : convertToHex()
 * Input       : unsigned short int, char* , short int
 * Returns     : E_CODE - SUCCESS or ERROR
 * Description : This function converts int data to hex string
 ********************************************************************/
E_CODE convertToHex(unsigned short int data, char* output, short int numByte)
{
    int remainder = 0;
    int i = 0;

    if (NULL == output)
    {
        return ERROR;
    }
    while (i < numByte)
    {
        remainder = data % 16;

        /* if remainder is less than 10, then add '0' to get the
           integer value */
        if (remainder < 10)
        {
            output[i++] = remainder + '0';
        }
        /* if remainder is greater or equal to 10, then add '7' to get the
           alphabetical value */
        else
        {
            output[i++] = remainder + '7';
        }

        data = data / 16;
    }

    output[i] = '\0';
    return SUCCESS;
}

/********************************************************************
 * Function    : hexStringToInt()
 * Input       : unsigned short int, char*
 * Returns     : E_CODE - SUCCESS or ERROR
 * Description : This function converts hex string to int
 ********************************************************************/
E_CODE hexStringToInt(unsigned short int & data, char* inputStr)
{
    int i = 0;
    int len = strlen(inputStr);

    if (NULL == inputStr)
    {
        return ERROR;
    }
    while (i < len)
    {
        if (inputStr[i] >= '0' && inputStr[i] <= '9')
        {
            data = (data * 16) + (inputStr[i] - '0');
        }
        else if (inputStr[i] >= 'A' && inputStr[i] <= 'F')
        {
            data = (data * 16) + (inputStr[i] - 'A' + 10);
        }
        if (inputStr[i] >= 'a' && inputStr[i] <= 'f')
        {
            data = (data * 16) + (inputStr[i] - 'a' + 10);
        }

        i++;
    }

    return SUCCESS;

}


/********************************************************************
 * Function    : reverseString()
 * Input       : char*
 * Returns     : E_CODE - SUCCESS or ERROR
 * Description : This function reverses the input string in place
 ********************************************************************/
E_CODE reverseString(char *string) 
{
    char *temp = string;
    int str_len = 0, i = 0, mid = 0;
    E_CODE ecode = SUCCESS;

    /* do-while loop is used to have single exit point from the function */
    do
    {
        if (NULL == string)
        {
            ecode = ERROR;
            break;
        }

        /* while loop to find the strlen, since calling library function for strlen
           takes more time, more executible size and even not recommended for platform 
           independent code
        */
        while(*temp++)
        {
            str_len++;
        }

        mid = str_len/2;

        /* This loop is to swap the string elements from first to last till
           it reaches to the centre of the string.
        */
        while(i < mid)
        {
            string[i] = string[i] + string[str_len - 1];
            string[str_len - 1] = string[i] - string[str_len - 1];
            string[i] = string[i] - string[str_len - 1];

            i++;
            str_len--;
        }

    } while(0);

    return ecode;

}



/********************************************************************
 * Function    : encode()
 * Input       : short int, char* - user has to take care of memory
 * Returns     : E_CODE - SUCCESS or ERROR
 * Description : This function encode the input data into output string
 ********************************************************************/
E_CODE encode(short int inputData, char* output)
{
    unsigned short int data = 0;
    E_CODE ecode = SUCCESS;

    do
    {
        if ((-8192 > inputData) || (8191 < inputData) || (NULL == output))
        {
            ecode = ERROR;
            break;
        }

        // translated data range from 0 to 16383, i.e. signed to unsigned
        data = 8192 + inputData;
        packData(data);
        if (ERROR == convertToHex(data, output, 4))
        {
            ecode = ERROR;
            break;
        }
        if (ERROR == reverseString(output))
        {
            ecode = ERROR;
            break;
        }

    } while (0);

    return SUCCESS;
}


/********************************************************************
 * Function    : decode()
 * Input       : unsigned char, unsigned char
 * Returns     : signed short int
 * Description : This function decodes the two input byte and returns
 *               the decoded output.
 ********************************************************************/
signed short int decode(unsigned char hiByte, unsigned char loByte)
{
    char hexString[5];
    char hiByteStr[3];
    char loByteStr[3];
    unsigned short int  num = 0;
    signed short int finalOutput = -1;
    
    do
    {
        if ((0x00 > hiByte || 0x7f < hiByte)
            || (0x00 > loByte || 0x7f < loByte))
        {
            cout<<"Input value out of range\n";
            break;
        }

        if (ERROR == convertToHex(hiByte, hiByteStr, 2))
        {
            cout << "convertToHex failed\n";
            break;
        }
        if (ERROR == reverseString(hiByteStr))
        {
            break;
        }
        if (ERROR == convertToHex(loByte, loByteStr, 2))
        {
            cout << "convertToHex failed\n";
            break;
        }
        if (ERROR == reverseString(loByteStr))
        {
            break;
        }

        strcpy(hexString, hiByteStr);
        strcat(hexString, loByteStr);
        hexString[5] = '\0';
        if (ERROR == hexStringToInt(num, hexString))
        {
            cout << "hexStringToInt failed\n";
            break;
        }

        unpackData(num);
        finalOutput = num - 8192;

    } while (0);

    return finalOutput;
}

