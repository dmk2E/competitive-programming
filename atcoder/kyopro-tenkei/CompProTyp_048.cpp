/*アルゴリズムと工夫点(I will not drop out/CPU: 105 ms Memory: 6540 KB  Length: 855 B)
どの問題についても解くのにかかる時間は同じであり，部分点をとった後に同じ問題から獲得できる点数はその部分点よりも少ない．したがって，全問題の中で最も高い点を取れる問題から順に解いていく貪欲法で解ける．
常に最大値を高速で取得できるように優先度付きキューを用いる．最悪計算量はO((N+K)log2(N))<10^7 となり，高速．
※上界や下界を見積もり，その値を高速に求める手段がそのまま解になることができる場合がある．
*/
#include<iostream>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;

typedef struct data{
    int a,b;
    bool flag;

    data(int aa=0,int bb=0):a(aa),b(bb){flag=true;}

    int getPoint()const{
        return flag?b:a-b;
    }

    bool operator<(const data& k)const{
        return getPoint()<k.getPoint();
    }
}Data;

int n,k;

int main(){
    int i,j;
    long long ans=0;
    priority_queue<Data> PQ;
    Data temp;
    scanf("%d%d",&n,&k);
    while(n--){
        scanf("%d%d",&i,&j);
        PQ.push(Data(i,j));
    }
    while(k--){
        temp=PQ.top();PQ.pop();
        //printf("%d\n",temp.getPoint());
        ans+=temp.getPoint();
        if(temp.flag){
            temp.flag=false;
            PQ.push(temp);
        }
    }
    printf("%lld\n",ans);
    return 0;
}