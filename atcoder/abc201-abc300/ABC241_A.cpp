/*アルゴリズムと工夫点(Digit Machine/CPU: 1 ms Memory: 3884 KB  Length: 365 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define N 10
#define CNT 3
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int cnt[N];

int main(){
    int i,j;
    rep(i,N)scanf("%d",&cnt[i]);
    i=0;
    j=0;
    while(j<CNT){
        i=cnt[i];
        j++;
    }
    printf("%d\n",i);
    return 0;
}