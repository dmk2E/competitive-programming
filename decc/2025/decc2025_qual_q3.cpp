/*アルゴリズムと工夫点(やさしいビンゴゲーム/CPU: - ms Memory: - KB  Length: - B)
メモ化再帰で解く．
ビンゴゲームの状態を，{ マスの状態, 何ターン何もしなかったか, 今何ターン目か } で表現し，
その状態からスタートした時の，最高得点をゲーム木探索の要領で解く．
何もしないターン数が3になるタイミングでは，〇を付けるマスを全探索する形で状態遷移を行う必要があることに注意．
ビンゴカードが，H * W マスである場合，最悪計算量を多めに見積もると，O(2 ^ (H * W) * MAX_IDLE_TURN * MAX_TURN) ≒ 3 * 10 ^ 9
となるが，実際はビンゴになった瞬間に探索が終わり，また毎回の操作で状態遷移先が複数あるわけではないため，より小さい計算量となる．
※ マス状態は，各マスが〇かどうかをビット表現で表している
*/
#include<iostream>
#include<vector>
#include<map>
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

// vector<vector<int> > ipt = {
//     {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,1,2,3,4,50,11,49,48,12,47,46,45,6,7,8,9,10,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,5},
//     {26,31,36,41,46,27,32,37,42,47,28,33,38,43,48,29,34,39,44,49,30,35,40,45,50,1,2,3,4,5,26,27,6,7,8,9,10,11,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,12,13,14,15,16,17,18,19,20,21,22,23,24,25,28,29,30},
//     {11,21,31,41,1,22,32,42,2,12,33,43,3,13,23,44,4,14,24,34,46,47,48,49,50,46,47,48,6,16,26,11,7,17,27,12,8,18,28,13,5,21,22,15,14,9,19,29,50,49,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,25,24,23,20,10,4,3,2,1}
// };
vector<vector<int> > ipt = {
    {43,18,35,34,46,15,8,49,29,19,44,37,7,30,14,13,11,39,27,6,23,36,22,21,50,4,2,27,26,33,10,18,28,42,14,41,17,49,21,23,48,32,35,3,20,12,9,43,8,50,22,40,31,7,1,45,47,44,5,39,37,38,36,29,15,46,24,30,16,11,25,6,34,19,13},
    {8,43,9,29,6,13,47,5,40,27,48,50,10,11,35,44,1,12,3,16,42,33,21,24,2,49,43,27,31,5,20,28,19,32,4,15,48,1,7,29,22,14,10,13,25,35,3,21,12,2,36,40,39,46,44,18,9,8,23,30,16,34,26,45,37,41,17,50,6,38,24,42,11,33,47},
    {39,38,36,24,1,32,45,47,50,48,40,31,30,34,49,41,33,42,25,44,29,28,37,46,43,15,20,41,27,23,1,11,2,10,9,22,31,4,7,16,3,26,5,8,6,47,17,12,43,18,13,46,19,14,33,35,38,28,37,24,42,34,32,36,29,49,21,30,50,25,44,39,48,45,40}
};
Outputer<int> answer;

const int H = 5;
const int W = 5;
const int MAX_NUM = 50;
const int MAX_IDLE = 3;

int main(){
    int i, j;

    for(int ipt_id = 0;ipt_id < INPUT_NUMBER;ipt_id++){
        auto& table = ipt[ipt_id];

        const int NIL = -1;
        int sum = 0;
        vector<int> num_to_y(MAX_NUM + 1, NIL), num_to_x(MAX_NUM + 1, NIL);
        rep(i, H * W){
            sum += table[i];

            num_to_y[table[i]] = i / W;
            num_to_x[table[i]] = i % W;
        }
        vector<int> a;
        for(i = H * W;i < table.size();i++)a.push_back(table[i]);

        vector<vector<map<int, int> > > turn_to_idle_to_state_to_point(a.size(), vector<map<int, int> >(MAX_IDLE));
        auto parseCoord = [&](int y, int x) -> int{
            return y * W + x;
        };
        auto isBingo = [&](int state) -> bool{
            int i, j;
            // 行
            rep(i, H){
                rep(j, W){
                    int id = parseCoord(/* y = */ i, /* x = */ j);
                    if(!((state >> id) & 1))break;
                }
                if(j == W)return true;
            }

            // 列
            rep(j, W){
                rep(i, H){
                    int id = parseCoord(/* y = */ i, /* x = */ j);
                    if(!((state >> id) & 1))break;
                }
                if(i == H)return true;
            }

            // 左上スタートの斜め
            rep(i, H){
                int id = parseCoord(/* y = */ i, /* x = */ i);
                if(!((state >> id) & 1))break;
            }
            if(i == H)return true;

            // 右上スタートの斜め
            rep(i, H){
                int id = parseCoord(/* y = */ i, /* x = */ W - 1 - i);
                if(!((state >> id) & 1))break;
            }
            if(i == H)return true;

            return false;
        };
        auto rec = [&](auto& func, int state, int idle_turn, int now_turn, int sum) -> int{
            if(now_turn == a.size())return 0;

            if(turn_to_idle_to_state_to_point[now_turn][idle_turn].count(state))
                return turn_to_idle_to_state_to_point[now_turn][idle_turn][state];
            
            if(isBingo(/* state = */ state))return sum;
            
            int i, j;
            int ans = NIL;
            int now_a = a[now_turn];
            int now_y = num_to_y[now_a], now_x = num_to_x[now_a];
            int id = parseCoord(/* y = */ now_y, /* x = */ now_x);
            if(now_y != NIL && now_x != NIL && !((state >> id) & 1)){
                // 指定されたマスが存在し，かつ〇が既に書かれていない場合
                int temp = func(
                    /* func = */ func, 
                    /* state = */ state | (1 << id), 
                    /* idle_turn = */ 0, 
                    /* now_turn = */ now_turn + 1, 
                    /* sum = */ sum - now_a
                );
                ans = max(ans, temp);
            }else{
                // 指定されたマスが無効な場合
                if(idle_turn == MAX_IDLE - 1){
                    int i;
                    rep(i, H * W)if(!((state >> i) & 1)){
                        int temp = func(
                            /* func = */ func, 
                            /* state = */ state | (1 << i), 
                            /* idle_turn = */ 0, 
                            /* now_turn = */ now_turn + 1, 
                            /* sum = */ sum - table[i]
                        );
                        ans = max(ans, temp);                        
                    }
                }else{
                    int temp = func(
                        /* func = */ func, 
                        /* state = */ state, 
                        /* idle_turn = */ idle_turn + 1, 
                        /* now_turn = */ now_turn + 1, 
                        /* sum = */ sum
                    );
                    ans = max(ans, temp);
                }
            }

            return turn_to_idle_to_state_to_point[now_turn][idle_turn][state] = ans;
        };
        answer.push(/* value = */ rec(
            /* func = */ rec, 
            /* state = */ 0, 
            /* idle_turn = */ 0, 
            /* now_turn = */ 0, 
            /* sum = */ sum
        ));
    }

    answer.output();
    return 0;
}