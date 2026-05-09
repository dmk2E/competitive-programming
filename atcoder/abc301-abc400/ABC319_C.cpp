/*アルゴリズムと工夫点(False Hope/CPU: 14 ms Memory: 3924 KB  Length: 1790 B)
再帰を用いた枝刈り全探索で解く．
各行各列，また斜め方向の2つについてそれぞれ，現時点で高橋君が知った順番を保持しながら，シミュレーションを行う．
全パターン数は，9! < 10^(3) しかないため，全探索が可能．
実装では再帰を用い，また枝刈りを行うことで高速化した．
最悪計算量は，O((H * W)! * 10 * H * W) < 10^8 となり間に合う．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define H 3
#define W 3
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

int c[H][W];

/// @brief 1行 or 1列 or 1つの斜め について，高橋君はがっかりしないか判定
/// @param arr 高橋君が知った順に値が格納された，長さ3以下の配列
/// @return 高橋君ががっかりしないか
bool checkArray(vector<int>& arr){
    return arr.size() != 3 || (arr[0] != arr[1] || arr[1] == arr[2]);
}

int main(){
    int i,j,sum = 1;
    rep(i, H * W)sum *= (i + 1);
    rep(i,H)rep(j,W)scanf("%d",&c[i][j]);
    vector<vector<int > > row(H),col(W),diag(2);

    auto rec = [&](auto& func, int state)->int{
        if(state == 0)return 1;
        int i,cnt = 0;
        rep(i, H * W)if((state >> i) & 1){
            bool flag = true;
            int y = i / W;
            int x = i % W;
            row[y].push_back(c[y][x]);
            if(!checkArray(row[y]))flag = false;
            col[x].push_back(c[y][x]);
            if(!checkArray(col[x]))flag = false;
            if(y == x){
                diag[0].push_back(c[y][x]);
                if(!checkArray(diag[0]))flag = false;
            }
            if(y == -x + 2){
                diag[1].push_back(c[y][x]);
                if(!checkArray(diag[1]))flag = false;
            }

            if(!flag){
                row[y].pop_back();col[x].pop_back();
                if(y == x)diag[0].pop_back();
                if(y == -x + 2)diag[1].pop_back();
                continue;
            }
            cnt += func(func, state ^ (1 << i));
            
            row[y].pop_back();
            col[x].pop_back();
            if(y == x)diag[0].pop_back();
            if(y == -x + 2)diag[1].pop_back();
        }
        return cnt;
    };
    printf("%.9f\n", (double)rec(rec, (1 << (H * W)) - 1) / sum);
    return 0;
}