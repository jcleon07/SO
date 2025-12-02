#include <stdio.h>

/* ------------------------------------------
   1. Función: determinar si un número es par
------------------------------------------- */
int esPar(int n) {
    return n % 2 == 0;
}

/* ------------------------------------------
   2. Función: mayor de 3 números
------------------------------------------- */
int mayorDeTres(int a, int b, int c) {
    int mayor = a;
    if (b > mayor) mayor = b;
    if (c > mayor) mayor = c;
    return mayor;
}

/* ------------------------------------------
   3. Función: suma del 1 al n
------------------------------------------- */
int sumaHastaN(int n) {
    int suma = 0;
    for (int i = 1; i <= n; i++) suma += i;
    return suma;
}

/* ------------------------------------------
   4. Función: contar dígitos
------------------------------------------- */
int contarDigitos(int n) {
    if (n == 0) return 1;

    int count = 0;
    while (n != 0) {
        count++;
        n /= 10;
    }
    return count;
}

/* ------------------------------------------
   5. Función: determinar si un número es primo
------------------------------------------- */
int esPrimo(int n) {
    if (n <= 1) return 0;

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

/* ------------------------------------------
   6. Función: invertir un número
------------------------------------------- */
int invertirNumero(int n) {
    int invertido = 0;
    while (n != 0) {
        invertido = invertido * 10 + (n % 10);
        n /= 10;
    }
    return invertido;
}

/* ------------------------------------------
   7. Imprimir los primeros n términos de Fibonacci
------------------------------------------- */
void fibonacci(int n) {
    int a = 0, b = 1;
    for (int i = 0; i < n; i++) {
        printf("%d ", a);
        int temp = a + b;
        a = b;
        b = temp;
    }
    printf("\n");
}

/* ------------------------------------------
                 MAIN DEMO
   Puedes borrar esto si solo quieres funciones
------------------------------------------- */
int main() {
    printf("¿4 es par? %s\n", esPar(4) ? "Si" : "No");
    printf("Mayor de (3, 10, 7): %d\n", mayorDeTres(3, 10, 7));
    printf("Suma del 1 al 10: %d\n", sumaHastaN(10));
    printf("El número 503 tiene %d dígitos\n", contarDigitos(503));
    printf("¿17 es primo? %s\n", esPrimo(17) ? "Si" : "No");
    printf("Número invertido de 12345: %d\n", invertirNumero(12345));

    printf("Fibonacci (10 términos): ");
    fibonacci(10);

    return 0;
}
