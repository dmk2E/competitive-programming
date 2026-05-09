/*アルゴリズムと工夫点(11/22 Subsequence/CPU: 320 ms Memory: 4364 KB  Length: 1473 B)
「長さX以上の条件を満たす部分文字列を取れるか」は単調性があるため，二分探索ができる．
長さX以上にできるかは，貪欲に前からX/2個の'1',それ以降で'/'，それ以降でX/2個の'2'が取れるか貪欲法で判定可能．
判定の計算量削減のため，入力される文字の種類の少なさを活かして，文字毎に登場する添え字を記録しておく．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,q;
string s;

int c2Id(char c){
    switch(c){
        case '1':
            return 0;
        case '/':
            return 1;
        default :
            return 2;
    }
}

int main(){
    int i,j,left,right,mid;
    scanf("%d%d",&n,&q);
    cin>>s;
    vector<vector<int> > ids(3);
    rep(i,n)ids[c2Id(s[i])].push_back(i);
    // rep(i,3){rep(j,ids[i].size())printf("%d ",ids[i][j]);puts("");}
    const int INF=2*n;
    auto getNext=[&](int id,int now,int len)->int{
        if(len==0)return now;
        auto& nis=ids[id];
        int i=lower_bound(nis.begin(),nis.end(),now)-nis.begin();
        i+=len-1;
        if(i<nis.size())return nis[i]+1;
        return INF;
    };
    auto judge=[&](int l,int r,int len)->bool{
        l=getNext(0,l,len);
        // printf("l:%d\n",l);
        l=getNext(1,l,1);
        // printf("l:%d\n",l);
        l=getNext(2,l,len);
        // printf("l:%d\n",l);
        return l<=r;
    };
    while(q--){
        scanf("%d%d",&i,&j);
        i--;
        left=0,right=n;
        while(left<right){
            mid=(left+right)/2;
            // printf("mid:%d\n",mid);
            if(judge(i,j,mid))left=mid+1;
            else right=mid;
        }
        printf("%d\n",max(2*(left-1)+1,0));
    }
    return 0;
}