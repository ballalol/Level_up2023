#include <stdio.h>
#include <math.h>

// Дана строка символов. Определить длину самой длинной подстроки, состоящей из подряд идущих букв а
// asd  => 1
// dfaaaf => 3
// dfhaagffaaa => 3


int main()
{
    constexpr int q = 255;
    char mass[q] = {};
    scanf("%s", mass);
    int max = 0;
    int count = 0;
    for (int i = 0; mass[i]; ++i) {
        if(mass[i] == 'a') {
            count++;
            max = fmax(count, max);
        }
        else {
            count = 0;

        }
    }
    printf("%d", max);
    return 0;
}
