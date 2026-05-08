/*アルゴリズムと工夫点(Square Permutation/CPU: 373 ms Memory: 3920 KB  Length: 806 B)
平方数を列挙し，文字列Sがその値をとり得るか判定すればよい．
N <= 13 より，候補となり得る平方数は，√10 ^ 13 < 10 ^ 7 個未満である．
またSの並び替えが，これらの平方数xをとり得るかの判定は，下記のロジックで O(|S|) で実装可能である．
 ・S と 「x の文字列」の長さが不一致である時，x に'0'を追加し，x' を作成
 ・S と x' をそれぞれソートし，完全一致するか判定
最悪計算量は，O(n * log2|n| * √(10 ^ n)) ≒ 10 ^ 8 となり，間に合う．
*/
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
string s;

bool judge(ll target_power_2){
    string target = to_string(target_power_2);
    while(target.size() < s.size())target += "0";
    
    sort(target.begin(), target.end());
    return s == target;
}

int main(){
    int i, j;
    scanf("%d", &n);
    cin >> s;
    sort(s.begin(), s.end());

    int ans = 0;
    ll max_num = pow(10, n);
    ans += judge(/* target_power_2 = */ 0); // '0' も平方数であるため
    for(i = 1;i < (max_num + i - 1) / i;i++)
        ans += judge(/* target_power_2 = */ (ll)i * i);

    printf("%d\n", ans);
    return 0;
}