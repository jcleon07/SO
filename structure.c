#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "/home/kromatic/Documents/C/IndividuoStructure.h"


int main() {
    //Se declara una variable de tipo estructura
    struct Individuo individuo1;
    FILE *archivo;
    
    // Se asignan los valores a la estructura
    strcpy(individuo1.nombre, "Juan");
    strcpy(individuo1.apellido, "Lopez");
    individuo1.edad = 20;
    individuo1.estatura = 1.69;

    // Se abre el archivo en modo escritura binaria
    archivo = fopen("individuo.txt", "wb");
    
    // Verificar si el archivo se abrió correctamente
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo para escritura.\n");
        return 1;
    }

    // Se escribe la estructura al archivo
    size_t elementos_escritos = fwrite(&individuo1, sizeof(struct Individuo), 1, archivo);
    
    if (elementos_escritos == 1) {
        printf("Datos guardados exitosamente en el archivo 'individuo.txt'\n");
    } else {
        printf("Error al escribir los datos en el archivo.\n");
    }


    return 0;
}