/*アルゴリズムと工夫点(Wind Cleaning/CPU: 1106 ms Memory: 52104 KB  Length: 1744 B)
BFS で解く．
二次元グリッドのあり得る状態数は，平行移動のさせ方の場合の数である，H * W 通り．
各状態への遷移は上下左右の4パターン，状態変更にマス数 H * W 分の計算量がかかる．
状態は連想配列で保持するため，探索時間は状態の長さ文加味して，H * W * log2(H * W) 分の計算量がかかる．
従って最悪計算量は，O(4 * (H * W) ^ (3) * log2(H * W)) < 10^8 となり間に合う．
※ 連想配列上での探索時間削減のため，二次元グリッドを一次元の文字列で表現している
※ 高橋君の位置は別変数で保持しておき，探索時はそのマスは`.`で塗っておく
※ 公式解説では，ゴミ群ではなく高橋君自体を動かす & 元の盤面の状態を再利用 する考え方
※ ↑そのため矩形の2点と高橋君の座標の1点の座標を保持し，状態を表現することで，O((H * W) ^ 3) となる
*/
#include<iostream>
#include<vector>
#include<map>
#include<queue>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int h,w;

string move(const string& now,const int& dy, const int& dx){
    int i;
    string ans = "";
    i = h * w;
    while(i--)ans += '.';
    rep(i,h * w){
        int y = i / w, x = i % w;
        int nxt_y = y + dy, nxt_x = x + dx;
        if(
            0 <= nxt_y && nxt_y < h && 
            0 <= nxt_x && nxt_x < w
        ){
            int nxt = nxt_y * w + nxt_x;
            ans[nxt] = now[i];
        }
    }
    return ans;
}

int main(){
    int i,j,t;
    scanf("%d%d",&h,&w);
    string mp = "";
    {
        rep(i,h){
            string tmp;
            cin>>tmp;
            mp += tmp;
        }
        rep(i, h * w)if(mp[i] == 'T')break;
        t = i;
        mp[t] = '.';
    }
    auto bfs = [&](string now)->int{
        int i;
        const int dy[] = {-1,0,1,0},MAX_D = 4;
        const int dx[] = {0,1,0,-1},NIL = -1;
        map<string,int> dict;
        queue<string> que;
        dict[now] = 0;
        que.push(now);
        while(que.size()){
            now = que.front();que.pop();
            rep(i,MAX_D){
                string nxt = move(now,dy[i],dx[i]);
                if(nxt[t] == '.' && dict.find(nxt) == dict.end()){
                    dict[nxt] = dict[now] + 1;
                    que.push(nxt);
                }
            }
        }
        string goal = "";
        i = h * w;while(i--)goal += '.';
        return dict.find(goal) == dict.end() ? NIL :dict[goal];
    };
    printf("%d\n", bfs(mp));
    return 0;
}