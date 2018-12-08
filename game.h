#include<bits\stdc++.h>
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
Pair get(){
	int x=read(),y=read();
	return (Pair){x,y};
}
void out(int x,int y){
	printf("%d %d\n",x,y);
}
void init(){
//	freopen("tmp","r",stdin);
	Player=read();
//	fclose(stdin);
	Filename_in[0]=Player+'0';
	Filename_out[0]=Player+'0';
}
