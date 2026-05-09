/*アルゴリズムと工夫点(Strange Balls/CPU: 27 ms Memory: 4168 KB  Length: 776 B)
ボールの消滅は，ボールを落とした時にしか起こらない．
そのため，スタックで(かかれた整数，ボールの連続数) と管理してシミュレーションすればよい．
最悪計算量は O(N)<10^6 となり十分高速．
*/
#include<iostream>
#include<stack>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

int n;

int main(){
    int i,j,sum=0;
    scanf("%d",&n);
    stack<P> rle;
    while(n--){
        scanf("%d",&i);
        if(rle.size()==0)
            rle.push(P(i,1));
        else{
            if(rle.top().first==i){
                j=rle.top().second;
                rle.pop();
                rle.push(P(i,j+1));
            }else
                rle.push(P(i,1));
        }
        sum++;
        if(rle.top().first==rle.top().second){
            sum-=rle.top().second;
            rle.pop();
        }
        printf("%d\n",sum);
    }
    return 0;
}