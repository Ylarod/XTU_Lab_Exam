#include <iostream>
#include <windows.h>	//Sleep()
#include <stdio.h>
#include <string.h>

using namespace std;

#define BUFFSIZE 128

void MyErrExit(char *Err)
{
	cout<<"Error : "<<Err<<endl;
	_flushall();		//清除缓冲区
	getchar();		//等待按键
	exit(0);
}

char Request[][128]={"Hello, I am pipe client",
					 "My name is Tom. What is your name?",
					 "Can you tell me something about pipe?",
					 "Thank you, Peter. Goodbye."};	

int main(int argc, char *argv[]) 
{
	if (argc<2)
		MyErrExit("CommandLine");
	HANDLE hPipe; 
	LPVOID lpvMessage; 
	CHAR chBuf[BUFFSIZE],chwBuf[BUFFSIZE];
	char name[20+BUFFSIZE]="Client ";
	BOOL fSuccess; 
	DWORD cbRead, cbWritten, dwMode;
	DWORD Messagesize;
	int xx=0;
	LPTSTR lpszPipename = "\\\\.\\pipe\\mynamedpipe";

	char mutexName[20]="smutex";
	strcat(mutexName,argv[1]);
	strcat(name,argv[1]);
	strcat(name," : ");
 
// Try to open a named pipe; wait for it, if necessary. 
 
	while (1) 
	{
		hPipe = CreateFile(
			lpszPipename,   // pipe name
			GENERIC_READ |  // read and write access
			GENERIC_WRITE,
			0,              // no sharing
			NULL,           // no security attributes
			OPEN_EXISTING,  // opens existing pipe
			0,              // default attributes
			NULL);          // no template file 
 
		// Break if the pipe handle is valid. 
 
		if (hPipe != INVALID_HANDLE_VALUE)
			break; 
 
		// Exit if an error other than ERROR_PIPE_BUSY occurs. 
 
		if (GetLastError() != ERROR_PIPE_BUSY)
			MyErrExit("1 Could not open pipe"); 
 
		// All pipe instances are busy, so wait for 20 seconds. 
 
		if (! WaitNamedPipe(lpszPipename, 20000) )
			MyErrExit("2 Could not open pipe"); 
	} 
 
// The pipe connected; change to message-read mode. 
 
	dwMode = PIPE_READMODE_MESSAGE; 
	fSuccess = SetNamedPipeHandleState(
		hPipe,    // pipe handle
		&dwMode,  // new pipe mode
		NULL,     // don't set maximum bytes
		NULL);    // don't set maximum time 
	if (!fSuccess)
		MyErrExit("SetNamedPipeHandleState"); 
 
// Send a message to the pipe server. 
 
	strcpy(chwBuf,name);
	strcat(chwBuf,Request[xx]);
	lpvMessage = chwBuf;
	Messagesize=strlen(chwBuf)+1;
 
	fSuccess = WriteFile(
		hPipe,			// pipe handle
		lpvMessage,		// message
		Messagesize,	// message length
		&cbWritten,		// bytes written
		NULL);			// not overlapped
	if (! fSuccess)
		MyErrExit("WriteFile"); 
 
	do 
	{
		fSuccess = ReadFile(
			hPipe,    // pipe handle
			chBuf,    // buffer to receive reply
			BUFFSIZE, // size of buffer
			&cbRead,  // number of bytes read
			NULL);    // not overlapped
 
		if (! fSuccess && GetLastError() != ERROR_MORE_DATA)
			MyErrExit("ReadFile");

		cout<<"Server : "<<chBuf<<endl;

		xx++;
		if (xx>3)
			break;

		strcpy(chwBuf,name);
		strcat(chwBuf,Request[xx]);
		lpvMessage = chwBuf;
		Messagesize=strlen(chwBuf)+1;

		fSuccess = WriteFile(
			hPipe,			// pipe handle
			lpvMessage,		// message
			Messagesize,	// message length
			&cbWritten,		// bytes written
			NULL);			// not overlapped
		if (! fSuccess)
			MyErrExit("WriteFile");

		Sleep(1000);//等待1000ms，为了便于观察并发执行的情况

	} while (fSuccess);//while (! fSuccess);  // repeat loop if ERROR_MORE_DATA 

	CloseHandle(hPipe);

	cout<<"\n ******** pipe client"<<argv[1]<<" will exit ********"<<endl;
	cout<<"\n Press Enter key to exit."<<endl;

	_flushall();		//清除缓冲区
	getchar();		//等待按键

	return 1; 
}