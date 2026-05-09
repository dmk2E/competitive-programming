/*アルゴリズムと工夫点(Avoid K Palindrome 2/CPU: 1395 ms Memory: 287172 KB  Length: 1127 B)
順列生成は，next_permutationを使った方が楽．
*/
#include<iostream>
#include<vector>
#include<set>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_S 10
using namespace std;
typedef long long ll;

int n,k;
string s;
bool check[MAX_S]={0};
set<string> cnt,same;

int count(string& sta){
    int i,j,cnt=0;
    if(sta.size()==n){
        //string sub;
        //cout<<sta<<endl;
        if(same.find(sta)!=same.end())
            return 0;
        same.insert(sta);
        //cout<<sta<<endl;
        rep(i,n-k+1){
            //sub=sta.substr(i,k);
            rep(j,k)
                if(sta[i+j]!=sta[i+k-1-j])
                    break;
            if(j==k)break;
        }
        return i<n-k+1;
    }
    for(i=0;i<n;i++){
        if(check[i]==false){
            check[i]=true;
            sta+=s.substr(i,1);
            //cout<<sta<<endl;
            cnt+=count(sta);
            sta.pop_back();
            check[i]=false;
        }
    }
    return cnt;
}

int main(){
    int i,j;
    scanf("%d%d",&n,&k);
    cin>>s;
    string sta="";
    i=count(sta);
    printf("%d\n",(int)same.size()-i);
    return 0;
}