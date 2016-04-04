#include <windows.h>
#include <iostream>
using namespace std;

#include"drive.h"

HANDLE hSerial;

void ReadCOM(void);

int initialize(void)
{
   LPCTSTR sPortName = "COM10";
   hSerial = ::CreateFile(sPortName,GENERIC_READ | GENERIC_WRITE,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
   if(hSerial==INVALID_HANDLE_VALUE)
    {
        if(GetLastError()==ERROR_FILE_NOT_FOUND)
        {
        cout << "serial port does not exist.\n";
        }
    cout << "some other error occurred.\n";
    }
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength=sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams))
    {
        cout << "getting state error\n";
    }
    dcbSerialParams.BaudRate=CBR_9600;
    dcbSerialParams.ByteSize=8;
    dcbSerialParams.StopBits=ONESTOPBIT;
    dcbSerialParams.Parity=NOPARITY;
    if(!SetCommState(hSerial, &dcbSerialParams))
    {
        cout << "error setting serial port state\n";
    }
    //if(iRet)
    //    cout << dwSize << " Bytes in string. " << dwBytesWritten << " Bytes sended. " << endl;
    /*while(1)
    {
        ReadCOM();
    }*/
    return 0;
}

void ReadCOM()
{
      DWORD iSize;
      char sReceivedChar;
      while (true)
      {
            ReadFile(hSerial, &sReceivedChar, 1, &iSize, 0);  // получаем 1 байт
            if (iSize > 0)   // если что-то принято, выводим
                cout << sReceivedChar;
      }
}


void move_send(char tosend){
    const void *data = &tosend;
    DWORD dwSize = sizeof(tosend);
    DWORD dwBytesWritten;
    WriteFile(hSerial,data,dwSize,&dwBytesWritten,NULL);
}
