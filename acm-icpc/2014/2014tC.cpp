/*アルゴリズムと工夫点(壊れた暗号生成器/CPU: 0 ms Memory: 3432 KB  Length: 1018 B)
再帰下降構文解析で解く．
'?'の部分はそのままにして解析処理を行い，解析後に'?'を'A'に書き換えればよい．

--+書き換えたBNF記法+-------------------------------
<expr>::=<term><expr>|+<expr>|-<expr>|[<expr>]<expr>
<term>::=A|B|...|Z
------------------------------------------

最悪計算量 O(|S|)<10^3 となり高速．

※問題URL：https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2584
*/
//#include<iostream>
//#include<cassert>
#include<bits/stdc++.h>
#define rep(i,n)for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string ipt;
const int ALFA=26;

/// @brief s[now,s.size())の再帰下降構文解析を行う
/// @param s 対象文字列
/// @param now s上の現解析位置
/// @return s[now,s.size())の解析結果
string expr(string& s,int& now){
    int tmp=now;
    string str="";
    if(('A'<=s[now]&&s[now]<='Z')||s[now]=='?'){
        str+=s[now];
        if(now<s.size()-1)str+=expr(s,++now);
    }else if(s[now]=='+'){
        str+=expr(s,++now);
        if(str[0]!='?')str[0]=(char)(((int)str[0]-(int)'A'+1)%ALFA+(int)'A');
    }else if(s[now]=='-'){
        str+=expr(s,++now);
        if(str[0]!='?')str[0]=(char)(((int)str[0]-(int)'A'-1+ALFA)%ALFA+(int)'A');
    }else if(s[now]=='['){
        str+=expr(s,++now);
        now++;
        reverse(str.begin(),str.end());
        str+=expr(s,now);
    }
    return str;
}

int main(){
    int i,j;
    while(1){
        cin>>ipt;
        if(ipt[0]=='.')break;
        i=0;
        string ans=expr(ipt,i);
        rep(i,ans.size())if(ans[i]=='?')ans[i]='A';
        cout<<ans<<'\n';
    }
    return 0;
}