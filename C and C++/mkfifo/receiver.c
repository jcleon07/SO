#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main() {

	int res,n;
	char buffer[100];
	res = open("fifo1",O_RDONLY);
	n = read(res,buffer,100);
	printf("Proceso lector con PID %d inicio\n",getpid());
	printf("La informacion recibida por el receptor %d es: %s\n", getpid(), buffer);

return 0;
}
