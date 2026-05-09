/*アルゴリズムと工夫点(Least Unbalanced/CPU: 57 ms Memory: 9552 KB  Length: 751 B)
逆順シミュレーションで解く．
二分木のように，kの値を半分近くの値に分割して，求める配列を生成すればよい．
最悪計算量は，O(N*2^(N)) < 10^8 となり高速．
※ 解法自体は思い浮かんでいたが，証明ができなかった...
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,k;

int main(){
    int i,ans_u = -1;
    scanf("%d%d",&n,&k);
    vector<int> ans(1,k);
    while(n--){
        vector<int> nxt;
        int min_a = k+1,max_a = -1;
        for(int a:ans){
            nxt.push_back(a/2);
            nxt.push_back((a+1)/2);
            min_a = min(min_a,nxt[nxt.size()-2]);
            max_a = max(max_a,nxt[nxt.size()-1]);
        }
        ans_u = max(ans_u,max_a-min_a);
        swap(nxt,ans);
    }
    printf("%d\n",ans_u);
    rep(i,ans.size()-1)printf("%d ",ans[i]);printf("%d\n",ans[i]);
    return 0;
}