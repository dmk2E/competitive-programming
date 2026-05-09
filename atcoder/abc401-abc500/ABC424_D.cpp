/*アルゴリズムと工夫点(2x2 Erasing 2/CPU: 61 ms Memory: 3952 KB  Length: 1890 B)
bitDPで解く．
i行目の白黒の塗られている状態を state_(i) とし，2進数で表現するとする．
dp[i][j] ::= state_(i) = j となっており，i-1行目より上（それ自体含む）の行では，条件を満たしている状態にするための，マスを白く塗りつぶす回数
最悪計算量は，O(T*H*W*2^(2*W)) < 10^8 となり間に合う．
※ バーチャル参加
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int t;

int popCountDiff(int x,int y){
    int ans = 0;
    while(x > 0 || y > 0){
        ans += (x & 1) ^ (y & 1);
        x >>= 1;
        y >>= 1;
    }
    return ans;
}

int solve(){
    int i,j,h,w,ans;
    scanf("%d%d",&h,&w);
    const int INF = h * w;
    ans = INF;
    vector<int> mp(h);
    rep(i,h){
        string s;
        cin>>s;
        j = 0;
        reverse(s.begin(),s.end());
        for(char c : s){
            j *= 2;
            j += c == '#';
        }
        mp[i] = j;
    }
    auto judge = [&](int row1,int row2)->bool{
        // state mp[row + 1]
        int j;
        rep(j,w-1){
            if(
                ((row1 >> j) & 1) && ((row1 >> (j+1)) & 1) &&
                ((row2 >> j) & 1) && ((row2 >> (j+1)) & 1)
            )return false;
        }
        return true;
    };
    vector<int> dp(1<<w,INF);
    dp[mp[0]] = 0;
    auto show = [&](const vector<int>& arr)->void{
        int i;
        rep(i,arr.size())if(arr[i] != INF)printf("(%d : %d)",i,arr[i]);puts("");
    };
    rep(i,h-1){
        //show(dp);
        vector<int> nxt(1<<w,INF);
        rep(j,1<<w)if(dp[j] != INF){
            // i行目の状態がjである時，i+1行目の状態を全探索
            int s = mp[i+1];
            do{
                if(judge(j,s))nxt[s] = min(nxt[s],dp[j] + popCountDiff(mp[i+1],s));
                s--;
                s &= mp[i+1];
            }while(s != mp[i+1]);
        }
        swap(dp,nxt);
    }
    rep(i,1<<w)ans = min(ans,dp[i]);
    return ans;
}

int main(){
    scanf("%d",&t);
    while(t--){
        printf("%d\n",solve());
    }
    return 0;
}