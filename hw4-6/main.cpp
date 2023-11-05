#include <stdio.h>
#include <math.h>

//   - Дана строка символов. Определить, является ли она правильным скобочным выражением.

int main()
{
    constexpr int q = 255;
    char Mass_A[q] = {};
    int countL = 0;
    int countR = 0;
    scanf("%s", Mass_A);
    for(int i = 0; Mass_A[i]; ++i){
        if(Mass_A[i] == '('){
            countL++;
        }
        for(int k = 0; Mass_A[k]; ++k){
            if(Mass_A[k] == ')'){
                countR++;
            }
        }
        if(countL == countR){
            printf("correct parenthetical expression");
            break;
        }
        if(countL != countR){
            printf("incorrect parenthetical expression");
            break;
        }
    }
    return 0;
}
