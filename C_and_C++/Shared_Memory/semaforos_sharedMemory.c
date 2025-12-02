#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/wait.h>

#define SHM_NAME "/mi_memoria"
#define SEM_HIJO "/sem_hijo"
#define SEM_PADRE "/sem_padre"

int main() {
    int shm_fd;
    int *dato;

    // Crear memoria compartida
    shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("Error al crear shm");
        exit(1);
    }

    // Tamaño de la memoria
    if (ftruncate(shm_fd, sizeof(int)) == -1) {
        perror("Error en ftruncate");
        exit(1);
    }

    // Mapear memoria
    dato = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (dato == MAP_FAILED) {
        perror("Error en mmap");
        exit(1);
    }

    // Crear semáforos POSIX
    sem_t *sem_hijo = sem_open(SEM_HIJO, O_CREAT, 0666, 1);  // hijo comienza
    sem_t *sem_padre = sem_open(SEM_PADRE, O_CREAT, 0666, 0); // padre espera
    if (sem_hijo == SEM_FAILED || sem_padre == SEM_FAILED) {
        perror("Error creando semáforos");
        exit(1);
    }

    pid_t pid = fork();

    if (pid == 0) {
        // ===========================
        //        PROCESO HIJO
        // ===========================
        for (int i = 1; i <= 5; i++) {

            sem_wait(sem_hijo);   // Espera turno del hijo

            *dato = i;  // Escribe en memoria compartida
            printf("[Hijo] Escribí: %d\n", i);

            sem_post(sem_padre);  // Despierta al padre
            sleep(1);
        }

        exit(0);
    }
    else {
        // ===========================
        //        PROCESO PADRE
        // ===========================
        for (int i = 0; i < 5; i++) {
            sem_wait(sem_padre);  // Espera turno del padre

            printf("[Padre] Leí: %d\n", *dato);

            sem_post(sem_hijo);   // Despierta al hijo
        }

        wait(NULL);

        // LIMPIEZA
        sem_close(sem_hijo);
        sem_close(sem_padre);
        sem_unlink(SEM_HIJO);
        sem_unlink(SEM_PADRE);

        munmap(dato, sizeof(int));
        shm_unlink(SHM_NAME);

        printf("\nMemoria y semáforos eliminados correctamente.\n");
    }

    return 0;
}
