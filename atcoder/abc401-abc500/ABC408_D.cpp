/*アルゴリズムと工夫点(Flip to Gather/CPU: 28 ms Memory: 5580 KB  Length: 2859 B)
ランレングス圧縮+動的計画法で解く．
まず，Sを (値,その数)の形にランレングス圧縮しておく．この数列の値一つ一つをrleとする．

-考察ポイント-
各rleに対して操作を行うか決めた時，その操作を行う順番は関係ない．
そこで前のrleから順番に操作を行うか決めていけばよい．

-発想ポイント-
ここで，次のようなDPを考える．
dp[i][j]:i番目のrleを0にするか1にするか決めた時，状態がjである時の最小操作回数
状態0:S[0,i)="00~0"
状態1:S[0,i)="0~01~1"
状態2:S[0,i)="0~01~10~0"

最悪計算量は，O(N)<10^6 となり十分高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define STATE 3
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

int t,n;

int main(){
    int i,j;
    scanf("%d",&t);
    const int NIL=100000000;
    while(t--){
        scanf("%d",&n);
        string s;
        vector<P> rle;
        i=0;
        cin>>s;
        while(i<n){
            P now(s[i]-'0',1);
            i++;
            while(i<n&&s[i]-'0'==now.first){
                now.second++;
                i++;
            }
            rle.push_back(now);
        }
        rep(i,rle.size())if(rle[i].first==1)break;
        vector<int> dp(STATE,NIL);
        dp[0]=0;
        rep(i,rle.size()){
            vector<int> now(STATE,NIL);
            //printf("%d %d %d\n",dp[0],dp[1],dp[2]);
            rep(j,STATE){
                if(dp[j]==NIL)continue;
                switch(j){
                    case 0:
                        if(rle[i].first){
                            // 1の集合を残す場合
                            now[1]=min(now[1],dp[0]);
                            //printf("%d\n",now[1]);
                            // 0にする場合
                            now[0]=min(now[0],dp[0]+rle[i].second);
                        }else{
                            // 0の集合を残す場合
                            now[0]=min(now[0],dp[0]);
                            // 1にする場合
                            now[1]=min(now[1],dp[0]+rle[i].second);
                        }
                        break;
                    case 1:
                        if(rle[i].first){
                            // 1の集合を残す場合
                            now[1]=min(now[1],dp[1]);
                            // 0にする場合
                            now[2]=min(now[2],dp[1]+rle[i].second);
                        }else{
                            // 0の集合を残す場合
                            now[2]=min(now[2],dp[1]);
                            // 1にする場合
                            now[1]=min(now[1],dp[1]+rle[i].second);
                        }
                        break;
                    default:
                        if(rle[i].first){
                            // 0にするしかない
                            now[2]=min(now[2],dp[2]+rle[i].second);
                        }else{
                            now[2]=min(now[2],dp[2]);
                        }
                        break;
                }
            }
            //printf("%d %d %d\n",now[0],now[1],now[2]);
            swap(dp,now);
        }
        printf("%d\n",min(min(dp[0],dp[1]),dp[2]));
    }
    return 0;
}