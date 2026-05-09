/*アルゴリズムと工夫点(Range Add Query/CPU: 102 ms Memory: 21156 KB  Length: 679 B)

*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

int n,k,q;

int main(){
    int i,j,ii;
    cin>>n>>k;
    vector<int> a(n);
    vector<vector<ll> > sum(k,vector<ll>(n+1,0));
    rep(i,n)
        scanf("%d",&a[i]);
    rep(i,n)
        sum[i%k][i+1]=a[i];
    rep(i,k)rep(j,n)sum[i][j+1]+=sum[i][j];
    scanf("%d",&q);
    while(q--){
        scanf("%d%d",&i,&j);
        i--;
        vector<ll> ns(k);
        rep(ii,k)ns[ii]=sum[ii][j]-sum[ii][i];
        sort(ns.begin(),ns.end());
        printf("%s\n",ns[0]==ns[k-1]?"Yes":"No");
    }
    return 0;
}