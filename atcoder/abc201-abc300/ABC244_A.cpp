/*アルゴリズムと工夫点(Last Letter/CPU: 1 ms Memory: 3824 KB  Length: 272 B)

*/
#include<iostream>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
string s;

int main(){
    scanf("%d",&n);
    cin>>s;
    cout<<s.back()<<endl;
    return 0;
}