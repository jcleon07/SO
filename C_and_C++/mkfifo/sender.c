#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main() {

	int res, n;
	res = open("fifo1",O_WRONLY);
	write(res,"Mensaje",7);
	printf("Sender process con PID %d envio la informacion\n",getpid());

return 0;
}
