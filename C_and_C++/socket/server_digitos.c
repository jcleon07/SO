#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

pthread_mutex_t mutex;

// ===== Función de lógica (compartida por todos los hilos) =====
int sumaDigitos(int n) {
    int suma = 0;
    while (n != 0) {
        suma += n % 10;
        n /= 10;
    }
    return suma;
}

// ===== Hilo que atiende a cada cliente =====
void* atender_cliente(void* arg) {
    int socket_cliente = *(int*)arg;
    free(arg);

    int numero;
    int leido = read(socket_cliente, &numero, sizeof(int));
    if (leido <= 0) {
        close(socket_cliente);
        return NULL;
    }

    printf("[Servidor] Recibido: %d\n", numero);

    // Zona crítica protegida
    pthread_mutex_lock(&mutex);
    int resultado = sumaDigitos(numero);
    pthread_mutex_unlock(&mutex);

    printf("[Servidor] Resultado enviado: %d\n", resultado);

    write(socket_cliente, &resultado, sizeof(int));
    close(socket_cliente);

    return NULL;
}

int main() {
    int server_fd, nuevo_socket;
    struct sockaddr_in direccion;
    pthread_mutex_init(&mutex, NULL);

    // Crear socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Error creando socket");
        exit(1);
    }

    direccion.sin_family = AF_INET;
    direccion.sin_addr.s_addr = INADDR_ANY;
    direccion.sin_port = htons(8080);

    // Enlazar
    if (bind(server_fd, (struct sockaddr*)&direccion, sizeof(direccion)) < 0) {
        perror("Error en bind");
        exit(1);
    }

    // Escuchar
    listen(server_fd, 5);
    printf("Servidor escuchando en puerto 8080...\n");

    while (1) {
        nuevo_socket = accept(server_fd, NULL, NULL);

        int* pcliente = malloc(sizeof(int));
        *pcliente = nuevo_socket;

        pthread_t hilo;
        pthread_create(&hilo, NULL, atender_cliente, pcliente);
        pthread_detach(hilo);  // libera automáticamente recursos del hilo
    }

    pthread_mutex_destroy(&mutex);
    close(server_fd);
    return 0;
}
