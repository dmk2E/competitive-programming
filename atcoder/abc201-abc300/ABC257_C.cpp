/*アルゴリズムと工夫点(Robot Takahashi/CPU: 116 ms Memory: 9248 KB  Length: 1642 B)

*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef struct CordinatedCompression{
    bool initiated;
    vector<int> xs;

    CordinatedCompression(){
        xs=vector<int>(0);
        initiated=false;
    }

    void init(){
        initiated=true;
        sort(xs.begin(),xs.end());
        xs.erase(unique(xs.begin(),xs.end()),xs.end());
    }

    void add(int x){
        initiated=false;
        xs.push_back(x);
    }

    int operator()(int k){
        if(!initiated)init();
        return lower_bound(xs.begin(),xs.end(),k)-xs.begin();
    }

    int operator[](int id){
        if(!initiated)init();
        return xs[id];
    }

    int size(){
        return xs.size();
    }
}CC;

int n;
string s;

int main(){
    int i,j,ans=0;
    scanf("%d",&n);
    cin>>s;
    vector<int> childs,adults;
    CC xs;
    xs.add(0);
    rep(i,n){
        scanf("%d",&j);
        if(s[i]=='0')
            childs.push_back(j);
        else
            adults.push_back(j);
        xs.add(j-1);
        xs.add(j);
        xs.add(j+1);
    }
    sort(childs.begin(),childs.end());
    sort(adults.begin(),adults.end());
    auto cal=[&](int x)->int{
        int ans=0;
        ans+=lower_bound(childs.begin(),childs.end(),x)-childs.begin();
        ans+=adults.end()-lower_bound(adults.begin(),adults.end(),x);
        return ans;
    };
    rep(i,xs.size())ans=max(ans,cal(xs[i]));
    printf("%d\n",ans);
    return 0;
}