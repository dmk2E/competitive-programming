/*アルゴリズムと工夫点(Pigeon Swap/CPU: 83 ms Memory: 15192 KB  Length: 856 B)
手順2が厄介であるため，"巣"と"鳩"以外に手順2用に"集合"という概念を追加する．
・鳩id->集合id
・集合id->巣id
・巣id->集合id
これら3つの情報を管理することで，O(N+Q)<10^7 となり高速．
※入れ替える操作を高速に行うためには，参照入れ替えをする必要があり，何かしら"集合"に関する概念を介する必要がある．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,q;

int main(){
    int i,j;
    scanf("%d%d",&n,&q);
    vector<int> bird2Set(n),set2Nest(n),nest2Set(n);
    rep(i,n)bird2Set[i]=set2Nest[i]=nest2Set[i]=i;
    while(q--){
        scanf("%d",&i);
        if(i==1){
            scanf("%d%d",&i,&j);
            i--;j--;
            bird2Set[i]=nest2Set[j];
        }else if(i==2){
            scanf("%d%d",&i,&j);
            i--;j--;
            swap(nest2Set[i],nest2Set[j]);
            set2Nest[nest2Set[i]]=i;
            set2Nest[nest2Set[j]]=j;
        }else{
            scanf("%d",&i);
            i--;
            printf("%d\n",set2Nest[bird2Set[i]]+1);
        }
    }
    return 0;
}