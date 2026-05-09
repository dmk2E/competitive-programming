/*アルゴリズムと工夫点(Number Box/CPU: 1 ms Memory: 3940 KB  Length: 831 B)

*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
const int dy[]={-1,-1,0,1,1,1,0,-1};
const int dx[]={0,1,1,1,0,-1,-1,-1},MAX_D=8;

int main(){
    int i,j,k;
    ll ans=0;
    scanf("%d",&n);
    vector<vector<int> > a(n,vector<int>(n));
    rep(i,n){
        getchar();
        rep(j,n)a[i][j]=getchar()-'0';
    }
    auto cal=[&](int y,int x,int d)->ll{
        int i;
        ll sum=0;
        rep(i,n){
            sum*=10;
            sum+=a[y][x];
            y=(y+dy[d]+n)%n;
            x=(x+dx[d]+n)%n;
        }
        return sum;
    };
    rep(i,n)rep(j,n)rep(k,MAX_D){
        ans=max(ans,cal(i,j,k));
    }
    printf("%lld\n",ans);
    return 0;
}