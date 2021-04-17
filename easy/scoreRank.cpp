#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct Student {
    char id[15];
    int score;
    int location_number;
    int local_rank;
} stu[30010];

bool cmp(Student a, Student b) {
    if(a.score != b.score) return a.score > b.score;
    else return strcmp(a.id, b.id) < 0;
}

int main() {
    
}