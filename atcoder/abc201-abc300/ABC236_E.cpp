/*アルゴリズムと工夫点(Average and Median/CPU: 148 ms Memory: 4696 KB  Length: 1762 B)
平均値や中央値を最大化する問題は，二分探索によって解を求めるのが定石．
「中央値(ceil(x/2)番目)をX以上にできるか」という問題は，「(X未満の値の数)<=(X以上の値の数)-1を満たすか」と言い換えることができる．
この条件を満たすかで，「0」か「1」に配列Aを書き換える．
「平均値をX以上にできるか」という問題は，式変形により「Σ(ai-X)>=0か」という問題に書き換えられる．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_A (int)(1e9)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

template<typename T>
void chMax(T& a,const T b){a=max(a,b);}

int n;

double solveAve(vector<int>& a){
    int i,cnt=100;
    double left,right,mid;
    const double NIL=-1e18;
    vector<double> tmp(n);
    auto judge=[&](vector<double>& a)->bool{
        int i,j;
        vector<double> last(2,NIL);
        last[1]=0;
        rep(i,n){
            vector<double> now(2,NIL);
            rep(j,2){
                chMax(now[1],last[j]+a[i]);
                if(j)chMax(now[0],last[j]);
            }
            swap(last,now);
        }
        return max(last[0],last[1])>=0;
    };
    left=0,right=(double)MAX_A*n;
    while(cnt--){
        mid=(left+right)/2;
        rep(i,n)tmp[i]=a[i]-mid;
        if(judge(tmp))left=mid;
        else right=mid;
    }
    return left;
}

int solveMed(vector<int>& a){
    int left,right,mid,i;
    vector<bool> tmp(n);
    left=0,right=MAX_A+1;
    auto judge=[&](vector<bool>& a)->bool{
        int i,one=0,zero=0,now=0;
        rep(i,n)one+=a[i];
        rep(i,n){
            if(a[i]){
                zero+=now/2;
                now=0;
            }else now++;
        }
        zero+=now/2;
        return zero<=one-1;
    };
    while(left<right){
        mid=(left+right)/2;
        rep(i,n)tmp[i]=(a[i]>=mid);
        if(judge(tmp))left=mid+1;
        else right=mid;
    }
    return left-1;
}

int main(){
    int i,j;
    scanf("%d",&n);
    vector<int> a(n);
    rep(i,n)scanf("%d",&a[i]);
    printf("%.4f\n%d\n",solveAve(a),solveMed(a));
    return 0;
}