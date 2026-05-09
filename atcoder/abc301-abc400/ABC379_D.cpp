/*アルゴリズムと工夫点(Home Garden/CPU: 29 ms Memory: 4164 KB  Length: 669 B)
植木鉢に入れるのが早ければ早いほど，高さは高くなるため，単調性がある．そのため，一度収穫した植物より前の植物に関しては無視できる．
このことから，「キュー」のイメージができる．
問題は高さをTだけ加算するところ．これを愚直にすることはできないため，キューには植物を植えた日を入れて置き，取り出す際は現在の日との差分から高さを求める．
最悪計算量は，O(Q)<10^6 となり十分高速．
※キューにどんな要素を入れ，別でどんな値を保持して置けば高速に値を求められるかを考える．
*/
#include<iostream>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int q;

int main(){
    int i,j;
    ll now;
    scanf("%d",&q);
    queue<ll> que;
    now=0;
    while(q--){
        scanf("%d",&i);
        if(i==1){
            que.push(now);
        }else if(i==2){
            scanf("%d",&i);
            now+=i;
        }else{
            scanf("%d",&i);
            j=0;
            while(que.size()&&now-que.front()>=i){
                que.pop();
                j++;
            }
            printf("%d\n",j);
        }
    }
    return 0;
}