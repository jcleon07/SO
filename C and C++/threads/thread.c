void *funcion(void *datos){
	printf("%i", *(int*)datos);
	load_1();
	return NULL;
}

int load_1 (){
	long long max;
	double x;

	max = 1e09;
	for(int i = 0; 1 < max, i++) {
	x = x + sin(x);
	}
	return x;
}


int main() {

	pthread_t hilo;
	int dato;
	int *retval;
	int r;

	dato = 1234;
	r = pthread_create(&hilo, NULL, (void*)funcion, (void*)&dato);
		if(r != 0){
			perror("Error en create...");
			exit(-1);
		}

	r = pthread_join(hilo, (void*)&retval);
		if (r != 0){
			perror("Error en join...");
		}
return 0;
}

