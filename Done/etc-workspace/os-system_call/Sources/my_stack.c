#include<linux/unistd.h>

#define my_stack_push 335
#define my_stack_pop 336

void push(int data){
    printf("Push: %d\n",data);
    syscall(my_stack_push,data);
}

void pop(){
    printf("Pop: %d\n", syscall(my_stack_pop));
}

int main(void){
    push(1);
    push(1);
    push(2);
    push(3);

    pop();
    pop();
    pop();

    return 0;
} 
