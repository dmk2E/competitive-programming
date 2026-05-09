/*アルゴリズムと工夫点(Addition and Multiplication 2/CPU: 51 ms Memory: 7548 KB  Length: 816 B)
最小金額の整数を選べるだけ選び，その後最上位桁から，支払える金額内で最大の整数で置き換えていくことを考えればよい．
貪欲で解くことができ，最悪計算量は O(|S|)<10^7 となり高速．
※初見5完達成!
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

int n;
const int MAX_C=9;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<int> c(MAX_C+1),ans;
    P tmp=P(n+1,0);
    rep(i,MAX_C){
        scanf("%d",&c[i+1]);
        if(tmp.first>c[i+1])tmp=P(c[i+1],i+1);
    }
    while(n>=tmp.first){
        ans.push_back(tmp.second);
        n-=tmp.first;
    }
    rep(i,ans.size()){
        for(j=MAX_C;j>ans[i];j--){
            if(n+tmp.first>=c[j]){
                n+=tmp.first;
                n-=c[j];
                ans[i]=j;
            }
        }
    }
    rep(i,ans.size())printf("%d",ans[i]);puts("");
    return 0;
}