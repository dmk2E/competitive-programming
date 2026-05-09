/*アルゴリズムと工夫点(Cooking/CPU: 275 ms Memory: 8724 KB  Length: 660 B)
二つのオーブンそれぞれで使用する料理を、2つの集合A,Bに分けることを考える。集合Aの料理を作るのにかかる時間の合計は集合Bのもの以上であると仮定しても一般性は失わない。T1+T2+...+TN=Sとすると、
time(A)+time(B)=S かつ time(A)>=time(B) より、time(A)>=S/2 となる。したがってこの条件を満たすように料理を選んだ時、time(A)の最小値を求めればよい(∵time(A)>time(B))。
これは料理にかかる時間の部分和問題に帰着できる。
*/
#include<iostream>
#include<vector>
#include<set>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;

int n;
vector<int> t;
set<int> v[2];

int main(){
    int i,j,now=0,sum=0;
    scanf("%d",&n);
    rep(i,n){
        scanf("%d",&j);
        t.push_back(j);
        sum+=j;
        v[(now+1)%2].insert(j);
        for(int x:v[now]){
            v[(now+1)%2].insert(x);
            v[(now+1)%2].insert(x+j);
        }
        v[now].clear();
        now=(now+1)%2;
    }
    sum=(sum+2-1)/2;
    for(int x:v[now]){
        if(x>=sum){
            printf("%d\n",x);
            return 0;
        }
    }
    return 0;
}