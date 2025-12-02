#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock;
    struct sockaddr_in server_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Error creando socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error conectando al servidor");
        exit(1);
    }

    int numero;
    printf("Ingrese un número para calcular la suma de dígitos: ");
    scanf("%d", &numero);

    write(sock, &numero, sizeof(int));

    int respuesta;
    read(sock, &respuesta, sizeof(int));

    printf("La suma de los dígitos es: %d\n", respuesta);

    close(sock);
    return 0;
}
