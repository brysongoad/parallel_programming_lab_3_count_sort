#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Count_sort(int a[], int n);

int main(int argc, char* argv[]) {
    int n = argc-1;

    int* a = malloc(n*sizeof(int));

    for (int i = 0; i < n; i++){
        a[i] = atoi(argv[i+1]);
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    Count_sort(a, n);
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    return 0;
}

void Count_sort(int a[], int n) {
    int i, j, count;
    int* temp = malloc(n*sizeof(int));

    for (i = 0; i < n; i++) {
        count = 0;
        for (j = 0; j < n; j++){
            if (a[j] < a[i])
                count++;
            else if (a[j] == a[i] && j < i)
                count++;
        }
        temp[count] = a[i];
    }

    memcpy(a, temp, n*sizeof(int));
    free(temp);
}