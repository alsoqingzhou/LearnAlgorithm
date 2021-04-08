#include <cstdio>
#include <cstring>

bool judge(char list[]) {
    int length = strlen(list);
    for(int i = 0; i < length/2; i++) {
        if(list[i] != list[length-1-i]) {
            return false;
        }
    }
    return true;
}

int main() {
    char list[100];
    gets(list);
    if(judge(list)){
        printf("Yes!");
    } else {
        printf("No.");
    }

    return 0;
}