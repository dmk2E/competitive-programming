/*アルゴリズムと工夫点(Perfect String/CPU: 1 ms Memory: 3660 KB  Length: 575 B)

*/
#include<iostream>
#include<map>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string s;

int main(){
    int i,j;
    bool flag_1=false,flag_2=false;
    cin>>s;
    map<char,int> v;
    rep(i,s.length()){
        if(isupper(s[i]))flag_1=true;
        if(islower(s[i]))flag_2=true;
        if(v.find(s[i])!=v.end()){
            puts("No");
            return 0;
        }
        v[s[i]]++;
    }
    printf("%s\n",flag_1&&flag_2?"Yes":"No");
    return 0;
}