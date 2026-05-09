/*アルゴリズムと工夫点(Gap Existence/CPU: 285 ms  Memory: 29120 KB  Length: 374 B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;

int n,x;
map<long long,bool> exist;

int main() {
	int i;
	scanf("%d%d",&n,&x);
	vector<int> a(n);
	rep(i,n){
		scanf("%d",&a[i]);
		exist[(long long)a[i]]=true;
	}
	rep(i,n){
		if(exist[(long long)x+a[i]])
			break;
	}
	printf("%s\n",i==n?"No":"Yes");
	return 0;
}