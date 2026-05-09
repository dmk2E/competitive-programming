/*アルゴリズムと工夫点(Matrix Reducing/CPU: 45 ms Memory: 3872 KB  Length: 1200 B)
行列Aにおいてどの行を残すかの集合hs, どの列を残すかの集合ws, を全探索し，条件を満たす場合が存在するか判定する．
最悪計算量は O(H1*W1*2^(H1)*2^(W1))≒10^8 となるが，適切に枝刈りをすれば間に合う．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int h1,w1,h2,w2;

int popCount(int x){
    int cnt=0;
    while(x>0){
        cnt+=x&1;
        x>>=1;
    }
    return cnt;
}

int main(){
    int i,j;
    scanf("%d%d",&h1,&w1);
    vector<vector<int> > a(h1,vector<int>(w1));
    rep(i,h1)rep(j,w1)scanf("%d",&a[i][j]);
    scanf("%d%d",&h2,&w2);
    vector<vector<int> > b(h2,vector<int>(w2));
    rep(i,h2)rep(j,w2)scanf("%d",&b[i][j]);
    auto judge=[&](int hs,int ws)->bool{
        int ai,aj,i,j;
        ai=aj=0;
        rep(i,h2)rep(j,w2){
            while(!(((hs>>ai)&1)&&((ws>>aj)&1))){
                aj=(aj+1)%w1;
                ai+=(aj==0);
            }
            if(a[ai][aj]!=b[i][j])return false;
            aj=(aj+1)%w1;
            ai+=(aj==0);
        }
        return true;
    };
    i=j=0;
    rep(i,1<<h1)rep(j,1<<w1){
        if(popCount(i)==h2&&popCount(j)==w2&&judge(i,j)){
            // printf("hs:%d ws:%d\n",i,j);
            puts("Yes");
            return 0;
        }
    }
    puts("No");
    return 0;
}