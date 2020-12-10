#include <windows.h>
#include <iostream>

using namespace std;
 
#define BUFSIZE 128
#define PIPE_TIMEOUT 2000

HANDLE createProcess(char* name,int num);
VOID MyErrExit(char *);
DWORD InstanceThread(LPVOID);
DWORD WorkThread(LPVOID);

char Reply[][128] = {"Hello, I am pipe server",
					 "My name is Peter. Tom, welcome.",
					 "Certianly, pipe can be used in\n\t interprocess communication.",
					 "Bye-bye, Tom."};
int threadNo=0;		// serial number of thread instance 

CRITICAL_SECTION cs_Screen;	// CRITICAL_SECTION object

// The following example is a multithreaded pipe server. It has
// a main thread with a loop that creates a pipe instance and
// waits for a pipe client to connect. When a pipe client
// connects, the pipe server creates a thread to service that
// client and then continues to execute the loop. It is
// possible for a pipe client to connect successfully to the
// pipe instance in the interval between calls to the
// CreateNamedPipe and ConnectNamedPipe functions. If this
// happens, ConnectNamedPipe returns zero, and GetLastError
// returns ERROR_PIPE_CONNECTED. 
// The thread created to service each pipe instance reads
// requests from the pipe and writes replies to the pipe
// until the pipe client closes its handle. When this
// happens, the thread flushes the pipe, disconnects,
// closes its pipe handle, and terminates.


int main() // Pipe Server
{
	BOOL fConnected;
	DWORD dwThreadId;
	HANDLE hPipe,hThrd,hwkThd;
	int nProcess=3;		// number of pipe client
	// name of the pipe	
	LPTSTR lpszPipename = "\\\\.\\pipe\\mynamedpipe";

	// init. CRITICAL_SECTION object cs_Screen
	InitializeCriticalSection(&cs_Screen);
   
	HWND hWindow;
	// obtain a handle to the foreground window
	hWindow=GetForegroundWindow();
	// changes the position and dimensions of the specified window
	MoveWindow(hWindow,0,10,750,385,TRUE);
	// create a thread. it create processes of pipe client
	hwkThd=CreateThread( 
            NULL,              // no security attribute 
            0,                 // default stack size 
            (LPTHREAD_START_ROUTINE) WorkThread, 
            (LPVOID) nProcess, // thread parameter 
            0,                 // not suspended 
            &dwThreadId);      // returns thread ID 

	if (hwkThd == NULL)
		MyErrExit("CreateThread1");

// The main loop creates an instance of the named pipe and 
// then waits for a client to connect to it. When the client 
// connects, a thread is created to handle communications 
// with that client, and the loop is repeated. 
 
   for (;;) // main loop
   {
	   // create an instance of the named pipe
	   hPipe = CreateNamedPipe( 
          lpszPipename,             // pipe name 
          PIPE_ACCESS_DUPLEX,       // read/write access 
          PIPE_TYPE_MESSAGE |       // message type pipe 
          PIPE_READMODE_MESSAGE |   // message-read mode 
          PIPE_WAIT,                // blocking mode 
          PIPE_UNLIMITED_INSTANCES, // max. instances  
          BUFSIZE,                  // output buffer size 
          BUFSIZE,                  // input buffer size 
          PIPE_TIMEOUT,             // client time-out 
          NULL);                    // no security attribute 

		if (hPipe == INVALID_HANDLE_VALUE)
			MyErrExit("CreatePipe"); 
 
		// Wait for the client to connect; if it succeeds, 
		// the function returns a nonzero value. If the function returns 
		// zero, GetLastError returns ERROR_PIPE_CONNECTED. 
 
		fConnected = ConnectNamedPipe(hPipe, NULL) ? 
			TRUE : (GetLastError() == ERROR_PIPE_CONNECTED); 
 
		if (fConnected) 
		{
			// Create a thread for this client. 
			threadNo++;
			hThrd = CreateThread(
				NULL,              // no security attribute
				0,                 // default stack size
				(LPTHREAD_START_ROUTINE) InstanceThread,
				(LPVOID) hPipe,    // thread parameter
				0,                 // not suspended
				&dwThreadId);      // returns thread ID 
			if (hThrd == NULL)
				MyErrExit("CreateThread2");
		} 
		else 
        // The client could not connect, so close the pipe. 
		CloseHandle(hPipe); 
	} 
	return 1; 
} 
 
