#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<ctime>
using namespace std;
inline int read(){
	int x=0,f=1;char ch;
	do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
	do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
	return x*f;
}
void stop(int x){
	int t=clock();
	while (clock()-t<=x);
}
int main(){
	while (1){
		l1:
		int x,y;
		while (scanf("%d%d",&x,&y)==EOF){
			stop(500);
			goto l1;
		}
		freopen("tmp","w",stdout);
		printf("%d %d",x,y);
		fclose(stdout);
	}
	return 0;
}
