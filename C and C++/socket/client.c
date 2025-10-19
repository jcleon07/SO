#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 3539
#define BACKLOG 4 


int main() {
    struct sockaddr_in server, cliente;
    int fd, r;
    char buffer[20];

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1){
        perror("Error al crear el socket");
        exit(-1);
    }
    
    cliente.sin_family = AF_INET;
    cliente.sin_port = htons(PORT);
    cliente.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    bzero(&server.sin_zero,8);
    
    r = connect(fd,(struct sockaddr *)&cliente, sizeof(struct sockaddr_in));
    if (r == -1){
        perror("Error al conectar");
        exit(-1);
    }

    r = recv(fd, buffer, sizeof(buffer) - 1, 0);
    buffer[r] = '\0';
    printf("%s", buffer);
    
    r = send(fd, "hola servidor", 13, 0);
    if (r == -1){
        perror("Error al enviar");
        exit(-1);
    }
    
    close(fd);
    
    return 0;
}
