#include <stdio.h>

int main() {
    int n, col, row;
    char word;
    scanf("%d %c", &n, &word);
    col = n;
    if(n % 2 == 0) {
        row = n / 2;
    } else {
        row = (n + 1) / 2;
    }

    for(int i = 0; i < col; i++) {
        printf("%c", word);
    } // first row
    printf("\n");

    for(int i = 0; i < row - 2; i++) {
        printf("%c", word);
        for(int j = 0; j < col - 2; j++) {
            printf(" ");
        }
        printf("%c", word);
        printf("\n");
    } // second to row-1

    for(int i = 0; i < col; i++) {
        printf("%c", word);
    } // last row

    return 0;
}