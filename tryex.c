#include "ourshell.h"

void builtin_exit()
{
    exit(0);
}

int main()
{

    builtin_exit();
    
    return 0;
}
