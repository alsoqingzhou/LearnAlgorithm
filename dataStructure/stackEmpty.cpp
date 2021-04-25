#include <stdio.h>
#include <stack>
using namespace std;

int main() {
    stack<int> st;
    if(st.empty() == true) {
        printf("stack is empty.\n");
    } else {
        printf("stack is not empty.\n");
    }
    st.push(1);

    if(st.empty() == true) {
        printf("stack is empty.\n");
    } else {
        printf("stack is not empty.\n");
    }
}