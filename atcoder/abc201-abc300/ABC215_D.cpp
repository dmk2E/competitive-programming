/*アルゴリズムと工夫点(Coprime 2/CPU: 78 ms Memory: 4100 KB  Length: 1045 B)
エラトステネスの篩の要領で，任意の整数列(a1,a2,a3,...,an)の倍数の整数を消す場合，任意の順番でaiの倍数を消していけばよい．この時，既にaiが消されていた場合は，処理を行う必要はない．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;

int n,m,a;

vector<int> pFact(int x){
    int i;
    vector<int> tmp;
    for(i=2;i*i<=x;i++){
        if(x%i==0){
            if(x/i<=m)tmp.push_back(x/i);
            if(i<=m)tmp.push_back(i);
        }
    }
    if(x!=1&&x<=m)tmp.push_back(x);
    return tmp;
}

int main(){
    int i,j;
    vector<int> factor,ans;
    scanf("%d%d",&n,&m);
    vector<bool> judge(m+1,true);
    while(n--){
        scanf("%d",&a);
        factor=pFact(a);
        rep(i,factor.size()){
            if(judge[factor[i]]){
                judge[factor[i]]=false;
                j=2*factor[i];
                while(j<=m){
                    judge[j]=false;
                    j+=factor[i];
                }
            }
        }
    }
    for(i=1;i<=m;i++)
        if(judge[i])
            ans.push_back(i);
    printf("%d\n",(int)ans.size());
    rep(i,ans.size())
        printf("%d\n",ans[i]);
    return 0;
}