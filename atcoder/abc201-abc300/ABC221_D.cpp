/*アルゴリズムと工夫点(Online games/CPU: 191 ms Memory: 15056 KB  Length: 2369 B)
座標圧縮とimos法の同時併用で解ける．良問．最悪計算量はO(N*log2(N))<10^7 より十分高速．
※初見4完!
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

typedef class CoordinateCompression{
    int MIN_X,MAX_X;
    bool initialized;
    vector<int> xs;
public:
    CoordinateCompression(int mmin=0,int mmax=(int)(1e9)+1):MIN_X(mmin),MAX_X(mmax),initialized(false){}
    
    void add(int x){
        if(MIN_X<=x-1&&x-1<=MAX_X)
            xs.push_back(x-1);
        if(MIN_X<=x&&x<=MAX_X)
            xs.push_back(x);
        if(MIN_X<=x+1&&x+1<=MAX_X)
            xs.push_back(x+1);
        initialized=false;
    }

    void init(){
        sort(xs.begin(),xs.end());
        xs.erase(unique(xs.begin(),xs.end()),xs.end());
        initialized=true;
    }

    int x2Id(int x){
        if(!initialized)init();
        int left=0,right=xs.size(),mid;
        while(left<right){
            mid=(left+right)/2;
            if(xs[mid]<x)
                left=mid+1;
            else
                right=mid;
        }
        return left;
    }

    int id2X(int id){
        if(!initialized)init();
        return xs[id];
    }

    int operator()(int x){
        return x2Id(x);
    }

    int operator[](int x){
        return id2X(x);
    }

    int size(){
        if(!initialized)init();
        return xs.size();
    }
}CC;

typedef pair<int,int> p;

int n,a,b;
vector<p> ipt;

int main(){
    int i,j,k;
    bool flag=false;
    scanf("%d",&n);
    ipt=vector<p>(n);
    CC xs(0,(int)(2e9)+3);
    rep(i,n){
        scanf("%d%d",&ipt[i].first,&ipt[i].second);
        xs.add(ipt[i].first);
        xs.add(ipt[i].second+=ipt[i].first);
    }
    vector<int> imos(xs.size(),0),count(n+1,0);
    rep(i,ipt.size()){
        imos[xs(ipt[i].first)]++;
        imos[xs(ipt[i].second)]--;
    }
    //rep(i,imos.size())printf("%d ",imos[i]);puts("");
    rep(i,imos.size()-1)
        imos[i+1]+=imos[i];
    rep(i,imos.size()){
        if(imos[i]>0){
            k=imos[i];
            j=i;
            while(k==imos[j]){
                j++;
            }
            count[k]+=xs[j]-xs[i];
            i=j-1;
        }
    }
    //rep(i,imos.size())printf("%d ",imos[i]);puts("");
    rep(i,n-1)
        printf("%d ",count[i+1]);
    printf("%d\n",count[i+1]);
    return 0;
}