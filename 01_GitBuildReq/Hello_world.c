#include <stdio.h>

int main() {
    char str[255];
    fgets(str, 255, stdin);
    printf("Hello, %s\n", str);
    return 0;
}
