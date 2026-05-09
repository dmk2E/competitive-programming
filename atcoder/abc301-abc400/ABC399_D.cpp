/*アルゴリズムと工夫点(Switch Seats/CPU: 178 ms Memory: 16056 KB  Length: 1732 B)
(a,b)が条件を満たすには，aの添え字2個とbの添え字2個について，昇順に整列した整数列Xとすると，"X3-X2=1 & X1-X0=1"を満たせばよい．
bの候補としては，(aの添え字)±1の範囲で十分．
従って，1テストケース当たりの最悪計算量は O(N*log2(N))
※4WAもしてしまった...
※↑の原因は，continue文によって十分なbの候補を列挙できていなかったこと...悔しすぎる.....
*/
#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int t,n;

int main(){
    int i,j,k;
    ll ans;
    scanf("%d",&t);
    while(t--){
        ans=0;
        scanf("%d",&n);
        vector<int> a(2*n);
        vector<vector<int> > x_to_id(n);
        vector<bool> flag(n,false);
        rep(i,2*n){
            scanf("%d",&a[i]);
            a[i]--;
            x_to_id[a[i]].push_back(i);
        }
        rep(i,n)if(abs(x_to_id[i][0]-x_to_id[i][1])==1)flag[i]=true;
        rep(i,n){
            if(flag[i])continue;
            set<int> v;
            /* WA Ver : 添え字-1の方が範囲外の時に，添え字+1の方を列挙できずに処理を終えてしまうという，痛恨のミス
            if(0<=x_to_id[i][j]-1&&x_to_id[i][j]-1<2*n){
                if(flag[a[x_to_id[i][j]-1]])continue;
                v.insert(a[x_to_id[i][j]-1]);
            }
            if(0<=x_to_id[i][j]+1&&x_to_id[i][j]+1<2*n){
                if(flag[a[x_to_id[i][j]+1]])continue;
                v.insert(a[x_to_id[i][j]+1]);
            }
            */
            //AC Ver
            rep(j,2){
                for(k=-1;k<=1;k+=2){
                    if(0<=x_to_id[i][j]+k&&x_to_id[i][j]+k<2*n){
                        v.insert(a[x_to_id[i][j]+k]);
                    }
                }
            }
            //AC Ver

            //if(v.find(i)!=v.end())v.erase(i);
            for(int x:v){
                if(i>=x||flag[x])continue;
                // printf("%d %d\n",i+1,x+1);
                vector<int> tmp;
                tmp.push_back(x_to_id[x][0]);
                tmp.push_back(x_to_id[x][1]);
                tmp.push_back(x_to_id[i][0]);
                tmp.push_back(x_to_id[i][1]);
                sort(tmp.begin(),tmp.end());
                ans+=(tmp[1]-tmp[0]==1)&&(tmp[3]-tmp[2]==1);
                //ans+=(((abs(x_to_id[x][0]-x_to_id[i][0])==1)&&(abs(x_to_id[x][1]-x_to_id[i][1])==1))||((abs(x_to_id[x][0]-x_to_id[i][1])==1)&&(abs(x_to_id[x][1]-x_to_id[i][0])==1)));
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}