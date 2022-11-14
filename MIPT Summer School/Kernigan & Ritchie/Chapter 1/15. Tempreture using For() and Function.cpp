#include <stdio.h>
int fic (int fahrad);

main(){
    int fahr;

    printf("Fahr into Celsius\n");
    for (fahr = 300; fahr >= 0; fahr = fahr - 20)
        printf("%4d  -- %4d\n", fahr, fic(fahr));
    return 0;
}

int fic (int fahrad){
    int celsius;
    celsius = (fahrad-32)*(5.0/9.0);
    return celsius;
}
