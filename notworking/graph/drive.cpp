#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

#include"drive.h"

HANDLE hSerial, hEvent;
HANDLE hTread;
DWORD bytesRead, bWritten;
DWORD dwParam, dwThreadId;
int counter = 0;

char tbuf[128];
char* pbuf=tbuf;

void ReadCOM(void);

VOID WINAPI ThreadProc(PVOID* dummy){
    while(true){
        ReadFile(hSerial, pbuf, 1, &bytesRead, NULL);
        if (bytesRead>0)
        {
            WriteFile(hSerial, pbuf++, 1, &bWritten, NULL);
            if(tbuf[counter] == '&'){
                SetEvent(hEvent);
              	tbuf[counter+1]='\0';
                counter=0;
                pbuf=tbuf;
            }
          counter++;
        }
    }
}

int initialize(void)
{
   char* sPortName = "COM7";
   hSerial=CreateFile(sPortName, GENERIC_READ | GENERIC_WRITE,
        0, NULL, OPEN_EXISTING, 0, NULL);
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
  	hEvent= CreateEvent(NULL, FALSE, FALSE, NULL);
    hTread=CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc,
        &dwParam, 0, &dwThreadId);
    //move_send('p');
    //move_send('l');
    return 0;
}

char *ReadCOM(char *buff)
{
  	WaitForSingleObject(hEvent, INFINITE);
  	sprintf(buff,"%s", tbuf);
  	return buff;
}



void move_send(char tosend){
    const void *data = &tosend;
    DWORD dwSize = sizeof(tosend);
    DWORD dwBytesWritten;
    WriteFile(hSerial,data,dwSize,&dwBytesWritten,NULL);
}
