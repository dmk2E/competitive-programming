/*アルゴリズムと工夫点(Buildings/CPU: 30 ms Memory: 5856 KB  Length: 540 B)
求めたいものは，「ビルiを固定した時，i<j<=N の範囲で最大値の更新が行われた回数」となる．
iの小さい順にそれを高速に求めていくことは困難だから，逆順に求めていくことを考える．
あるビルを固定した時，i(0<=i<N)，つまり値h[i]で最大値の更新が行われた時，それまで更新が起こった時の値h[i]をiの昇順に並べると，h[i]の値も昇順に並んでいる．
つまり解法は，「最大値の更新点の累積個数」を数え上げる，スタックを用いたアルゴリズムとなる．
最悪計算量は，O(N)<10^6 となり，十分高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<int> h(n),sta,ans;
    rep(i,n)scanf("%d",&h[i]);
    for(i=n-1;i>=0;i--){
        ans.push_back((int)sta.size());
        while((int)sta.size()>0&&(h[i]>sta.back()))sta.pop_back();
        sta.push_back(h[i]);
    }
    rep(i,n-1)printf("%d ",ans[n-1-i]);
    printf("%d\n",ans[n-1-i]);
    return 0;
}