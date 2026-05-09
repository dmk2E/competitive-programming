/*アルゴリズムと工夫点(Dango/CPU: 4 ms  Memory: 4012 KB  Length: 412 B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define NIL 0
using namespace std;

int n;
string s;

int main() {
	int i,prev,max=NIL;
	scanf("%d",&n);
	cin>>s;
	i=0;
	while(i<n&&s[i]!='-')
		i++;
	if(i<n&&i>0)
		max=i;
	while(i<n){
		prev=i;
		i++;
		while(i<n&&s[i]!='-')
			i++;
		if(max<i-prev-1)
			max=i-prev-1;
	}
	printf("%d\n",max==NIL?-1:max);
	return 0;
}