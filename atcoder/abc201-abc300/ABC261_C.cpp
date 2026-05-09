/*アルゴリズムと工夫点(NewFolder(1)/CPU: 310 ms Memory: 19380 KB  Length: 460 B)

*/
#include<iostream>
#include<map>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
string str;

int main(){
    int i,j;
    scanf("%d",&n);
    map<string,int> dic;
    rep(i,n){
        cin>>str;
        if(dic.find(str)==dic.end())cout<<str<<'\n';
        else printf("%s(%d)\n",str.c_str(),dic[str]);
        dic[str]++;
    }
    return 0;
}