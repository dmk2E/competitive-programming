/*アルゴリズムと工夫点(Word Ladder/CPU: 1 ms Memory: 3680 KB  Length: 745 B)

*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string s,t;

int main(){
    int i;
    cin>>s>>t;
    vector<int> cnt(s.length());
    vector<string> ans;
    rep(i,s.length())
        cnt[i]=(int)t[i]-(int)s[i];
    rep(i,s.length()){
        if(cnt[i]<0){
            s[i]=t[i];
            ans.push_back(s);
        }
    }
    rep(i,s.length()){
        if(s[s.length()-1-i]!=t[t.length()-1-i]){
            s[s.length()-1-i]=t[t.length()-1-i];
            ans.push_back(s);
        }
    }
    cout<<ans.size()<<endl;
    rep(i,ans.size())
        cout<<ans[i]<<endl;
    return 0;
}