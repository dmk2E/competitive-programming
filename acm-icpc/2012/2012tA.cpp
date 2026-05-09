/*アルゴリズムと工夫点(君のプライバシーを守れ!/CPU: 0 ms Memory: 3616 KB  Length: 1016 B)
番号の最大値が100であるため，個人の番号をキーとし，流出したか否かをbool値の配列lで持つようにする．その後，入力されたデータを巡回して，「流出した全ての個人情報を保持している人は一人か」を判定し，真ならその人の番号を，
偽なら-1を出力する．「その個人情報は流出したもの」か否かの判定は配列lを用いることでO(1)で判定可能．したがって，全体の計算量はO(N^2)<10^5 となり十分高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 100
#define NIL -1
using namespace std;

int n,m,k;

int main(){
    int i,j,cnt,ans;
    while(1){
        scanf("%d",&n);
        if(!n)
            break;
        vector<vector<int> > info(n);
        rep(i,n){
            scanf("%d",&m);
            while(m--){
                scanf("%d",&j);
                info[i].push_back(j-1);
            }
        }
        vector<bool> l(n,false);
        scanf("%d",&k);
        rep(i,k){
            scanf("%d",&j);
            l[j-1]=true;
        }
        ans=NIL;
        rep(i,n){
            cnt=0;
            rep(j,info[i].size()){
                if(l[info[i][j]])
                    cnt++;
            }
            if(cnt==k){
                if(ans==NIL)
                    ans=i;
                else{
                    ans=NIL;
                    break;
                }
            }
        }
        printf("%d\n",ans==NIL?ans:ans+1);
    }
    return 0;
}