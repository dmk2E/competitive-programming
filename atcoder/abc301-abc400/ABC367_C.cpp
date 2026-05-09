/*アルゴリズムと工夫点(Enumerate Sequences/CPU: 73 ms Memory: 3920 KB  Length: 703 B)
再帰関数を実装するときは，指定された順に列挙できるかをまず考えてみる．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,k;
vector<int> r;

void dfs(int now,vector<int>& aa,int sum){
    int i;
    if(now==n){
        if(sum%k==0){
            rep(i,n-1)printf("%d ",aa[i]);printf("%d\n",aa[i]);
        }
        return ;
    }
    for(i=1;i<=r[now];i++){
        aa.push_back(i);
        dfs(now+1,aa,sum+i);
        aa.pop_back();
    }
}

int main(){
    int i,j;
    scanf("%d%d",&n,&k);
    r=vector<int>(n);
    rep(i,n)
        scanf("%d",&r[i]);
    vector<int> aa(0);
    dfs(0,aa,0);
    return 0;
}