/*アルゴリズムと工夫点(Many Balls/CPU: 1 ms Memory: 3796 KB  Length: 513 B)
0から始めるのではなく，Nから操作を逆に行って判定する．現在のNの値が奇数ならAの操作で-1,偶数ならBの操作で/2することで，最小の操作回数でN->0にできる．
最悪計算量は，O(120)<10^6 となり，十分高速．
*/
#include<iostream>
#include<stack>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;

ll n;

int main(){
    int i,j;
    stack<bool> sta;
    scanf("%lld",&n);
    while(n>0&&sta.size()<120){
        if(n%2==0){
            n/=2;
            sta.push(true);
        }else{
            n-=1;
            sta.push(false);
        }
    }
    while(sta.size()){
        printf("%c",sta.top()?'B':'A');
        sta.pop();
    }
    puts("");
    return 0;
}