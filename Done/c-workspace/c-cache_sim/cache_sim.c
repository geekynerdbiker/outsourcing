#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//some definitions
#define FALSE 0
#define TRUE 1
#define ADDR long long
#define DATA unsigned long
#define BOOL char

typedef struct _MEMREQUEST{
    ADDR addr;
    BOOL is_read;
} MEMREQUEST;

typedef enum _RPL{LRU=0, RAND=1} RPL;

////global variables///
long long hit_cnt=0;               //total number of cache hits
long long miss_cnt=0;              //total number of cache misses

int cache_size=32768;
int assoc=8;
int block_size=32;
RPL repl_policy=LRU;



//misc. function
FILE* fp = 0;
char trace_file[100]="memtrace.trc";
BOOL read_new_memaccess(MEMREQUEST*);  //read new memory access from the memory trace file (already implemented)

//TODO: implement this function
//configure a cache
void init_cache(int cache_size, int block_size, int assoc, RPL repl_policy){


}

//TODO: implement this function
//check if the memory request hits on the cache
BOOL isHit(MEMREQUEST request){

}

//TODO: implement this function
//insert a new block into the cache
ADDR insert_to_cache(MEMREQUEST request){

}

//TODO: update this function so that some simulation statistics are calculated in it
//print the simulation statistics
/*
 * Function: print_stat
 * --------------------------
 * print the simulation statistics
 *
 */
void print_stats()
{

    //print the simualtion statistics
    printf("\nSimulation statistics\n");
    printf("cache size: %dB\n", cache_size);
    printf("block_size: %dB\n", block_size);
    printf("associativity: %d\n",assoc);
    printf("replacement policy: ");
    if(repl_policy==LRU)
        printf("LRU\n");
    else
        printf("RAND\n");


    //TODO: Print simulation results
}


//main
int main(int argc, char*argv[])  
{
    int i=0;

	/*
    *  Read through command-line arguments for options.
    */
    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == 's') 
                cache_size=atoi(argv[i+1]);
            
            if (argv[i][1] == 'b')
                block_size=atoi(argv[i+1]);
            
            if (argv[i][1] == 'a')
                assoc=atoi(argv[i+1]);
            
            if (argv[i][1] == 'f')
                strcpy(trace_file,argv[i+1]);


            if (argv[i][1] == 'r')
            {
                if(strcmp(argv[i+1],"lru")==0)
                    repl_policy=LRU;
                else if(strcmp(argv[i+1],"rand")==0)
                    repl_policy=RAND;
                else
                {
                    printf("unsupported replacement policy:%s\n",argv[i+1]);
                    return -1;
                }           
            }
        }
    }
    
    // TODO
    // main body of cache simulator
    init_cache(cache_size, block_size, assoc, repl_policy);   //configure the cache with the cache parameters specified in the input arguments
    
    while(1)
	{
        MEMREQUEST new_access;
        
        BOOL success=read_new_memaccess(&new_access);  //read new memory access from the memory trace file
        
        if(success!=TRUE)   //check the end of the trace file
            break;        
        
        // TODO
        if(isHit(new_access)==FALSE)   //check if the new memory access hit on the cache
        {
            insert_to_cache(new_access);  //if miss, insert a cache block for the memory access to the cache
        }
	}
    
    print_stats();     //print simulation statistics    
    fclose(fp);

	return 0;
}


/*
 * Function: read_new_memrequest
 * ____________________________
 * read a new memory request from the memory trace file
 *
 */
BOOL read_new_memaccess(MEMREQUEST* mem_access)
{
    ADDR access_addr;
    char access_type[10];
    /*
     * open the mem trace file
     */

    if(fp==NULL)
    {
        fp=fopen(trace_file,"r");
        if(fp==NULL)
        {
            fprintf(stderr,"error opening file");
            exit(2);

        }   
    }

    if(mem_access==NULL)
    {
        fprintf(stderr,"MEMACCESS pointer is null!");
        exit(2);
    }

    if(fscanf(fp,"%s %llx", &access_type, &access_addr)!=EOF)
    {
        mem_access->addr=access_addr;
        if(strcmp(access_type,"R")==0)
            mem_access->is_read=TRUE;
        else
            mem_access->is_read=FALSE;
        
        return TRUE;
    }       
    else
        return FALSE;

}



