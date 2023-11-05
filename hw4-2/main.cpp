#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Определить местоположение элементов массива А (30), не встречающихся в массиве В (15).


int main()
{

    int mass_A[30];
    int mass_B[15];

    srand(time(NULL));

    for(int i = 0; i < 30; ++i){
        mass_A[i] = rand() % 30;
    }
    for(int k = 0; k < 15; ++k){
        mass_B[k] = rand() % 15;
    }

    printf("A: ");
    for(int i = 0; i < 30; ++i){
    printf("%3d", mass_A[i]);
    }
    printf("\n");
    printf("B: ");
    for( int k = 0; k < 15; ++k){
    printf("%3d", mass_B[k]);
    }
    printf("\n");

    for(int i = 0; i < 30; ++i){
        bool found = false;
        for( int k = 0; k < 15; ++k){
            if(mass_A[i] == mass_B[k]){
                found = true;
                break;
            }
        }
        if(!found){
            printf("%d", i);
            break;
        }
    }

    return 0;
}
