/*アルゴリズムと工夫点(Logical Filling/CPU: 5 ms Memory: 4076 KB  Length: 1667 B)
S上の?を'.'または'o'に決め打って，それが可能か判定していく．
'o'の両隣は'.'に確定するため，実際に考えなければならないSは，'?'の連続した成分が独立に存在したものとなる．
最悪計算量は O(N)≒10^6 となり十分高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,k;
string s;

int main(){
    int i,j,ii,sum_q=0;
    scanf("%d%d",&n,&k);
    cin>>s;
    rep(i,n){
        if(s[i]=='o'){
            if(i-1>=0)s[i-1]='.';
            if(i+1<n)s[i+1]='.';
            k--;
        }
    }
    vector<int> st_q;
    i=0;
    while(i<n){
        if(s[i]=='?'){
            j=0;
            while(i<n&&s[i]=='?'){
                j++;
                i++;
            }
            sum_q+=(j+1)/2;
            st_q.push_back(j);
        }
        i++;
    }
    //printf("st_q:");rep(i,st_q.size())printf("%d ",st_q[i]);puts("");printf("sum_q:%d\n",sum_q);
    string ans=s;
    auto judgeO=[&](int id_s,int id_st)->bool{
        if(k==0)return false;
        //printf("judgeO(%d,%d)\n",id_s,id_st);
        int tmp=sum_q-(st_q[id_st]+1)/2;
        tmp+=(id_s)/2+(st_q[id_st]-id_s-1)/2+1;
        return 0<=k&&k<=tmp;
    };
    auto judgeDot=[&](int id_s,int id_st)->bool{
        //printf("judgeDot(%d,%d)\n",id_s,id_st);
        int tmp=sum_q-(st_q[id_st]+1)/2;
        tmp+=(id_s+1)/2+(st_q[id_st]-id_s)/2;
        return 0<=k&&k<=tmp;
    };
    j=-1;
    rep(i,n){
        if(s[i]=='?'){
            if(i-1<0||s[i-1]!='?')ii=0,j++;
            bool flag_o=judgeO(ii,j),flag_dot=judgeDot(ii,j);
            if(flag_o&&flag_dot)ans[i]='?';
            else if(flag_o)ans[i]='o';
            else if(flag_dot)ans[i]='.';
            ii++;
        }
    }
    cout<<ans<<endl;
    return 0;
}