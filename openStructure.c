#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "/home/kromatic/Documents/C/IndividuoStructure.h"

int main() {
//Se define la estructura
    struct Individuo individuo1;
    FILE *archivo;
    archivo = fopen("individuo.txt", "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    size_t elementos_leidos = fread(&individuo1, sizeof(struct Individuo), 1, archivo);
    if (elementos_leidos == 1) {
        printf("Nombre: %s\n", individuo1.nombre);
        printf("Apellido: %s\n", individuo1.apellido);
        printf("Edad: %d\n", individuo1.edad);
        printf("Estatura: %.2f\n", individuo1.estatura);
    } else {
        printf("Error al leer los datos del archivo.\n");
    }
    
    fclose(archivo);

    return 0;
}