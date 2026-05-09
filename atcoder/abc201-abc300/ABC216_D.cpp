/*アルゴリズムと工夫点(Pair of Balls/CPU: 167 ms Memory: 29916 KB  Length: 2659 B)
その時点で選択することができるボールの中で，最も数が多い色とその数をセグ木で高速で求めることができるため，シミュレーションで解ける．
その色のボールがどの筒にあるのかというデータa2Tutuと，それぞれの筒の一番上のボールの色をそれぞれ保持するデータcntを保持して置く．
すると毎回のシミュレーションで，セグ木，a2Tutu，cntの更新はそれぞれ2回しか行われないから，最悪計算量はO(N*log2(N))<10^7 より，十分高速．
※初見4完!嬉しいぜ
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define NNIL -1
using namespace std;

const int NIL=0;

typedef struct data{
    int x,id;

    data(int xx=NIL,int iid=NIL):x(xx),id(iid){}
}Data;

typedef class SegmentTree{
public:
    int n,size;
    vector<Data> tree;
public:
    SegmentTree(int nn=0){
        n=1;
        size=nn;
        while(n<nn)n*=2;
        int i;
        tree=vector<Data>(2*n-1);
        for(i=n-1;i<2*n-1;i++)
            tree[i]=Data(NIL,i-n+1);
    }

    void update(int k,int x){
        k+=n-1;
        tree[k].x=x;
        while(k>0){
            k=(k-1)/2;
            if(tree[2*k+1].x<tree[2*k+2].x){
                tree[k].x=tree[2*k+2].x;
                tree[k].id=tree[2*k+2].id;
            }else{
                tree[k].x=tree[2*k+1].x;
                tree[k].id=tree[2*k+1].id;
            }
        }
    }

    Data query(int a,int b,int k,int l,int r){
        if(r<0)r=n;
        if(b<=l||r<=a)return Data();
        if(a<=l&&r<=b)return tree[k];
        Data left=query(a,b,2*k+1,l,(l+r)/2),right=query(a,b,2*k+2,(l+r)/2,r);    
        return left.x<right.x?right:left;
    }

    int get(int id){
        return tree[id+n-1].x;
    }

    void show(){
        int i;
        rep(i,size)
            printf("%d ",tree[i+n-1].x);
        puts("");
    }
}SegT;

int n,m;
vector<int> cnt;
vector<vector<int> > tutu,a2Tutu;

int main(){
    int i,j,k;
    Data tmp;
    scanf("%d%d",&n,&m);
    cnt=vector<int>(m,0);
    a2Tutu=vector<vector<int> >(n,vector<int>(0));
    tutu=vector<vector<int> >(m,vector<int>(0));
    SegT tree(n);
    rep(i,m){
        scanf("%d",&k);
        while(k--){
            scanf("%d",&j);
            j--;
            tutu[i].push_back(j);
        }
    }
    rep(i,m){
        tree.update(tutu[i][cnt[i]],1+tree.get(tutu[i][cnt[i]]));
        a2Tutu[tutu[i][cnt[i]]].push_back(i);
    }
    rep(i,n){
        //tree.show();
        tmp=tree.query(0,n,0,0,NNIL);
        //printf("%d %d\n",tmp.id,tmp.x);
        if(tmp.x<2)
            break;
        tree.update(tmp.id,0);
        rep(j,2){
            cnt[a2Tutu[tmp.id][j]]++;
            if(cnt[a2Tutu[tmp.id][j]]<tutu[a2Tutu[tmp.id][j]].size()){
                tree.update(tutu[a2Tutu[tmp.id][j]][cnt[a2Tutu[tmp.id][j]]],1+tree.get(tutu[a2Tutu[tmp.id][j]][cnt[a2Tutu[tmp.id][j]]]));
                a2Tutu[tutu[a2Tutu[tmp.id][j]][cnt[a2Tutu[tmp.id][j]]]].push_back(a2Tutu[tmp.id][j]);
            }
        }
    }
    //tree.show();
    printf("%s\n",i==n?"Yes":"No");
    return 0;
}