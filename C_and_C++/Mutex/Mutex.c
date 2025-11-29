/* Ejemplo de manejo de hilos
 * Compilar con threads: -lpthread
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>  // Para sleep()

#define MAX_PROCESOS 1
#define NUM_HILOS 1000

pthread_mutex_t mutex;

struct datos_tipo {
    int dato;
    int p;
};

void* proceso(void* datos) {
    struct datos_tipo* datos_proceso;
    datos_proceso = (struct datos_tipo *)datos;

    int a, i, p;
    a = datos_proceso->dato;
    p = datos_proceso->p;

//−−−>
    pthread_mutex_lock(&mutex);
    // Impresión del dato
    for (i = 0; i <= p; i++) {
        printf(" %i ", a);
    }
    fflush(stdout);
    sleep(1);

    // Impresión de guiones
    for (i = 0; i <= p; i++) {
        printf("− ");
    }
    fflush(stdout);
    pthread_mutex_unlock(&mutex);
//−−−>

    return NULL;  // Se debe retornar algo desde las funciones de hilo
}

int main() {
    int error, i;
    char* valor_devuelto;

    /* Variables para hilos */
    struct datos_tipo hilo_datos[NUM_HILOS];
    pthread_t idhilo[NUM_HILOS];

    pthread_mutex_init(&mutex,NULL);
    // Inicialización de datos para cada hilo
    for (i = 0; i < NUM_HILOS; i++) {
        hilo_datos[i].dato = i;
        hilo_datos[i].p = i+1;
    }

    /* Se lanzan los hilos */
    for (i = 0; i < NUM_HILOS; i++) {
        error = pthread_create(&idhilo[i], NULL,(void*) proceso, (void*)&hilo_datos[i]);
        if (error != 0) {
            perror("No puedo crear hilo");
            exit(-1);
        }
     sleep(1);
    }

    /* Esperar a que terminen */
    for (i = 0; i < NUM_HILOS; i++) {
        pthread_join(idhilo[i], (void**)&valor_devuelto);
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}
