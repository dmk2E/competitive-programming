/*アルゴリズムと工夫点(Event Attendance/CPU: 16 ms Memory: 3940 KB  Length: 429 B)
imos法の基本問題．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int d,n;

int main(){
    int i,j;
    scanf("%d%d",&d,&n);
    vector<int> ans(d+1,0);
    while(n--){
        scanf("%d%d",&i,&j);
        ans[i-1]++;
        ans[j]--;
    }
    rep(i,d)ans[i+1]+=ans[i];
    rep(i,d)printf("%d\n",ans[i]);
    return 0;
}