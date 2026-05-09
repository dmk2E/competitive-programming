/*アルゴリズムと工夫点(AtCoder Cards/CPU: 7 ms Memory: 3904 KB  Length: 986 B)
「各アルファベットの登場数を一致させることができるか」という視点で解く．
最悪計算量はO(|S|+|T|)<10^6 となり十分高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string s,t;
const string at="atcoder";

int main(){
    int i,j,atS=0,atT=0;
    cin>>s>>t;
    const int MAX_ALFA=26;
    vector<int> alfaS(MAX_ALFA,0),alfaT(MAX_ALFA,0);
    rep(i,s.length()){
        if(s[i]=='@')atS++;
        else alfaS[s[i]-'a']++;
        if(t[i]=='@')atT++;
        else alfaT[t[i]-'a']++;
    }
    auto judge=[&](char x)->bool{
        for(char ss:at)if(x==ss)return true;
        return false;
    };
    rep(i,MAX_ALFA){
        if(alfaS[i]!=alfaT[i]){
            if(judge('a'+i)){
                j=max(alfaS[i],alfaT[i]);
                atS-=abs(j-alfaS[i]);
                atT-=abs(j-alfaT[i]);
            }else{
                puts("No");
                return 0;
            }
        }
    }
    printf("%s\n",(atS>=0&&atT>=0)?"Yes":"No");
    return 0;
}