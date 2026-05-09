/*アルゴリズムと工夫点(Treasure Chest/CPU:  ms  Memory:  KB  Length:  B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define NIL -1
using namespace std;

int n;
string s;

int main() {
	int i,f,ss,c;
	scanf("%d",&n);
	cin>>s;
	f=ss=c=NIL;
	rep(i,n){
		if(s[i]=='|'){
			if(f==NIL)
				f=i;
			else
				ss=i;
		}else if(s[i]=='*')
			c=i;
	}
	printf("%s\n",f<c&&c<ss?"in":"out");
	return 0;
}