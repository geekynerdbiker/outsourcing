#include "types.h"
#include "user.h"
#include "stat.h"
#include "time.h"


int main(int argc, char *argv[])
{
	//setnice(getpid(),5);
	int pid = fork();
	if(pid > 0)
	{
		setnice(getpid(),5);
		ps(0);
		while(1)
		{
			ps(0);
			//sleep(10);
		}
	}
	else
	{
		int pid2 = fork();
		if(pid2 > 0)
		{
			while(1)
			{
		//		ps(0);
			}
		}
		else
		{
			while(1)
			{
			//	ps(0);
			}
		}
	}
}



