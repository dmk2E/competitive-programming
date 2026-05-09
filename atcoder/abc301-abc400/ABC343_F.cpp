/*アルゴリズムと工夫点(Second Largest Query/CPU: 1045 ms Memory: 11508 KB  Length: 3101 B)
segtree実装時の留意点
・2のべき乗に変化させる前の入力値を対比したうえで、配列の初期状態を受け取る必要があること。
・マージソートと同様に、ある範囲rにおける必要な情報を節点毎に保持するだけでなく、左の子のrと右の子のrから、親のrの情報を決定していく、分割統治法を意識する必要がある。
*/
#include<iostream>
#include<vector>
#include<map>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define NIL -1
using namespace std;

typedef struct data{
    int first,second,cntF,cntS;

    data(int ffirst=NIL,int ccntF=NIL,int ssecond=NIL,int ccntS=NIL):first(ffirst),second(ssecond),cntF(ccntF),cntS(ccntS){}
}Data;

int n,q;
vector<Data> segT;

void init(int nn){
    int i;
    n=1;
    while(n<nn)n*=2;
    segT.resize(2*n-1);
    rep(i,nn)
        segT[n-1+i]=Data();
}

void update(int k,int a){
    int i;
    k+=n-1;
    //printf("segT[%d].first=%d\n",k,a);
    segT[k].first=a;
    segT[k].cntF=1;
    map<int,int>::iterator it;
    while(k>0){
        map<int,int> temp;
        k=(k-1)/2;
        //printf("%d:%d %d %d %d\n",k,segT[k].first,segT[k].cntF,segT[k].second,segT[k].cntS);printf("%d:%d %d %d %d\n",2*k+1,segT[2*k+1].first,segT[2*k+1].cntF,segT[2*k+1].second,segT[2*k+1].cntS);printf("%d:%d %d %d %d\n",2*k+2,segT[2*k+2].first,segT[2*k+2].cntF,segT[2*k+2].second,segT[2*k+2].cntS);puts("");
        if(segT[2*k+1].first!=NIL)
            temp[segT[2*k+1].first]+=segT[2*k+1].cntF;
        if(segT[2*k+1].second!=NIL)
            temp[segT[2*k+1].second]+=segT[2*k+1].cntS;
        if(segT[2*k+2].first!=NIL)
            temp[segT[2*k+2].first]+=segT[2*k+2].cntF;
        if(segT[2*k+2].second!=NIL)
            temp[segT[2*k+2].second]+=segT[2*k+2].cntS;
        temp[NIL]=NIL;
        it=temp.end(),it--;
        segT[k].first=it->first;segT[k].cntF=it->second;it--;
        segT[k].second=it->first;segT[k].cntS=it->second;
    }
    //printf("%d:%d %d %d %d\n",k,segT[k].first,segT[k].cntF,segT[k].second,segT[k].cntS);printf("%d:%d %d %d %d\n",2*k+1,segT[2*k+1].first,segT[2*k+1].cntF,segT[2*k+1].second,segT[2*k+1].cntS);printf("%d:%d %d %d %d\n",2*k+2,segT[2*k+2].first,segT[2*k+2].cntF,segT[2*k+2].second,segT[2*k+2].cntS);puts("");
}

Data query(int a,int b,int k,int l,int r){
    //printf("%d:%d %d %d %d\n",k,segT[k].first,segT[k].cntF,segT[k].second,segT[k].cntS);
    if(b<=l||r<=a) return Data();
    if(a<=l&&r<=b) return segT[k];
    map<int,int> temp;
    map<int,int>::iterator it;
    Data ll=query(a,b,2*k+1,l,(l+r)/2),rr=query(a,b,2*k+2,(l+r)/2,r),qq;
    if(ll.first!=NIL)
        temp[ll.first]+=ll.cntF;
    if(ll.second!=NIL)
        temp[ll.second]+=ll.cntS;
    if(rr.first!=NIL)
        temp[rr.first]+=rr.cntF;
    if(rr.second!=NIL)
        temp[rr.second]+=rr.cntS;
    temp[NIL]=NIL;
    it=temp.end(),it--;
    qq.first=it->first;qq.cntF=it->second;it--;
    qq.second=it->first;qq.cntS=it->second;
    return qq;
}

int main(){
    int i,j,k;
    Data ans;
    scanf("%d%d",&n,&q);
    k=n;
    init(n);
    rep(i,k){
        scanf("%d",&j);
        update(i,j);
    }
    while(q--){
        scanf("%d",&i);
        if(i==1){
            scanf("%d%d",&i,&j);
            update(i-1,j);
        }else{
            scanf("%d%d",&i,&j);
            ans=query(i-1,j,0,0,n);
            printf("%d\n",ans.cntS==NIL?0:ans.cntS);
        }
    }
    return 0;
}