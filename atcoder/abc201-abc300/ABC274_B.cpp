/*アルゴリズムと工夫点(Line Sensor/CPU: 14 ms Memory: 5848 KB  Length: 473 B)

*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int h,w;

int main(){
    int i,j;
    scanf("%d%d",&h,&w);
    vector<string> c(h);
    rep(i,h)cin>>c[i];
    vector<int> ans(w);
    rep(j,w){
        ans[j]=0;
        rep(i,h)
            ans[j]+=c[i][j]=='#';
    }
    rep(i,w-1)printf("%d ",ans[i]);
    printf("%d\n",ans[i]);
    return 0;
}