DWORD InstanceThread(LPVOID lpvParam) 
{
	int nThread=threadNo;
	CHAR chRequest[BUFSIZE];
	CHAR chReply[BUFSIZE];
	DWORD cbBytesRead, cbReplyBytes, cbWritten;
	BOOL fSuccess;
	int index=0;
	HANDLE hPipe; 
 
// The thread's parameter is a handle to a pipe instance. 
 
	hPipe = (HANDLE) lpvParam;
 
	while (1)
	{
		// Read client requests from the pipe. 
		fSuccess = ReadFile(
			hPipe,			// handle to pipe
			chRequest,		// buffer to receive data
			BUFSIZE,		// size of buffer
			&cbBytesRead,	// number of bytes read
			NULL);			// not overlapped I/O
		if (! fSuccess || cbBytesRead == 0)
			break;

		EnterCriticalSection(&cs_Screen);
		cout<<chRequest<<endl;
		LeaveCriticalSection(&cs_Screen);
		strcpy(chReply,Reply[index]);
		cbReplyBytes=strlen(Reply[index])+1;

		index=(index+1)%4;
		
		// Write the reply to the pipe.
		fSuccess = WriteFile(
			hPipe,			// handle to pipe
			chReply,		// buffer to write from
			cbReplyBytes,	// number of bytes to write
			&cbWritten,		// number of bytes written
			NULL);			// not overlapped I/O

		if (! fSuccess || cbReplyBytes != cbWritten)
			MyErrExit("Write the pipe failrd.");

		Sleep(1000); //等待1000ms，为了便于观察并发执行的情况
	}
 
	// Flush the pipe to allow the client to read the pipe's contents 
	// before disconnecting. Then disconnect the pipe, and close the 
	// handle to this pipe instance. 
 
	FlushFileBuffers(hPipe); 
	DisconnectNamedPipe(hPipe); 
	CloseHandle(hPipe);
	EnterCriticalSection(&cs_Screen);
	cout<<"\n ****** InstanceThread "
		<<nThread<<" exit."<<endl<<endl;
	LeaveCriticalSection(&cs_Screen);
	return 1;
}

DWORD WorkThread(LPVOID lpPara)
{
	int nClint=(int)lpPara;

	char name[20]="PipeClient";
	for (int i=1; i<=nClint; i++) // create pipe client
	{
		createProcess(name,i);
	}
	return 1;
}

HANDLE createProcess(char *name,int num)
{
	static int position=1;
	char cmdline[256];
	char ich[8];
	itoa(num,ich,10);		// number of process to string
	strcpy(cmdline,name);
	strcat(cmdline," ");
	strcat(cmdline,ich);	// command-line

	STARTUPINFO si={sizeof(STARTUPINFO)};
	si.dwFlags=STARTF_USEPOSITION|	// enable dwX and dwY
		STARTF_USESIZE|				// enable dwXSize and dwYSize
		STARTF_USEFILLATTRIBUTE;	// enable dwFillAttribute
	si.dwXSize=365;		// width, in pixels, of the window
	si.dwYSize=380;		// height, in pixels, of the window
	si.lpTitle=cmdline;	// title of window
	// produces blue text on a whilte background
	si.dwFillAttribute=FOREGROUND_BLUE|BACKGROUND_RED| BACKGROUND_GREEN| BACKGROUND_BLUE;
	PROCESS_INFORMATION pi;
	DWORD dwx=0,dwy=0;	// the upper left corner of a window
	switch (position)
	{
	case 0 : si.dwX=dwx+770;	// the upper left corner of a window 0
			 si.dwY=dwy;
			 break;
	case 1 : si.dwX=dwx;		// the upper left corner of a window 1
			 si.dwY=dwy+400;
			 break;
	case 2 : si.dwX=dwx+385;	// the upper left corner of a window 2
			 si.dwY=dwy+400;
			 break;
	case 3 : si.dwX=dwx+770;	// the upper left corner of a window 3
			 si.dwY=dwy+400;
			 break;
	}
	
	BOOL fsuccess=CreateProcess(
		NULL,	// no executable module
		cmdline,// command line string
		NULL,	// the returned handle cannot be inherited by child processes
		NULL,	// the returned handle cannot be inherited by child processes
		TRUE,	// each inheritable open handle in the calling
				// process is inherited by the new process
		NORMAL_PRIORITY_CLASS|CREATE_NEW_CONSOLE,
				// The new process has a new console
		NULL,	// new process uses the environment of the calling process
		NULL,	// new process is created with the same current drive 
				// and directory as the calling process
		&si,	// Pointer to a STARTUPINFO structure that specifies how
				// the main window for the new process should appear
		&pi		// Pointer to a PROCESS_INFORMATION structure that receives
				// identification information about the new process
		);
	if (!fsuccess)
		MyErrExit("CreateProcess");

	position=(position+1)%4;

	return pi.hThread;
}

VOID MyErrExit(char *Err)
{
	EnterCriticalSection(&cs_Screen);
	cout<<"Error : "<<Err<<endl;
	LeaveCriticalSection(&cs_Screen);
	exit(0);
}