/*アルゴリズムと工夫点(Monotonically Increasing/CPU: 1 ms Memory: 3796 KB  Length: 660 B)

*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;

int main(){
    int i,j;
    scanf("%d%d",&n,&m);
    vector<int> ans;
    auto rec=[&](auto& f,int last,int now)->void{
        int i;
        if(now==n){
            rep(i,n-1)printf("%d ",ans[i]);
            printf("%d\n",ans[i]);
            return ;
        }
        for(i=last+1;i<=m;i++){
            if(i+n-now-1>m)return ;
            ans.push_back(i);
            f(f,i,now+1);
            ans.pop_back();
        }
    };
    rec(rec,0,0);
    return 0;
}