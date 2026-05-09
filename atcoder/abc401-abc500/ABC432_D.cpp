/*アルゴリズムと工夫点(Suddenly, A Tempest/CPU: 1 ms Memory: 4040 KB  Length: 3282 B)
長方形で黒マス管理シミュレーション + 連結成分計算
一つ一つの座標を持つことはできないが，黒マスの長方形で持つことが可能．
また，一つ一つの操作で各長方形が被ることはないため，N回単純にシミュレーションを行う．
連結成分の計算は，BFSで実装した．
生成される長方形の数は最大でも，2^N となるため，最悪計算量は，O(2^(2*N)) < 10^7 となり高速．
※ 半開区間で管理すると，共通範囲が0で「接している」，負の数で全く接していないという判定が行えて便利
*/
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Rectangle{
    ll sy,sx,gy,gx;

    Rectangle(ll sy = 0, ll sx = 0, ll gy = 0, ll gx = 0):sy(sy),sx(sx),gy(gy),gx(gx){};
};

int n,x,y;

int main(){
    int i,j;
    scanf("%d%d%d",&n,&x,&y);
    queue<Rectangle> que;
    vector<Rectangle> boxes;
    que.push(Rectangle(0,0,y - 1,x - 1));
    while(n--){
        char c;
        int a,b;
        getchar();
        scanf("%c %d%d",&c,&a,&b);
        queue<Rectangle> nxt_que;
        while(que.size()){
            Rectangle now = que.front();que.pop();
            if(c == 'X'){
                if(now.sx < a && a <= now.gx){
                    nxt_que.push(Rectangle(now.sy - b, now.sx, now.gy - b, a - 1));
                    nxt_que.push(Rectangle(now.sy + b, a, now.gy + b, now.gx));
                }else if(now.gx < a){
                    nxt_que.push(Rectangle(now.sy - b, now.sx, now.gy - b, now.gx));
                }else{
                    nxt_que.push(Rectangle(now.sy + b, now.sx, now.gy + b, now.gx));
                }
            }else{
                if(now.sy < a && a <= now.gy){
                    nxt_que.push(Rectangle(now.sy, now.sx - b, a - 1, now.gx - b));
                    nxt_que.push(Rectangle(a, now.sx + b, now.gy, now.gx + b));
                }else if(now.gy < a){
                    nxt_que.push(Rectangle(now.sy, now.sx - b, now.gy, now.gx - b));
                }else{
                    nxt_que.push(Rectangle(now.sy, now.sx + b, now.gy, now.gx + b));
                }
            }
        }
        swap(que,nxt_que);
    }
    // while(que.size()){Rectangle now = que.front();que.pop();printf("s:(%d, %d) e:(%d, %d)\n",now.sy,now.sx,now.gy,now.gx);}
    while(que.size()){
        Rectangle now = que.front();que.pop();
        boxes.push_back(now);
    }
    vector<ll> ans;
    const int NIL = -1;
    vector<int> color(boxes.size(), NIL);
    auto bfs = [&](int now)->void{
        auto judge = [&](ll a_id, ll b_id) -> bool{
            Rectangle& a = boxes[a_id];
            Rectangle& b = boxes[b_id];
            ll tmp_y = min(a.gy, b.gy) - max(a.sy, b.sy);
            ll tmp_x = min(a.gx, b.gx) - max(a.sx, b.sx);
            return (tmp_y == NIL && tmp_x >= 0) || (tmp_y >= 0 && tmp_x == NIL); 
        };
        int i,c = ans.size();
        ll sum = ((ll)boxes[now].gy - boxes[now].sy + 1) * (boxes[now].gx - boxes[now].sx + 1);
        queue<int> que;
        color[now] = c;
        que.push(now);
        while(que.size()){
            now = que.front();que.pop();
            rep(i,boxes.size())if(color[i] == NIL && judge(now, i)){
                color[i] = c;
                que.push(i);
                sum += ((ll)boxes[i].gy - boxes[i].sy + 1) * (boxes[i].gx - boxes[i].sx + 1);  
            }
        }
        ans.push_back(sum);
    };
    rep(i,boxes.size())if(color[i] == NIL)bfs(i);
    sort(ans.begin(),ans.end());
    printf("%ld\n",ans.size());
    rep(i,ans.size() - 1)printf("%lld ",ans[i]);
    printf("%lld\n",ans[i]);
    return 0;
}