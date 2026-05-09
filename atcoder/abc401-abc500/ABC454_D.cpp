/*アルゴリズムと工夫点((xx)/CPU: 147 ms Memory: 10552 KB  Length: 817 B)
スタックを用いて解く．
「標準形」の考え方を用いると，
「文字列Aに対して複数回の操作を行うことで，B にできるか」=「A, Bそれぞれに含まれる括弧の数を最小にした形は同じか」
という性質が存在する．
従って，最悪計算量は，O(|A| + |B|) < 10 ^ 7 となり高速．
※ 標準形：複数の状態をとり得るデータX が存在する時，どの状態のXでも，
           状態遷移を繰り返すことで到達できる，一意な状態のこと
※ 今回の問題の様に，状態遷移が双方向に可能（可逆）である場合，「2状態の標準形が同値であるか」という指標を用いることが可能
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int t;

string minParentheses(const string str){
    string stk = "";
    for(char c : str){
        if(
            c == ')' && 
            stk.size() >= 3 && stk.substr(stk.size() - 3, 3) == "(xx"
        ){
            stk.pop_back();stk.pop_back();stk.pop_back();
            stk.push_back('x');stk.push_back('x');
        }else stk.push_back(c);
    }
    return stk;
}

bool solve(){
    string a, b;
    cin >> a >> b;
    return minParentheses(/* str = */ a) == minParentheses(/* str = */ b);
}

int main(){
    scanf("%d", &t);
    while(t--)printf("%s\n", solve() ? "Yes" : "No");
    return 0;
}