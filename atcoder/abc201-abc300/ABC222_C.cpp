/*アルゴリズムと工夫点(Swiss-System Tournament/CPU: 2 ms Memory: 3920 KB  Length: 1480 B)
algorithmの「sort」は安定なソートではないことに注意．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef struct data{
    int point,id;

    data(int ppoint=0,int iid=0):point(ppoint),id(iid){}

    bool operator<(const data& k){
        return point<k.point||(point==k.point&&id>k.id);
    }
}Data;

int n,m;
vector<string> a;
vector<int> id2Point;
vector<Data> rank2Id;

bool isWin(char l,char r){
    return (l=='G'&&r=='C')||(l=='C'&&r=='P')||(l=='P'&&r=='G');
}

int main(){
    int i,j;
    scanf("%d%d",&n,&m);
    a=vector<string>(2*n);
    rep(i,2*n){
        cin>>a[i];
    }
    id2Point=vector<int>(2*n,0);
    rep(j,m){
        rank2Id=vector<Data>(0);
        rep(i,2*n)
            rank2Id.push_back(Data(id2Point[i],i));
        sort(rank2Id.begin(),rank2Id.end());
        for(i=1;i<=n;i++){
            if(a[rank2Id[2*n-1-2*i+1].id][j]!=a[rank2Id[2*n-1-2*i+2].id][j]){
                if(isWin(a[rank2Id[2*n-1-2*i+1].id][j],a[rank2Id[2*n-1-2*i+2].id][j]))
                    id2Point[rank2Id[2*n-1-2*i+1].id]++;
                else
                    id2Point[rank2Id[2*n-1-2*i+2].id]++;
            }
        }
    }
    rank2Id=vector<Data>(0);
    rep(i,2*n)
        rank2Id.push_back(Data(id2Point[i],i));
    sort(rank2Id.begin(),rank2Id.end());
    rep(i,2*n)
        printf("%d\n",rank2Id[2*n-1-i].id+1);
    return 0;
}