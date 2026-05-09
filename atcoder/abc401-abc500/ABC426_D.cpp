/*アルゴリズムと工夫点(Pop and Insert/CPU: 58 ms Memory: 8312 KB  Length: 1244 B)
RLE を用いて解く．
目標状態にするために必要な操作回数の計算を，シミュレーションではなく，配列の各要素に対して何回操作を行うかを数え上げる方針．
最悪計算量は，O(N) < 10^6
※ 目標状態に持っていくまでに，操作を行わない"区間"を固定するという見方はできていなかったため，覚えておきたい．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Data{
    char x;
    int cnt;

    Data(bool x = false, int cnt = 0):x(x),cnt(cnt){}
};

int t;

int solve(){
    int i,n,ans;
    string s;
    scanf("%d",&n);cin>>s;
    vector<Data> rle;
    i = 0;
    while(i < s.length()){
        Data d;
        d.x = s[i];d.cnt = 1;
        i++;
        while(i < s.length() && d.x == s[i]){
            d.cnt++;
            i++;
        }
        rle.push_back(d);
    }
    int one_sum = 0, zero_sum = 0;
    rep(i,rle.size())if(rle[i].x == '1')one_sum += rle[i].cnt;
    rep(i,rle.size())if(rle[i].x == '0')zero_sum += rle[i].cnt;
    ans = 2 * n;
    rep(i,rle.size()){
        if(rle[i].x == '0'){
            ans = min(
                ans, 
                one_sum  + (zero_sum - rle[i].cnt) * 2
            );
        }else{
            ans = min(
                ans, 
                zero_sum + (one_sum - rle[i].cnt) * 2
            );
        }
    }
    return ans;
}

int main(){
    scanf("%d",&t);
    while(t--)printf("%d\n",solve());
    return 0;
}