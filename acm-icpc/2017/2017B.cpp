/*アルゴリズムと工夫点(ほとんど同じプログラム/CPU: 0 ms Memory: 3368 KB  Length: 1319 B)
文字列定数の部分は一つの塊として扱い，文字列比較を行う．この時，文字列定数を一つの文字とみなした時の2つの文字列の長さが異なる場合，"DIFFERENT"が解となる．
文字列定数だけが1回だけ異なる場合は，"CLOSE"となるが，2回以上異なると"DIFFERENT"となる．
また，文字列定数以外の文字が1つでも異なる場合も"DIFFERENT"となる．
それ以外の場合は"IDENTICAL"となる．
1テストケース当たりの最悪計算量は O(|S|) <10^3 となり十分高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string s0,s1;

vector<string> strEncoder(const string& s){
    int i,now;
    vector<string> ans;
    i=0;
    while(i<s.length()){
        if(s[i]=='\"'){
            i++;
            ans.push_back("\"");
            while(s[i]!='\"'){
                ans.back()+=s[i];
                i++;
            }
            ans.back()+="\"";
        }else ans.push_back(s.substr(i,1));
        i++;
    }
    //rep(i,ans.size())cout<<ans[i]<<endl;puts("");
    return ans;
}

int main(){
    int i,j;
    while(1){
        cin>>s0;
        if(s0==".")break;
        cin>>s1;
        vector<string> s0_encoded,s1_encoded;
        s0_encoded=strEncoder(s0);
        s1_encoded=strEncoder(s1);
        if(s0_encoded.size()!=s1_encoded.size())
            puts("DIFFERENT");
        else{
            j=0;
            rep(i,s0_encoded.size()){
                if(s0_encoded[i]!=s1_encoded[i]){
                    if(s0_encoded[i].size()>=2&&s1_encoded[i].size()>=2&&j==0)j++;
                    else break;
                }
            }
            printf("%s\n",i<s0_encoded.size()?"DIFFERENT":(j==1?"CLOSE":"IDENTICAL"));
        }
    }
    return 0;
}