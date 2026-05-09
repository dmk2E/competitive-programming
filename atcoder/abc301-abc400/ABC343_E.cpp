/*アルゴリズムと工夫点(7x7x7/CPU: 92 ms  Memory: 3876 KB  Length: 1862 B)
全探索で間に合うことは気づいていたが、共通範囲を求める方法が思いつかなかった。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;

int v1,v2,v3;

int common(int x,int e,int xx,int ee){
    return max(0,min(e,ee)-max(x,xx));
}

int calV2(int a,int b,int c,int aa,int bb,int cc){
    return common(a,a+7,aa,aa+7)*common(b,b+7,bb,bb+7)*common(c,c+7,cc,cc+7);
}

int ccommon(int x,int e,int xx,int ee,int xxx,int eee){
    return max(0,min(e,min(ee,eee))-max(x,max(xx,xxx)));
}

int calV3(int a,int b,int c,int aa,int bb,int cc){
    return ccommon(0,7,a,a+7,aa,aa+7)*ccommon(0,7,b,b+7,bb,bb+7)*ccommon(0,7,c,c+7,cc,cc+7);
}

int main() {
    scanf("%d%d%d",&v1,&v2,&v3);
    int a,b,c,aa,bb,cc,v12,v13,v23,v123;
    for(a=-7;a<=7;a++){
        for(b=-7;b<=7;b++){
            for(c=-7;c<=7;c++){
                for(aa=-7;aa<=7;aa++){
                    for(bb=-7;bb<=7;bb++){
                        for(cc=-7;cc<=7;cc++){
                            //printf("%d %d %d %d %d %d\n",a,b,c,aa,bb,cc);
                            v12=calV2(0,0,0,a,b,c);
                            v13=calV2(0,0,0,aa,bb,cc);
                            v23=calV2(a,b,c,aa,bb,cc);
                            v123=calV3(a,b,c,aa,bb,cc);
                            if(v1!=343*3-2*(v12+v23+v13)+3*v123)
                                continue;
                            if(v2!=v12+v23+v13-3*v123)
                                continue;
                            if(v123==v3){
                                printf("Yes\n%d %d %d %d %d %d %d %d %d\n",0,0,0,a,b,c,aa,bb,cc);
                                //printf("v12:%d v13:%d v23:%d v123:%d\n",v12,v13,v23,v123);
                                return 0;
                            }   
                        }
                    }
                }
            }
        }
    }
    puts("No");
	return 0;
}