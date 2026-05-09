/*アルゴリズムと工夫点(Not Too Bright/CPU: 1 ms Memory: 3908 KB  Length: 255 B)
問題文の条件をしっかり読んで、コーナーケースに気を付ける。
<i>答えの上界を考えて、上界が実現できる構成を考える。
<ii>小さめのケースで実験して、法則性を導く。
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;

int h,w;

int main(){
    scanf("%d%d",&h,&w);
    if(h==1||w==1)
        printf("%d\n",h*w);
    else
        printf("%d\n",((h+1)/2)*((w+1)/2));
    return 0;
}