#include <cstdio>
#include <cstring>

int main() {
    char str[90];
    gets(str);

    int len = strlen(str), row = 0, col = 0;
    char ans[90][90];

    for(int i = 0; i < len; i++) {
        if(str[i] != ' ') {
            ans[row][col++] = str[i];
        } else {
            ans[row][col] = '\0';
            row++;
            col = 0;
        }
    }

    for(int i = row; i >=0; i--) {
        printf("%s", ans[i]);
        if(i > 0) printf(" ");
    }

    return 0;
}