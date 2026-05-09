/*アルゴリズムと工夫点(Let's Get a Perfect Score/CPU: 1 ms Memory: 3876 KB  Length: 518 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 30
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m,player[MAX_N];

int main(){
    int i,j,ans=0;
    string s;
    scanf("%d%d",&n,&m);
    rep(i,n){
        cin>>s;
        player[i]=0;
        rep(j,m)if((s[j]=='o'))player[i]|=1<<j;
    }
    rep(i,n)
        for(j=i+1;j<n;j++){
            ans+=(player[i]|player[j])==((1<<m)-1);
        }
    printf("%d\n",ans);
    return 0;
}