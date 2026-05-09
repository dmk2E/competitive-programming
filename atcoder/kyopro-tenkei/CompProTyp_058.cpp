/*アルゴリズムと工夫点(Original Calculator（★4）/CPU: 1 ms Memory: 4316 KB  Length: 707 B)
キーワードは「周期性を考える」
単純な計算では求められない10^9番目のような値は，周期性を利用することで，求めることができる．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N (int)(1e5)
#define NIL -1
using namespace std;
typedef long long ll;

int n,visited[MAX_N]={0},num2Value[MAX_N];
ll k;

int main(){
    int i,j,ii;
    rep(i,MAX_N)visited[i]=NIL;
    scanf("%d%lld",&n,&k);
    i=0;
    while(visited[n]==NIL){
        visited[n]=i;
        num2Value[i]=n;
        if(i==k){
            printf("%d\n",n);
            return 0;
        }
        i++;
        ii=n;
        while(n>0){
            ii+=n%10;
            n/=10;
        }
        n=ii%MAX_N;
        //printf("%d\n",n);
    }
    printf("%d\n",num2Value[(k-i)%(i-visited[n])+visited[n]]);
    return 0;
}