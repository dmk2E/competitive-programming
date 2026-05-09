#include<bits/stdc++.h>
#define rep(i,n)for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

int main(){
    int n,i;
    while(cin>>n,n){
        vector<int> a(n),b(n);
        rep(i,n)
            cin>>a[i];
        rep(i,n)
            cin>>b[i];
        int A,B;
        A=B=0;
        int ans=0,w=-1;
        rep(i,n){
            A+=a[i];
            B+=b[i];
            if(A>B){
               if(w==-1){
                w=0;
               }
               if(w==1){
                w=0;
                ans++;
               }
            }else if(B>A){
                if(w==-1){
                    w=1;
                }
                if(w==0){
                    w=1;
                    ans++;
                }
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}