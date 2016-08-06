#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <excpt.h>

int main(int argc, char **argv)
{
	if (IsDebuggerPresent())
	{
		printf("Debugger Detected");
		MessageBox(0,"I'm just another clean game application :D","*Debugger Detected*",MB_OK);
		system("%SystemRoot%\\System32\\winmine.exe");
		exit(0);
	}
	printf("No Debugger");
	MessageBox(0,"You're normal user, you're now infected with this deadly virus","*Debugger Not Detected*",MB_OK);
	system("%SystemRoot%\\System32\\winmine.exe");
	return 0;
}
