#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5   // Tamaño del buffer circular

int buffer[BUFFER_SIZE];
int in = 0;      // Índice de escritura
int out = 0;     // Índice de lectura
int count = 0;   // Elementos actuales en el buffer

pthread_mutex_t mutex;
pthread_cond_t cond_lleno;
pthread_cond_t cond_vacio;

// =============================
//     HILO PRODUCTOR
// =============================
void* productor(void* arg) {
    int item = 1;

    while (item <= 15) {
        pthread_mutex_lock(&mutex);

        // Esperar si el buffer está lleno
        while (count == BUFFER_SIZE) {
            printf("[Productor] Buffer lleno, esperando...\n");
            pthread_cond_wait(&cond_vacio, &mutex);
        }

        // Insertar en buffer
        buffer[in] = item;
        printf("[Productor] Produje: %d en posición %d\n", item, in);

        in = (in + 1) % BUFFER_SIZE;
        count++;

        // Avisar al consumidor que hay datos
        pthread_cond_signal(&cond_lleno);
        pthread_mutex_unlock(&mutex);

        item++;
        sleep(1);
    }

    return NULL;
}

// =============================
//     HILO CONSUMIDOR
// =============================
void* consumidor(void* arg) {
    for (int i = 0; i < 15; i++) {

        pthread_mutex_lock(&mutex);

        // Esperar si el buffer está vacío
        while (count == 0) {
            printf("    [Consumidor] Buffer vacío, esperando...\n");
            pthread_cond_wait(&cond_lleno, &mutex);
        }

        // Consumir
        int item = buffer[out];
        printf("    [Consumidor] Consumí: %d de posición %d\n", item, out);

        out = (out + 1) % BUFFER_SIZE;
        count--;

        // Avisar al productor que hay espacio
        pthread_cond_signal(&cond_vacio);
        pthread_mutex_unlock(&mutex);

        usleep(500000); // 0.5 segundos
    }

    return NULL;
}

// =============================
//             MAIN
// =============================
int main() {
    pthread_t hiloProd, hiloCons;

    // Inicializar mutex y condiciones
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_lleno, NULL);
    pthread_cond_init(&cond_vacio, NULL);

    // Crear hilos
    pthread_create(&hiloProd, NULL, productor, NULL);
    pthread_create(&hiloCons, NULL, consumidor, NULL);

    // Esperar hilos
    pthread_join(hiloProd, NULL);
    pthread_join(hiloCons, NULL);

    // Limpieza
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_lleno);
    pthread_cond_destroy(&cond_vacio);

    printf("\nPrograma terminado correctamente.\n");

    return 0;
}
