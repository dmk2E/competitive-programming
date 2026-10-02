#include<iostream>
#include<random>
#include<time.h>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

mt19937 mt_for_color(time(NULL));
const int MAX_N = 3000;
const int MAX_Q = 3000;

int main(){
    int n = (mt_for_color() % MAX_N) + 1;
    int q = (mt_for_color() % MAX_Q) + 1;
    printf("%d %d\n", n, q);

    const int ALFA = 26;
    while(q--){
        int id = (mt_for_color() % 2) + 1;

        printf("%d ", id);
        if(id == 2)printf("%c\n", (char)('a' + (int)(mt_for_color() % ALFA)));
        else printf("%d\n", (int)(mt_for_color() % n) + 1);
    }
    return 0;
}