/*アルゴリズムと工夫点(時間の計算/CPU: - ms Memory: - KB  Length: - B)
秒数に変換して計算し，その計算結果を文字列表現に直せばよい．
24時間（60 * 60 * 24）を単位とし，計算結果は全てその余りを取る形にする必要があることに注意．
*/
#include<iostream>
#include<vector>
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

// vector<string> ipt = {
//     "0h0m59s+0h0m1s",
//     "1h59m59s-2h0m0s",
//     "4h5m10s-10h15m3s+7h0m0s"
// };
vector<string> ipt = {
    "0h0m0s-0h41m6s+20h54m10s+23h59m59s-1h23m13s+15h4m7s+14h46m10s",
    "16h13m37s-17h15m28s+10h51m31s-0h0m0s+15h39m56s-18h35m25s+19h17m42s-20h32m46s+22h21m31s",
    "0h4m7s-23h19m2s-19h47m15s-23h31m23s-22h45m58s-19h27m58s-21h9m59s-22h14m57s-19h39m36s-23h59m59s"
};
Outputer<string> answer;

int main(){
    int i, j;

    const int MAX_TIME = 24 * 60 * 60;
    for(int ipt_id = 0;ipt_id < INPUT_NUMBER;ipt_id++){
        auto calc = [&](string equation) -> string{
            auto convert2Seconds = [](string time) -> int{
                auto str2Int = [](string str) -> int{
                    int ans = 0;
                    for(char c : str){
                        ans *= 10;
                        ans += c - '0';
                    }
                    return ans;
                };
                int pos_h = time.find('h');
                int pos_m = time.find('m');
                int pos_s = time.find('s');
                return str2Int(/* str = */ time.substr(0, pos_h)) * 60 * 60 + 
                       str2Int(/* str = */ time.substr(pos_h + 1, pos_m - pos_h - 1)) * 60 +
                       str2Int(/* str = */ time.substr(pos_m + 1, pos_s - pos_m - 1));
            };

            const int NIL = -1;
            int i = 0, left = NIL, start_id = NIL;
            char last_ope, nxt_ope;
            while(i < equation.size()){
                if(start_id == NIL)start_id = i;
                if(equation[i] == '+' || equation[i] == '-'){
                    nxt_ope = equation[i];
                    
                    int right = convert2Seconds(/* time = */ equation.substr(start_id, i - start_id));
                    if(left == NIL)left = right;
                    else if(last_ope == '+')left = (left + right) % MAX_TIME;
                    else left = (MAX_TIME + left - right) % MAX_TIME;
                    
                    last_ope = nxt_ope;
                    start_id = NIL;
                }
                i++;
            }
            if(last_ope == '+')left = (left + convert2Seconds(/* time = */ equation.substr(start_id))) % MAX_TIME;
            else left = (MAX_TIME + left - convert2Seconds(/* time = */ equation.substr(start_id))) % MAX_TIME;

            auto convertToStr = [](int time) -> string{
                int seconds = time % 60;
                time /= 60;
                int minutes = time % 60;
                time /= 60;
                int hours = time % 60;
                return to_string(hours) + "h" + to_string(minutes) + "m" + to_string(seconds) + "s";
            };
            return convertToStr(/* time = */ left);
        };

        answer.push(/* value = */ calc(/* equation = */ ipt[ipt_id]));
    }

    answer.output(/* prefix = */ "\"", /* suffix = */ "\"");
    return 0;
}