/*アルゴリズムと工夫点(文字列のおいしいドーナッツ/CPU: - ms Memory: - KB  Length: - B)
シミュレーションで解く．
一口で食べられなくなるまで，部分文字列を順に食べていけばよい．
対象文字列S とすると，最悪計算量は，O(|S| ^ 2) < 10 ^ 5 となり，十分高速．
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
//     "MGTToodDOkkkNUTM",
//     "MisssssissipppiiPPippi",
//     "GFeedCAaaaaaaaAbBbCddeFG"
// };
vector<string> ipt = {
    "zzvvJJaOkuIPPIQQhodakSSjjjXXaFyyyujiKitvz",
    "AAKKAyyyuummmuFFTuvpppvvuuuIIpppRtAALUUeooonHLLHnnfffPPNNkknnnkjjjkAmeA",
    "zzDDfBBsGGkJrrrJpppZZhryyyrrISSInnntWWmXxxxjjjFFXrrDODDODNNrhhhaaWztttzzWTTaNgmNkkkDDNmAAmLLmeeeKlllOTSYoDDfPPkkkAPPAffjjjSSamvvnnnlHHllvz"
};
Outputer<string> answer;
const char NIL = '*';

string eraseNil(string str){
    string ans = "";
    for(char c : str)if(c != NIL)ans += c;
    return ans;
}

int main(){
    int i, j;

    for(int ipt_id = 0;ipt_id < INPUT_NUMBER;ipt_id++){
        string str = ipt[ipt_id];

        bool is_eaten = true;
        while(is_eaten){
            is_eaten = false;
            rep(i, str.size()){
                auto isThreeSameLower = [&](char s0, char s1, char s2) -> bool{
                    return islower(s0) && islower(s1) && islower(s2) && s0 == s1 && s1 == s2;
                };
                if(str.size() >= 3 && isThreeSameLower(
                    /* s0 = */ str[i], 
                    /* s1 = */ str[(i + 1) % str.size()], 
                    /* s2 = */ str[(i + 2) % str.size()]
                )){
                    is_eaten = true;
                    str[i] = str[(i + 1) % str.size()] = str[(i + 2) % str.size()] = NIL;
                    str = eraseNil(/* str = */ str);
                    break;
                }

                auto isTwoSameUpper = [&](char s0, char s1) -> bool{
                    return isupper(s0) && isupper(s1) && s0 == s1;
                };
                if(str.size() >= 2 && isTwoSameUpper(
                    /* s0 = */ str[i], 
                    /* s1 = */ str[(i + 1) % str.size()]
                )){
                    is_eaten = true;
                    str[i] = str[(i + 1) % str.size()] = NIL;
                    str = eraseNil(/* str = */ str);
                    break;
                }
            }
        }
        answer.push(/* value = */ str);
    }

    answer.output(/* prefix = */ "\"", /* suffix = */ "\"");
    return 0;
}