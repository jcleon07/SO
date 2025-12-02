#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int contador = 0;           // Variable compartida
pthread_mutex_t mutex;      // Mutex para sincronización

void* productor(void* arg) {
    for (int i = 1; i <= 10; i++) {

        pthread_mutex_lock(&mutex);   // Bloquea el acceso
        contador++;
        printf("[Productor] Contador incrementado a: %d\n", contador);
        pthread_mutex_unlock(&mutex); // Libera el acceso

        sleep(1);
    }
    return NULL;
}

void* consumidor(void* arg) {
    for (int i = 1; i <= 10; i++) {

        pthread_mutex_lock(&mutex);   // Bloquea para lectura segura
        printf("    [Consumidor] Lee contador: %d\n", contador);
        pthread_mutex_unlock(&mutex); // Libera

        usleep(400000); // 0.4 segundos
    }
    return NULL;
}

int main() {
    pthread_t hilo1, hilo2;

    // Inicializar mutex
    pthread_mutex_init(&mutex, NULL);

    // Crear hilos
    pthread_create(&hilo1, NULL, productor, NULL);
    pthread_create(&hilo2, NULL, consumidor, NULL);

    // Esperar hilos
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    // Destruir mutex
    pthread_mutex_destroy(&mutex);

    printf("\nPrograma finalizado.\n");
    return 0;
}
