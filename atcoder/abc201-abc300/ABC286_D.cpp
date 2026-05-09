/*アルゴリズムと工夫点(Money in Hand/CPU: 54 ms Memory: 3892 KB  Length: 713 B)
dp[i][j]:1~i+1枚目の硬貨のいずれかを使ったとき，j円払うことができるかを真偽値で持つ．
の動的計画法で解ける．ただし，A円の硬貨がB枚存在するとき，A円が独立してB枚存在すると考える．
最悪計算量はO(NBX)=2.5*10^7≒10^7 となり，高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

int n,x,a,b;

int main(){
    int i,j;
    scanf("%d%d",&n,&x);
    vector<bool> last(x+1,false);
    last[0]=true;
    rep(i,n){
        scanf("%d%d",&a,&b);
        while(b--){
            vector<bool> now(x+1,false);
            rep(j,x+1){
                if(last[j]){
                    now[j]=true;
                    if(j+a<=x)
                        now[j+a]=true;
                }
            }
            swap(last,now);
        }
        //rep(j,x+1)printf("%d ",last[j]?1:0);puts("");
    }
    printf("%s\n",last[x]?"Yes":"No");
    return 0;
}