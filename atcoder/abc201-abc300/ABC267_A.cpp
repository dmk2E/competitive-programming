/*アルゴリズムと工夫点(Saturday/CPU: 1 ms Memory: 3812 KB  Length: 363 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int MAX=5;
string days[]={"Monday","Tuesday","Wednesday","Thursday","Friday"};

int main(){
    int i;
    string s;
    cin>>s;
    rep(i,MAX)if(s==days[i])break;
    printf("%d\n",MAX-i);
    return 0;
}