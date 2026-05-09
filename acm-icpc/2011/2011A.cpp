/*アルゴリズムと工夫点(チェビシェフの定理/CPU: 0 ms  Memory: 3956 KB  Length: 817 B)
最初にエラトステネスの篩で必要な素数を全列挙し、配列prime昇順に保持しておく。この前処理の最悪計算量はO(MAX_N*log2(log2(MAX_N)))<10^7 となり、高速。
各入力nに対して、n以下で最小の素数が格納されているprime上の添え字s,2*nより大きい素数で最小の素数が格納されているprime上の添え字eのそれぞれを二分探索で求め、「e-s」を出力すればよい。
一つのデータセットに対するこの処理の最悪計算量は、O(log2(n))<10^2 となり、十分高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 123456
using namespace std;

int n;
bool isPrime[2*MAX_N+1];
vector<int> prime;

void init(){
	int i,j;
	rep(i,2*MAX_N+1)
		isPrime[i]=true;
	isPrime[0]=isPrime[1]=false;
	for(i=2;i<2*MAX_N+1;i++){
		if(isPrime[i]){
			prime.push_back(i);
			j=2*i;
			while(j<2*MAX_N+1){
				isPrime[j]=false;
				j+=i;
			}
		}
	}
}

int main() {
	int left,right,mid,s;
	init();
	while(1){
		scanf("%d",&n);
		if(!n)
			break;
		left=0;right=prime.size();
		while(left<right){
			mid=(left+right)/2;
			if(prime[mid]<=n)
				left=mid+1;
			else
				right=mid;
		}
		s=left;
		left=0;right=prime.size();
		while(left<right){
			mid=(left+right)/2;
			if(prime[mid]<=2*n)
				left=mid+1;
			else
				right=mid;
		}
		printf("%d\n",left-s);
	}
	return 0;
}