/*アルゴリズムと工夫点(Dividing Game/CPU: 15 ms Memory: 4396 KB  Length: 1254 B)
数を素因数分解し，素数のボールの山があると考えると，「約数に変える」という操作は，「一つの山からボールを好きなだけとる」という処理に言い換えることができる．
これは「ただの石取りゲーム」で「NIM」という．NIMでは，いくつかのボールの山があり，「一つの山からボールを好きなだけとる」という操作を二人で交互に行い，操作が行えなくなった方の負けというゲーム．
全ての山の数のXORを取った時，その値が「0」である時，その状態から始めた人は相手が適切な操作をした場合，必ず負ける．非0である時，その状態から始めた人は必ず勝てる手が存在する．
NIMにおける各山の数をGrundy数といい，今回は素因数の個数となる．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_NUM (int)(1e5)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
vector<int> cnt,minPF;

vector<int> erato(){
    int i,j;
    const int NIL=-1;
    vector<int> minPF(MAX_NUM+1,NIL);
    vector<bool> isPrime(MAX_NUM+1,true);
    isPrime[0]=isPrime[1]=false;
    minPF[0]=0;minPF[1]=1;
    for(i=2;i<=MAX_NUM;i++){
        if(isPrime[i]){
            j=2*i;
            minPF[i]=i;
            while(j<=MAX_NUM){
                isPrime[j]=false;
                if(minPF[j]==NIL)minPF[j]=i;
                j+=i;
            }
        }
    }
    return minPF;
}

int main(){
    int i,j;
    ll sum=0;
    scanf("%d",&n);
    minPF=erato();
    auto val2PFs=[&](int x)->int{
        int p,cnt=0;
        while(x>1){
            p=minPF[x];
            while(x%p==0){
                x/=p;
                cnt++;
            }
        }
        return cnt;
    };
    rep(i,n){
        scanf("%d",&j);
        cnt.push_back(val2PFs(j));
        //printf("%d ",cnt.back());
        sum^=cnt.back();
    }
    //puts("");
    printf("%s\n",sum==0?"Bruno":"Anna");
    return 0;
}