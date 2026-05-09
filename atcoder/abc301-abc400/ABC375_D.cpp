/*アルゴリズムと工夫点(Spiral Rotation/CPU: 11 ms Memory: 3988 KB  Length: 1022 B)
dp[i][len][alfa]:1~i+1文字目まで見た時の，先頭大文字がalfaで長さがlenとなる回文の個数
とする動的計画法で解ける．
最悪計算量はO(|S|*26*4)<10^7 となり十分高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string s;

int main(){
    int i,j,k;
    ll ans=0;
    cin>>s;
    const int ALFA=26,LEN=4;
    vector<vector<ll> > last(LEN,vector<ll>(ALFA,0)),now;
    //rep(j,ALFA)last[0][j]=1;
    //rep(k,ALFA)printf("%c ",'A'+k);puts("");
    rep(i,s.length()){
        now=last;
        for(j=1;j<LEN;j++){
            if(j==1){
                now[j][s[i]-'A']=last[j][s[i]-'A']+1;
            }else if(j==2){
                //now[j][k]=last[j][k];
                rep(k,ALFA)now[j][k]+=last[j-1][k];
            }else{
                if(last[j-1][s[i]-'A']>0)
                    now[j][s[i]-'A']=last[j-1][s[i]-'A']+now[j][s[i]-'A'];
            }
        }
        //rep(j,LEN){rep(k,ALFA)printf("%lld ",now[j][k]);puts("");}puts("");
        swap(last,now);
    }
    rep(j,ALFA)ans+=last[3][j];
    printf("%lld\n",ans);
    return 0;
}