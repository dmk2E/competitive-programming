/*アルゴリズムと工夫点(chukodai/CPU: 2 ms Memory: 3812 KB  Length: 281 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string s;

int main(){
    int i,j;
    cin>>s;
    scanf("%d%d",&i,&j);
    swap(s[i-1],s[j-1]);
    cout<<s<<endl;
    return 0;
}