#include <stdio.h>

/* ============================================
   1. Sumar los dígitos de un número
   Ejemplo: 135 → 1 + 3 + 5 = 9
============================================= */
int sumaDigitos(int n) {
    int suma = 0;
    while (n != 0) {
        suma += n % 10;
        n /= 10;
    }
    return suma;
}

/* ============================================
   2. Verificar si un número es palíndromo
============================================= */
int esCapicua(int n) {
    int original = n, invertido = 0;

    while (n > 0) {
        invertido = invertido * 10 + (n % 10);
        n /= 10;
    }

    return original == invertido;
}

/* ============================================
   3. Encontrar el MCD (Máximo Común Divisor)
   usando el algoritmo de Euclides
============================================= */
int mcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/* ============================================
   4. Contar cuantos números pares hay en un arreglo
============================================= */
int contarPares(int arr[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) count++;
    }
    return count;
}

/* ============================================
   5. Calcular el factorial usando recursividad
============================================= */
long long factorial(int n) {
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

/* ============================================
   6. Verificar si una cadena es palíndromo
   (sin usar funciones de string.h)
============================================= */
int esPalindromo(const char* s) {
    int i = 0;
    int j = 0;

    // Obtener longitud
    while (s[j] != '\0') j++;
    j--;

    // Comparar
    while (i < j) {
        if (s[i] != s[j]) return 0;
        i++;
        j--;
    }

    return 1;
}

/* ============================================
   7. Obtener el segundo mayor de un arreglo
============================================= */
int segundoMayor(int arr[], int n) {
    if (n < 2) return -1; // No válido

    int mayor = arr[0];
    int segundo = -2147483648; // MIN int

    for (int i = 1; i < n; i++) {
        if (arr[i] > mayor) {
            segundo = mayor;
            mayor = arr[i];
        } else if (arr[i] > segundo && arr[i] != mayor) {
            segundo = arr[i];
        }
    }

    return segundo;
}

/* ============================================
                MAIN DEMO
   Puedes borrarlo si solo quieres las funciones
============================================= */
int main() {
    printf("Suma de dígitos de 357: %d\n", sumaDigitos(357));
    printf("¿Es palindromo 1221?: %s\n", esCapicua(1221) ? "Sí" : "No");
    printf("MCD de 48 y 18: %d\n", mcd(48, 18));

    int arr[] = {3, 8, 2, 9, 12, 7};
    printf("Cantidad de pares en arreglo: %d\n", contarPares(arr, 6));

    printf("Factorial de 6: %lld\n", factorial(6));

    printf("¿Es palíndromo 'ana'?: %s\n", esPalindromo("ana") ? "Sí" : "No");

    int arr2[] = {5, 17, 3, 9, 15};
    printf("Segundo mayor: %d\n", segundoMayor(arr2, 5));

    return 0;
}
