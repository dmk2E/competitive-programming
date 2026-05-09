/*アルゴリズムと工夫点(Polyomino/CPU: 32 ms Memory: 3624 KB  Length: 2808 B)
再帰を用いた全探索で解く．
各ポリオミノの大きさは，4 * 4 マスで固定で渡されるため，それぞれ下記の操作を全て試す．
 ・90度回転を，0~3 回 行ったもの
 ・dy ∈ [-3, 3], dx ∈ [-3, 3] の範囲で平行移動したもの
その上で，4 * 4 の全マスを埋められるか判定すればよい．
最悪計算量は，O(4 ^ (N) * 4 * (H * W) ^ (2)) < 10 ^ 6 となり十分高速．
※ 枝刈りを行っているため，実際の計算量はより小さくなる
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
#define H 4
#define W 4
#define N 3
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

vector<vector<string> > polys(N, vector<string>(H));

void rotate90(vector<string>& poly){
    int i, j;
    vector<string> rotated_poly(H, string(/* count = */ W, /* ch = */ '.'));
    rep(i, H)rep(j, W){
        rotated_poly[j][W - 1 - i] = poly[i][j];
    }
    swap(rotated_poly, poly);
}

bool canMovePoly(int dy, int dx, vector<string>& poly){
    int i, j;
    rep(i, H)rep(j, W)if(poly[i][j] == '#'){
        int y = i + dy;
        int x = j + dx;
        if(y < 0 || y >= H || x < 0 || x >= W)return false;
    }
    return true;
}

vector<string> movePoly(int dy, int dx, vector<string>& poly){
    vector<string> moved_poly(H, string(/* count = */ W, /* ch = */ '.'));

    int i, j;
    rep(i, H)rep(j, W)if(poly[i][j] == '#')moved_poly[i + dy][j + dx] = '#';
    return moved_poly;
}

bool canPlace(const vector<string>& poly, vector<string>& mp){
    int i, j;
    rep(i, H)rep(j, W)if(poly[i][j] == '#' && mp[i][j] == '#')return false;
    return true;
}

int placePoly(const vector<string>& poly, vector<string>& mp){
    int i, j, cnt_sharp = 0;
    rep(i, H)rep(j, W)if(poly[i][j] == '#'){
        mp[i][j] = poly[i][j];
        cnt_sharp++;
    }
    return cnt_sharp;
}

bool rec(int now_poly_id, int sum_sharp, vector<string>& mp){
    if(sum_sharp == H * W)return true;
    if(now_poly_id == N)return false;

    int rot_i, i, j;
    auto& poly = polys[now_poly_id];

    rep(rot_i, 4){
        rotate90(/* poly = */ poly);
        for(i = - H + 1;i < H;i++)for(j = - W + 1;j < W;j++)if(canMovePoly(/* dy = */ i, /* dx = */ j, /* poly = */ poly)){
            vector<string> moved_poly = movePoly(
                /* dy = */ i, 
                /* dx = */ j, 
                /* poly = */ poly
            );
            if(canPlace(/* poly = */ moved_poly, /* mp = */ mp)){
                vector<string> nxt_mp = mp;
                if(rec(
                    /* now_poly_id = */ now_poly_id + 1, 
                    /* sum_sharp = */ sum_sharp + placePoly(/* poly = */ moved_poly, /* mp = */ nxt_mp), 
                    /* mp = */ nxt_mp
                ))return true;
            }
        }
    }
    return false;
}

int main(){
    int i, j, k;

    // 入力
    rep(i, N){
        auto& poly = polys[i];
        rep(j, H)cin >> poly[j];
    }

    vector<string> mp(H, string(/* count = */ W, /* ch = */ '.'));
    printf("%s\n", rec(
        /* now_poly_id = */ 0, 
        /* sum_sharp = */ 0, 
        /* mp = */ mp
        ) ? "Yes" : "No");
    return 0;
}