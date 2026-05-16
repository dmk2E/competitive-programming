/*アルゴリズムと工夫点(点Pをたくさん動かすゲーム/CPU: - ms Memory: - KB  Length: - B)
bitDP で解く．
下記のDPテーブルを満たす動的計画法を考え，値の最大値を解とすればよい．
 dp[state][now_pt] := 状態state (どの点を訪問済みであるかを保持) で，頂点now_pt にいる時の移動距離の最大値
 ※ stateはビットで表現する．
各2点間の移動について，下記の条件を満たすか適切に判定すること．
 ・距離は整数であるか（浮動小数点数の値がが整数値に丸めても値が同じかで判定）
 ・他の点が移動線分上に存在しないか（内積と外積を用いて判定）
点の数をN とすると，最悪計算量は，O(N * N * N * 2 ^ N) < 10 ^ 7 となり，高速．
※ 枝刈りの都合上，再帰を用いた順列全探索で実装した方が早いかも
*/
#include<iostream>
#include<vector>
#include<cmath>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
#define INPUT_NUMBER 3
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

template<typename T>
class Outputer{
    vector<T> ans;

public:
    Outputer(){}

    void push(T value){
        ans.push_back(value);
    }

    void output(string prefix = "", string suffix = ""){
        int i;
        if(ans.size() > 0){
            rep(i, ans.size() - 1)cout << prefix << ans[i] << suffix << ',';
            cout << prefix << ans[i] << suffix << '\n';
        }
    }
};

struct Point{
    int y, x;

public: 
    Point(int y = 0, int x = 0):y(y), x(x){}

    Point operator-(const Point& k)const{
        return Point(this -> y - k.y, this -> x - k.x);
    }

    bool operator==(const Point& k)const{
        return this -> y == k.y && this -> x == k.x;
    }

    int norm(){
        return this -> y * this -> y + this -> x * this -> x;
    }

    int abs(){
        return sqrt(this -> norm());
    }
};

// vector<vector<int> > ipt = {
//     {0,0,1,0,2,0,3,0,4,0,0,1,0,2,1,2,2,2,4,2},
//     {1,0,0,0,2,0,4,0,4,1,4,3,2,3,1,3,0,3,0,1},
//     {4,1,1,0,6,4,0,0,12,0,1,5,12,5,13,5,10,1,0,5}
// };
vector<vector<int> > ipt = {
    {4,3,0,6,8,6,1,5,0,0,4,1,8,0,8,2,5,2,5,6},
    {0,0,30,0,60,0,90,0,96,0,0,40,30,40,60,40,90,40,96,40},
    {100,20,65,18,1,0,86,90,0,90,92,60,86,23,80,51,50,100,2,10}
};
Outputer<int> answer;

int dot(Point vec0, Point vec1){
    return vec0.y * vec1.y + vec0.x * vec1.x;
}

int cross(Point vec0, Point vec1){
    return vec0.x * vec1.y - vec1.x * vec0.y;
}

bool isOnLine(Point p0, Point p1, Point target){
    Point vec0 = p1 - p0;
    Point vec1 = target - p0;
    if(cross(/* vec0 = */ vec0, /* vec1 = */ vec1) != 0)return false;
    if(dot(/* vec0 = */ vec0, /* vec1 = */ vec1) <= 0)return false;
    return vec1.norm() < vec0.norm();
}

int main(){
    int i, j, k;

    for(int ipt_id = 0;ipt_id < INPUT_NUMBER;ipt_id++){
        auto& ipt_line = ipt[ipt_id];
        vector<Point> pts;
        rep(i, ipt_line.size() / 2)pts.push_back(Point(ipt_line[2 * i + 1], ipt_line[2 * i]));

        // bitDP
        auto isValidMove = [&](Point start, Point goal) -> bool{
            Point movement = goal - start;
            double dist_move = sqrt(movement.norm());
            if((int)dist_move != dist_move)return false;
            
            for(Point pt : pts)if(isOnLine(/* p0 = */ start, /* p1 = */ goal, /* target = */ pt))return false;
            return true;
        };
        const int NIL = -1;
        vector<vector<int> > dp(1 << pts.size(), vector<int>(pts.size(), NIL));
        dp[1][0] = 0;
        int ans = 0;
        rep(i, 1 << pts.size()){
            rep(j, pts.size())if(dp[i][j] != NIL){
                rep(k, pts.size())if(!((i >> k) & 1) && isValidMove(/* start = */ pts[j], /* goal = */ pts[k])){
                    int nxt_state = i | (1 << k);
                    dp[nxt_state][k] = max(
                        dp[nxt_state][k], 
                        dp[i][j] + (pts[k] - pts[j]).abs()
                    );
                    ans = max(ans, dp[nxt_state][k]);
                }
            }
        }
        answer.push(/* value = */ ans);
    }

    answer.output();
    return 0;
}