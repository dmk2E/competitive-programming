/*アルゴリズムと工夫点(Pasta/CPU: 1 ms Memory: 3884 KB  Length: 530 B)

*/
#include<iostream>
#include<map>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;

int main(){
    int i,j;
    scanf("%d%d",&n,&m);
    map<int,int> a2Cnt;
    rep(i,n){
        scanf("%d",&j);
        a2Cnt[j]++;
    }
    rep(i,m){
        scanf("%d",&j);
        if(a2Cnt.find(j)==a2Cnt.end()||a2Cnt[j]==0){
            puts("No");
            return 0;
        }
        a2Cnt[j]--;
    }
    puts("Yes");
    return 0;
}