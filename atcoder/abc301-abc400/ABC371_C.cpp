/*アルゴリズムと工夫点(Make Isomorphic/CPU: 10 ms Memory: 3912 KB  Length: 1547 B)
効率的な同型判定アルゴリズムを考えようとした結果，上手くいかず，全探索の仕方も間違えてしまった...
「判定条件の部分が全探索できるかどうか」という視点を新たに持つようにしていきたい．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;

int main(){
    int i,j,l,r,tmp,ans=(int)(1e8);
    string now;
    scanf("%d%d",&n,&m);
    rep(i,n)now+=(char)((int)'0'+i);
    vector<vector<bool> > adjG(n,vector<bool>(n,false)),adjH(n,vector<bool>(n,false));
    vector<vector<int> > a(n,vector<int>(n,0));
    while(m--){
        scanf("%d%d",&i,&j);
        i--;j--;
        adjG[i][j]=adjG[j][i]=true;
    }
    scanf("%d",&m);
    while(m--){
        scanf("%d%d",&i,&j);
        i--;j--;
        adjH[i][j]=adjH[j][i]=true;
    }
    rep(i,n-1)rep(j,n-1-i)scanf("%d",&a[i][j]);
    do{
        tmp=0;
        rep(i,n)rep(j,i){
            if(adjG[i][j]){
                if(adjH[(int)now[i]-(int)'0'][(int)now[j]-(int)'0']==false){
                    l=min((int)now[i]-(int)'0',(int)now[j]-(int)'0');
                    r=max((int)now[i]-(int)'0',(int)now[j]-(int)'0');
                    tmp+=a[l][r-l-1];
                }
            }else{
                if(adjH[(int)now[i]-(int)'0'][(int)now[j]-(int)'0']){
                    l=min((int)now[i]-(int)'0',(int)now[j]-(int)'0');
                    r=max((int)now[i]-(int)'0',(int)now[j]-(int)'0');
                    tmp+=a[l][r-l-1];
                }
            }
        }
        if(tmp<ans)ans=tmp;
    }while(next_permutation(now.begin(),now.end()));
    printf("%d\n",ans);
    return 0;
}