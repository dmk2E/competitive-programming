/*アルゴリズムと工夫点(Graph Isomorphism/CPU: 1 ms Memory: 3696 KB  Length: 1021 B)

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
    int i,j,k;
    scanf("%d%d",&n,&m);
    vector<vector<bool> > adjT(n,vector<bool>(n,false)),adjA(n,vector<bool>(n,false));
    rep(i,m){
        scanf("%d%d",&j,&k);
        j--;k--;
        adjT[j][k]=true;
        adjT[k][j]=true;
    }
    rep(i,m){
        scanf("%d%d",&j,&k);
        j--;k--;
        adjA[j][k]=true;
        adjA[k][j]=true;
    }
    string per="";
    rep(i,n)per+=(char)('0'+i);
    auto judge=[&]()->bool{
        int i,j;
        rep(i,n)rep(j,i)if((adjT[i][j]&&(!adjA[per[i]-'0'][per[j]-'0']))||((!adjT[i][j])&&adjA[per[i]-'0'][per[j]-'0']))return false;
        return true;
    };
    do{
        if(judge()){
            puts("Yes");
            return 0;
        }
    }while(next_permutation(per.begin(),per.end()));
    puts("No");
    return 0;
}