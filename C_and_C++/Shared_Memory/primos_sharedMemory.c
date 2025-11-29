#include <stdio.h>
#include <stdlib.h> 
#include <stdarg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>
#include <wait.h>

int a;

int esPrimo(int n) {

    int count = 0;

    if (n == 1) {
        return 0;
    } else if (n == 2) {
        return 1;
    }else{
        for (int i = 2; i <= n; i++){
            if (n % i == 0) {
                count++;
            }
        }
        if (count == 1) {
            return 1;
        } else {
            return 0;
        }       
    }
}


int main() {
    key_t key = 12345;
    int *ap;
    int shmId;
    int status;
    pid_t pid;

    scanf("%d", &a);

    //Creacion shared memory
    shmId = shmget(key, sizeof(int), 0666 | IPC_CREAT);
    if (shmId < 0){
        perror("Error al crear el shm");
        exit(-1);
    }

    ap = shmat(shmId, 0, 0);
    *ap = a;

    pid = fork();

    //Validacion error
    if (pid < 0){
        perror("Error al crear el pip");
        exit(-1);
    }



    //Proceso hijo
    if (pid == 0){

        int counter = 0;

        FILE *archivo = fopen("primos.txt","w");
        if (archivo == 0){
            perror("Error al abrir el archivo");
            exit(-1);
        }

        for (int i = 1; i < *ap/2; i++ ){
           counter += esPrimo(i);
    }
    fprintf(archivo, "%d", counter);    

    fclose(archivo);

    shmdt(ap);
    exit(0);



    //Proceso padre
    }  else {
       wait(&status);

        FILE *archivo = fopen("primos.txt", "r");
            if (archivo == 0){
                perror("Error al abrir el archivo");
                exit(-1);
            }

        int counter;
        fscanf(archivo, "%d", &counter);
        fclose(archivo);

        int counter2 = 0;

        for (int i = *ap/2; i <= *ap; i++ ){

        counter2 += esPrimo(i);
        }

        int total = counter + counter2;

        printf("Hay: %d primos hasta el numero %d\n", total, a);

    }

    shmdt(ap);
    shmctl(shmId, IPC_RMID, NULL);

    return 0;
}