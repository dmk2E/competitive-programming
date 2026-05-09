/*アルゴリズムと工夫点(Move Right/CPU: 1 ms Memory: 3580 KB  Length: 371 B)

*/
#include<iostream>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string ipt;

int main(){
    int i;
    cin>>ipt;
    for(i=ipt.size()-1;i>=0;i--){
        if(ipt[i]=='1'&&i+1<ipt.size())ipt[i+1]='1';
        ipt[i]='0';
    }
    cout<<ipt<<endl;
    return 0;
}