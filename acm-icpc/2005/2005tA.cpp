/*アルゴリズムと工夫点(Keitai Message/CPU: 0 ms  Memory: 3500 KB  Length: 759 B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
#define KH 9
#define KW 5
#define DEFAULT 0
#define MAX_S 1024
using namespace std;

int n;
char s[MAX_S+1], keitai[KH + 1][KW + 1] = {"\0",".,!? ","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};

int main() {
	int row,temp,cnt,i;
	cin >> n;
	while (n--) {
		//scanf_s("%s",s,MAX_S+1);
		scanf("%s", s);
		row = DEFAULT;
		cnt = 0;
		for (i = 0; s[i] != '\0'; i++) {
			if ((temp = (int)s[i] - (int)'0') == 0) {
				if(keitai[row][cnt]!='\0')
					putchar(keitai[row][cnt]);
				row = DEFAULT;
				cnt = 0;
			}
			else {
				if (row == DEFAULT)
					row = temp;
				else {
					if (keitai[row][cnt + 1] == '\0')
						cnt = 0;
					else
						cnt++;
				}
			}
		}
		cout << endl;
	}
	return 0;
}