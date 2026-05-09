/*アルゴリズムと工夫点(Move Segment/CPU: 32 ms Memory: 8424 KB  Length: 1245 B)
言われたことを実装するだけだが，バグを埋め込みやすい問題．
自分は，(値,その数)という形にランレングス圧縮して，その上で問題を考えた．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

int n,k;
string s;

int main(){
    int i,j,kk,ii;
    scanf("%d%d",&n,&k);
    cin>>s;
    vector<P> rnl;
    P tmp;
    i=0;
    while(i<n){
        tmp.first=s[i]-'0';
        tmp.second=0;
        while(i<n&&s[i]-'0'==tmp.first){
            tmp.second++;
            i++;
        }
        rnl.push_back(tmp);
    }
    //rep(i,rnl.size())printf("(%d,%d)",rnl[i].first,rnl[i].second);
    j=0;
    bool flag=true;
    rep(i,rnl.size()){
        if(rnl[i].first==1)j++;
        if(flag&&j==k-1){kk=i;flag=false;}
        else if(j==k)break;
    }
    // printf("kk:%d\n",kk);
    // printf("ii:%d\n",i);
    ii=i;
    rep(i,rnl.size()){
        if(i==kk+1){
            while(rnl[ii].second--){
                printf("%d",rnl[ii].first);
            }
            while(rnl[i].second--){
                printf("%d",rnl[i].first);
            }
        }else if(i!=ii){
            while(rnl[i].second--){
                printf("%d",rnl[i].first);
            }
        }
    }
    puts("");
    return 0;
}