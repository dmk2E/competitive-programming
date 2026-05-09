/*アルゴリズムと工夫点(Joint Two Strings/CPU: 53 ms Memory: 9420 KB  Length: 1157 B)
ソート + 尺取り法で解く．
ある文字列Sの「先頭長さ」を，「SとT共に先頭から順に走査した際に，部分列として含む長さ」とする．
また，ある文字列Sの「末尾長さ」を，「SとT共に末尾から順に走査した際に，部分列として含む長さ」とする．
 例）T = "bac" の場合
 ・"abba" -> 先頭長さ = 2, 末尾長さ = 0
 ・"bca" -> 先頭長さ = 1, 末尾長さ = 1
 ・"aaca" -> 先頭長さ = 0, 末尾長さ = 2
すると本問題は，「先頭長さ」+「末尾長さ」の値が，Tの文字列の長さ以上となるような，(i, j)の組の個数を求めればよい．
これは，先頭長さの配列 head と，末尾長さの配列 tail を用いて，尺取り法を行うことで高速に計算可能．
最悪計算量は，O(N * log2(N)) < 10 ^ 7 となり高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
string t;

int calcMaxSubStrLen(string& target, string& sub){
    int t_i = 0, sub_i = 0;
    while(t_i < target.size() && sub_i < sub.size()){
        if(target[t_i] == sub[sub_i])sub_i++;
        t_i++;
    }
    return sub_i;
}

int main(){
    int i, j;
    scanf("%d", &n);
    cin >> t;
    string rev_t = t;
    reverse(rev_t.begin(), rev_t.end());

    vector<int> head, tail;
    rep(i, n){
        string s;
        cin >> s;
        head.push_back(calcMaxSubStrLen(/* target = */ s, /* sub = */ t));
        
        reverse(s.begin(), s.end());
        tail.push_back(calcMaxSubStrLen(/* target = */ s, /* sub = */ rev_t));
    }

    sort(head.begin(), head.end());
    sort(tail.begin(), tail.end());

    ll ans = 0;
    for(int l = 0, r = n - 1;l < n;l++){
        while(r >= 0 && head[l] + tail[r] >= t.size())r--;
        ans += n - r - 1;
    }
    printf("%lld\n", ans);
    return 0;
}