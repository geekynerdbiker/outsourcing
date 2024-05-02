/* mycode4.c: your portion of the kernel
 *
 *   	Below are functions that are called by other parts of the kernel. 
 * 	Your ability to modify the kernel is via these functions.  You may
 *  	modify the bodies of these functions (and add code outside of them)
 * 	in any way you desire, but you must not change their interfaces. 
 */

#include "aux.h"
#include "sys.h"
#include "mycode4.h"

#define FALSE 0
#define TRUE 1

/*  	A sample semaphore table.  You may modify this in any way you wish. 
 */

int processes;
static struct {
	int valid;	// Is this a valid entry (was sem allocated)?
	int value;	// value of semaphore
    int procs[MAXPROCS + 1];
    int head;
    int tail;
    int size;
} semtab[MAXSEMS];


/* 	InitSem () is called when the kernel starts running.  Initialize data
 *  	structures (such as the semaphore table) and call any initialization
 *   	functions here. 
 */

void InitSem ()
{
	int s;

	/* modify or add code any way you wish */

	for (s = 0; s < MAXSEMS; s++) {		// mark all sems free
		semtab[s].valid = FALSE;
        semtab[s].size = 0;
        semtab[s].head = semtab[s].tail = 0;
	}
}

/* 	MySeminit (v) is called by the kernel whenever the system call
 *  	Seminit (v) is called.  The kernel passes the initial value v. 
 * 	MySeminit should allocate a semaphore (find a free entry in
 *  	semtab and allocate), initialize that semaphore's value to v,
 * 	and then return the ID (i.e., index of the allocated entry).  
 *  	Should return -1 if it fails (e.g., no free semaphores). 
 */

int MySeminit (int v)
	// v: initial value of semaphore
{
	int s;

	/* modify or add code any way you wish */

	for (s = 0; s < MAXSEMS; s++) {
		if (semtab[s].valid == FALSE) {
			break;
		}
	}
	if (s == MAXSEMS) {
		DPrintf ("No free semaphores\n");
		return (-1);
	}

	semtab[s].valid = TRUE;
	semtab[s].value = v;

	return (s);
}

/*   	MyWait (s) is called by the kernel whenever the system call
 * 	Wait (s) is called.  Return 0 if successful, else -1 if failed. 
 */

int MyWait (int s)
	// s: semaphore ID
{
	/* modify or add code any way you wish */
    if (s <= -1 || s >= MAXSEMS || !semtab[s].valid)
        return (0);

	semtab[s].value--;
    if (semtab[s].value < 0) {
        int p = GetCurProc();
        
        semtab[s].procs[semtab[s].tail] = p;
        semtab[s].tail = (semtab[s].tail + 1) % (MAXPROCS + 1);
        semtab[s].size = semtab[s].size + 1;
        Block();
        }

	return (0);
}

/*  	MySignal (s) is called by the kernel whenever the system call
 * 	Signal (s) is called.  Return 0 if successful, else -1 if failed. 
 */

int MySignal (int s)
	// s: semaphore ID
{
	/* modify or add code any way you wish */
    if (s <= -1 || s >= MAXSEMS || !semtab[s].valid)
        return (0);

	semtab[s].value++;
    if (semtab[s].size > 0) {
        int p = semtab[s].procs[semtab[s].head];

        semtab[s].head = (semtab[s].head + 1) % (MAXPROCS + 1);
        semtab[s].size = semtab[s].size - 1;
        Unblock(p);
    }
	return (0);
}
