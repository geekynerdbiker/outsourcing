#include<linux/syscalls.h>
#include<linux/kernel.h>
#include<linux/linkage.h>

#define LENGTH 5
int stack[LENGTH];
int top = -1;

SYSCALL_DEFINE1(my_push,int,data){
    if( top < LENGTH ){
        stack[++top] = data;
    }
    int i;
    printk("[System call] my_push(): Push %d\n",data);
    printk("Stack Top--------------\n");
    for(i = top; i>=0; i--){
        printk("%d\n", stack[i]);
    }
    printk("Stack Bottom-----------\n");
}

SYSCALL_DEFINE0(my_pop){    
    if(top != -1){
    int tmp = stack[top--]; 
    int i;
    printk("[System call] my_pop(): Pop %d\n",tmp);
    printk("Stack Top--------------\n");
    for(i = top; i>=0; i--){
        printk("%d\n", stack[i]);
    }
    printk("Stack Bottom-----------\n");

    return tmp;
    }
}