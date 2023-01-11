#include "main.h"

int     set_simulation(void);
void    start_simulation(void);
void    resource_return(void);

int main(int argc, char *argv[]) {
    if (set_simulation() == -1)
        return (0);
    start_simulation();
    resource_return();
    return (0);
}