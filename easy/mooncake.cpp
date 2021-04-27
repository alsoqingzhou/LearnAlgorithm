#include <cstdio>
#include <algorithm>
using namespace std;

struct mooncake{
    double store;
    double sell;
    double price;
}cake[1010];

bool cmp(mooncake a, mooncake b) {
    return a.price > b.price; //按月饼单价升序排列
}

int main() {
    int n; //月饼种类
    double D; //总需求量
    scanf("%d%lf", &n, &D);
    for(int i = 0; i < n; i++) {
        scanf("%lf", &cake[i].store);
    }

    for(int i = 0; i < n; i++) {
        scanf("%lf", &cake[i].sell);
        cake[i].price = cake[i].sell / cake[i].store;
    }
    sort(&cake[0], &cake[n-1], cmp);

    double ans = 0; //收益
    for(int i = 0; i < n; i++) {
        if(cake[i].store <= D){
            ans += cake[i].sell;
            D -= cake[i].store;
        } else {
            ans += cake[i].price * D;
            break;
        }
    }

    printf("%.2f", ans);
    return 0;
}