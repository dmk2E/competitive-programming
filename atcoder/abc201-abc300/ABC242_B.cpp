/*アルゴリズムと工夫点(Minimize Ordering/CPU: 8 ms Memory: 3632 KB  Length: 268 B)

*/
#include<iostream>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string s;

int main(){
    cin>>s;
    sort(s.begin(),s.end());
    cout<<s<<endl;
    return 0;
}