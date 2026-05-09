/*アルゴリズムと工夫点(Just K/CPU: 7 ms Memory: 3888 KB  Length: 610 B)

*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_ALFA 26
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,k;

int main(){
    int i,j,ii,mx;
    scanf("%d%d",&n,&k);
    vector<string> ipt(n);
    rep(i,n)cin>>ipt[i];
    mx=-1;
    rep(i,1<<n){
        vector<int> cnt_alfa(MAX_ALFA,0);
        rep(j,n)if((i>>j)&1)rep(ii,ipt[j].length())cnt_alfa[ipt[j][ii]-'a']++;
        ii=0;
        rep(j,MAX_ALFA)ii+=(cnt_alfa[j]==k);
        mx=max(ii,mx);
    }
    printf("%d\n",mx);
    return 0;
}