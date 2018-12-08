#include<bits\stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char ch;
	do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
	do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
	return x*f;
}
int Player;//0->white 1->black
char Filename_in[10]="x.in",Filename_out[10]="x.out";
struct Pair{
	int x,y;
};
void stop(int x){
	int t=clock();
	while (clock()-t<=x);
}
Pair get(){
	int x=0,y=0;
	llt:
	freopen(Filename_in,"r",stdin);
	if (scanf("%d%d",&x,&y)==EOF){
		fclose(stdin);
		stop(500);
		goto llt;
	}
	fclose(stdin);
	freopen(Filename_in,"w",stdout);
	fclose(stdout);
	return (Pair){x,y};
}
void out(int x,int y){
	freopen(Filename_out,"w",stdout);
	printf("%d %d\n",x,y);
	fclose(stdout);
}
void init(){
	freopen("tmp","r",stdin);
	Player=read();
	cerr<<Player<<endl;
	fclose(stdin);
	freopen("tmp","w",stdout);
	fclose(stdout);
	Filename_in[0]=Player+'0';
	Filename_out[0]=Player+'0';
}
