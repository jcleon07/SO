#include <unistd.h>
#include <stdio.h>

int var = 22;

int main(void) {

    pid_t pidA;
    printf("** proc. PID =  %d comienza ** \n", getpid());
    pidA = fork();

    printf("proc. PID = %d , pidA = %d ejecutandose \n", getpid(), pidA);
    
    if(pidA > 0) {
        var = 15;
    }
    else if (pidA == 0) {
        var = 5;
    }
    else /*error*/ {

    }   

    //Bucle infinito
    while (1) {
        sleep(2);
        printf("proc. PID = %d, var = %d ejecutandose \n", getpid(), var);
    }
    return 0;
}
