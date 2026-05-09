#include<bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
using namespace std;

int n;

int res(int row,int level,vector<string>& str){
	//printf("res(%d,%d):start\n",row,level);
	if(row==0&&level==0&&(int)'0'<=(int)str[row][level]&&(int)str[row][level]<=(int)'9')
		return (int)str[row][level]-(int)'0';
	int i,sum;
	if(str[row][level]=='+'){
		sum=0;
		for(i=row+1;i<n;i++){
			if(str[i].size()<=level+1)break;
			if(level+1<str[i].size()&&str[i][level+1]!='.'){
				if((int)'0'<=(int)str[i][level+1]&&(int)str[i][level+1]<=(int)'9'){
					sum+=(int)str[i][level+1]-(int)'0';
				}else
					sum+=res(i,level+1,str);
				str[i][level+1]='.';
			}
			//printf("i:%d level:%d\n",str[i].size(),level);
		}
	}else if(str[row][level]=='*'){
		sum=1;
		for(i=row+1;i<n;i++){
			if(str[i].size()<=level+1)break;
			if(level+1<str[i].size()&&str[i][level+1]!='.'){
				if((int)'0'<=(int)str[i][level+1]&&(int)str[i][level+1]<=(int)'9')
					sum*=(int)str[i][level+1]-(int)'0';
				else
					sum*=res(i,level+1,str);
				str[i][level+1]='.';
			}
		}
	}else{
		printf("Error!\n");
		return -1;
	}
	//printf("res(%d,%d)=%d\n",row,level,sum);
	return sum;
}

int main(){
	int i;
	//rep(i,9)j*=9;printf("%lld\n",j);return 0;
	while(1){
		vector<string> str;
		scanf("%d",&n);
		if(n==0)
			break;
		rep(i,n){
			str.push_back("");
			cin>>str[i];
		}
		//rep(i,n)cout<<str[i]<<endl;
		printf("%d\n",res(0,0,str));
	}
	return 0;
}