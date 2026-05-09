/*アルゴリズムと工夫点(Kaiten Sushi/CPU: 87 ms Memory: 5680 KB  Length: 1163 B)
この問題は，「「Ai<=Bj」を満たす最小のiを求めよ．」と言い換えることができる．
よって、(Ai,i)の形の要素を，Aiの値の昇順にソートして保持した配列Cを用意する．
その後，minId[i]=(C[0,i]の範囲で最小のi) を時系列処理でO(N)で求めておく．
そうすると各Biについて，二分探索でAi<=Bjを満たす最大のi,mnIを求めることができるため，minId[mnI]を出力すればよい．
最悪計算量は O(N+M*log2(N))<10^6 となり十分高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct P{
    int first,second;
    P(int f=0,int s=0):first(f),second(s){}

    bool operator<(const P& k)const{
        return (first<k.first)||(first==k.first&&second<k.second);
    }
};

int n,m,b;

int main(){
    int i,j,left,right,mid;
    scanf("%d%d",&n,&m);
    vector<P> ipt(n);
    rep(i,n){
        scanf("%d",&ipt[i].first);
        ipt[i].second=i;
    }
    sort(ipt.begin(),ipt.end());
    const int INF=n;
    vector<int> minI(n,INF);
    minI[0]=ipt[0].second;
    for(i=1;i<n;i++){
        minI[i]=min(ipt[i].second,minI[i-1]);
    }
    //rep(i,n)printf("(%d,%d)",ipt[i].first,ipt[i].second);
    while(m--){
        scanf("%d",&b);
        left=0,right=n;
        while(left<right){
            mid=(left+right)/2;
            if(ipt[mid].first<=b)left=mid+1;
            else right=mid;
        }
        if(left==0)printf("-1\n");
        else{
            printf("%d\n",minI[left-1]+1);
        }
    }
    return 0;
}