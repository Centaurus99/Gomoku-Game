#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<ctime>
using namespace std;
const int N=15;
int data[N][N],type;
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
inline bool check(int a,int l,int r){
	return a<l||a>r;
}
char tmp[5];
void out(){
	freopen("tmp","w",stdout);
	printf("%s",tmp);
	fclose(stdout);
}
struct Pair{
	int x,y;
};
Pair get(int wh){
	Pair ans;
	ans.x=N,ans.y=N;
	if (wh){
		l1:
		freopen("1.out","r",stdin);
		if (scanf("%d%d",&ans.x,&ans.y)==EOF){
			fclose(stdin);
			stop(500);
			goto l1;
		}
		fclose(stdin);
		freopen("1.out","w",stdout);
		fclose(stdout);
	}
	else{
		l2:
		freopen("0.out","r",stdin);
		if (scanf("%d%d",&ans.x,&ans.y)==EOF){
			fclose(stdin);
			stop(500);
			goto l2;
		}
		fclose(stdin);
		freopen("0.out","w",stdout);
		fclose(stdout);
	}
	return ans;
}
void out(int wh,int x,int y){
	if (wh){
		freopen("1.in","w",stdout);
		printf("%d %d",x,y);
		fclose(stdout);
	}
	else{
		freopen("0.in","w",stdout);
		printf("%d %d",x,y);
		fclose(stdout);
	}
}
bool check_five(int x,int y,int c){
	int lx,rx,ly,ry;
	lx=rx=x;
	while (lx>0&&data[lx-1][y]==c) --lx;
	while (rx<N-1&&data[rx+1][y]==c) ++rx;
	if (rx-lx>=4) return 1;
	ly=ry=y;
	while (ly>0&&data[x][ly-1]==c) --ly;
	while (ry<N-1&&data[x][ry+1]==c) ++ry;
	if (ry-ly>=4) return 1;
	lx=rx=x,ly=ry=y;
	while (lx>0&&ly>0&&data[lx-1][ly-1]==c) --lx,--ly;
	while (rx<N-1&&ry<N-1&&data[rx+1][ry+1]==c) ++rx,++ry;
	if (rx-lx>=4) return 1;
	lx=rx=x,ly=ry=y;
	while (lx>0&&ry<N-1&&data[lx-1][ry+1]==c) --lx,++ry;
	while (rx<N-1&&ly>0&&data[rx+1][ly-1]==c) ++rx,--ly;
	if (rx-lx>=4) return 1;
	return 0;
}
void print(){
		cerr<<"  ";
		for (int j=0;j<N;++j){
			if (j<10) cerr<<' ';
			cerr<<j<<' ';
		}
		cerr<<endl;
		for (int i=0;i<N;++i){
		cerr<<i<<' ';
		if (i<10) cerr<<' ';
		for (int j=0;j<N;++j){
			if(data[i][j]==0)cerr<<'+';
			if(data[i][j]==1)cerr<<'X';
			if(data[i][j]==-1)cerr<<'O';
			cerr<<"  ";
		}
		cerr<<endl;
	}
	cerr<<endl;
}
int main(){
	freopen("0.in","w",stdout);
	fclose(stdout);
	freopen("1.in","w",stdout);
	fclose(stdout);
	freopen("0.out","w",stdout);
	fclose(stdout);
	freopen("1.out","w",stdout);
	fclose(stdout);
	freopen("tmp","w",stdout);
	fclose(stdout);
	start1:
	cerr<<"Player1 is ?\n0->while 1->black ";
	scanf("%d",&type);
	if (check(type,0,1)) goto start1;
	if (type){
		tmp[0]='1';
		out();
		system("start player1.exe");
		stop(500);
		tmp[0]='0';
		out();
		system("start player2.exe");
	}
	else{
		tmp[0]='0';
		out();
		system("start player1.exe");
		tmp[0]='1';
		out();
		system("start player2.exe");
	}
	int now=1;
	bool gfg=1,win;
	memset(data,0,sizeof(data));
	while (gfg){
		Pair t=get(now);
		cerr<<"Player"<<((type==now)?'1':'2')<<':'<<t.x<<' '<<t.y<<endl;
		if (check(t.x,0,N-1)||check(t.y,0,N-1)){
			if (t.x==N&&t.y==N)
			cerr<<"Player"<<((type==now)?'1':'2')<<" writes down\"GG\""<<endl;
			else
			cerr<<"Player"<<((type==now)?'1':'2')<<" lose"<<endl;
			win=now^1;
			break;
		}
		if (data[t.x][t.y]){
			cerr<<"It is now empty!"<<endl;
			win=now^1;
			break;
		}
		data[t.x][t.y]=now?1:-1;
		print();
		if (check_five(t.x,t.y,data[t.x][t.y])){
			win=now;
			break;
		}
		now^=1;
		out(now,t.x,t.y);
	}
	cerr<<"The winner is Player"<<((type==win)?'1':'2')<<endl;
	return 0;
}
