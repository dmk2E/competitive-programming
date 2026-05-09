/*アルゴリズムと工夫点(Made Up/CPU: 38 ms Memory: 5336 KB  Length: 1284 B)
数列Aを、値とその個数で保持しておく。数列Bは(値,数列B上での添え字)で保持し、値の昇順にソートしておく。数列Cも数列Aと同様に値とその個数で保持しておく。
数列Aを0~(Aiの最大値)まで、線型的に訪問し、固定する。個数が1個以上ある場合、その値を数列Bが持っている可能性があるため、二分探索で探索する。同じ値が複数存在する可能性があるため、固定したAiの値と同じ値が続く数列B上の
範囲[s,e)を二分探索してそれぞれ求める。次にB[s,e)の各要素の添え字の値が、数列Cに存在するか判定し、数える。
数列Aにおいて、与えられる整数の種類の最大数はNであり、数列Bの各要素は最大1回しか訪問されないから、最悪計算量は、O(max(Ai)*log2(N)+N)≒10^6 となり、十分高速。
*/
#include<iostream>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 100000
using namespace std;

typedef pair<int,int> p;

int n,a[MAX_N+1]={0},c[MAX_N]={0};//a[i],c[i]:配列a,c上での整数iの個数
p b[MAX_N];

int main(){
    int i,j,left,right,mid;
    long long cnt=0;
    scanf("%d",&n);
    rep(i,n){
        scanf("%d",&j);
        a[j]++;
    }
    rep(i,n){
        scanf("%d",&b[i].first);
        b[i].second=i;
    }
    sort(b,b+n);
    rep(i,n){
        scanf("%d",&j);
        c[j-1]++;
    }
    rep(i,MAX_N+1){
        if(a[i]>0){
            left=0;right=n;
            while(left<right){
                mid=(left+right)/2;
                if(b[mid].first<i)
                    left=mid+1;
                else
                    right=mid;
            }
            j=left;
            left=0;right=n;
            while(left<right){
                mid=(left+right)/2;
                if(b[mid].first<=i)
                    left=mid+1;
                else
                    right=mid;
            }
            //printf("a:%d b[%d,%d)\n",j,left);
            while(j<left){
                cnt+=(long long)a[i]*c[b[j].second];
                j++;
            }
        }
    }
    printf("%lld\n",cnt);
    return 0;
}