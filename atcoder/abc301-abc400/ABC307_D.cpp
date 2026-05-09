/*アルゴリズムと工夫点(Mismatched Parentheses/CPU: 5 ms Memory: 5644 KB  Length: 823 B)
貪欲法+imos法による区間管理を利用して解く．
`('と`)'の対応が正しくとれている区間を，その長さが最も小さい順に削除していけば解は求まる．
ただし愚直に削除するのではなく，``削除された文字か否か''を，``値が0であるか否か''で判定する別の一次元配列を保持しておき，処理を行う．
この配列は，処理中に適切にimos法を行うことで作成可能である．
最悪計算量は，O(N)<10^6 となり高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
string s;

int main(){
    int i,j;
    scanf("%d",&n);
    cin>>s;
    vector<int> sta,imos(n+1,0);
    rep(i,n){
        switch(s[i]){
            case '(':
                sta.push_back(i);
                break;
            case ')':
                if(sta.size()){
                    j=sta.back();sta.pop_back();
                    imos[j]++;
                    imos[i+1]--;
                }
                break;
            default:
                break;
        }
    }
    rep(i,n)imos[i+1]+=imos[i];
    string ans="";
    rep(i,n)if(imos[i]==0)ans+=s[i];
    cout<<ans<<'\n';
    return 0;
}