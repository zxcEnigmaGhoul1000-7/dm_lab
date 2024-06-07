#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 100000

int main() {
    int n;
    printf("количество в последовательности: ");
    scanf("%d", &n);

    int *posledovatelnost = (int *)malloc(n * sizeof(int));
    int povtor[MAX_NUM] = {0};

    printf("последовательность: ");
    for (int i = 0; i < n; ++i) {
        scanf("%d", &posledovatelnost[i]);
        povtor[posledovatelnost[i]]++;
    }

    int oddCount = 0;
    for (int i = 0; i < MAX_NUM; ++i) {
        if (povtor[i] % 2 != 0) {
            oddCount++;
        }
    }

    printf("различные числа, нечетн раз: %d\n", oddCount);

    free(posledovatelnost);
    return 0;
}