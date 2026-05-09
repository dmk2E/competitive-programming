/*アルゴリズムと工夫点(The Simple Game/CPU: 77 ms Memory: 45076 KB  Length: 1237 B)
メモ化再帰を用いたゲーム木探索で解く．
K <= 10 であるため，ゲームの遷移状態を全探索し，最適な行動時の勝者を求める．
最悪計算量は，O(M * K + 2* K * 2 *N) = O(K * (M + N)) < 10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

enum State{
    NIL = -1,
    LOSE = 0,
    WIN = 1
};

int t;

bool solve(){
    int i,j,n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    string s;
    vector<vector<int> > adj(n);
    vector<bool> color(n,false);
    cin>>s;
    rep(i,n)color[i] = s[i] == 'A';
    while(m--){
        int u,v;
        scanf("%d%d",&u,&v);u--;v--;
        adj[u].push_back(v);
    }
    vector<vector<vector<State> > > memo(2 * k,vector<vector<State> > (2, vector<State>(n,NIL)));
    auto rec = [&](auto& func, int k, bool p_color, int now)->bool{
        // WIN:true
        // LOSE:false
        if(k == 0)return p_color == color[now];
        for(int nxt : adj[now]){
            if(memo[k - 1][!p_color][nxt] == NIL)memo[k - 1][!p_color][nxt] = func(func, k-1, !p_color, nxt) ? WIN : LOSE;
            if(memo[k - 1][!p_color][nxt] == LOSE)return true;
        }
        return false;
    };
    return rec(rec, 2 * k, true, 0);
}

int main(){
    scanf("%d\n",&t);
    while(t--)printf("%s\n",solve() ? "Alice" : "Bob");
    return 0;
}