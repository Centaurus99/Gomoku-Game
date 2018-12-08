#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include"game.h"
#define ll long long
using namespace std;
const int N=15,MOD=5;
const int MX_deep=5,SZ=2;
const ll MX=1e18,INF=1e16,INF2=1e15,Alpha=5000,Beta=7,T=10;
//Alpha->向空地靠拢系数 （越大越强）
//Beta->点对空地程度改变能力 （越小越强） 
//SZ->点对待选空间扩展能力 （越大越强） 
//T->随机选取点数 
ll val[N]={0,1e2,1e4,1e6,1e8,1e10,1e12,1e14,1e14,1e14,1e14,1e14,1e14,1e14};
ll val2[N]={1,1e3,1e5,1e7,1e9,1e11,1e13,1e15,1e15,1e15,1e15,1e15,1e15,1e15};
ll Base[N][N]={
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
{0,1,2,2,2,2,2,2,2,2,2,2,2,1,0},
{0,1,2,3,3,3,3,3,3,3,3,3,2,1,0},
{0,1,2,3,4,4,4,4,4,4,4,3,2,1,0},
{0,1,2,3,4,5,5,5,5,5,4,3,2,1,0},
{0,1,2,3,4,5,6,6,6,5,4,3,2,1,0},
{0,1,2,3,4,5,6,7,6,5,4,3,2,1,0},
{0,1,2,3,4,5,6,6,6,5,4,3,2,1,0},
{0,1,2,3,4,5,5,5,5,5,4,3,2,1,0},
{0,1,2,3,4,4,4,4,4,4,4,3,2,1,0},
{0,1,2,3,3,3,3,3,3,3,3,3,2,1,0},
{0,1,2,2,2,2,2,2,2,2,2,2,2,1,0},
{0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
struct node{
	int data[N][N];
	bool can[N][N];
	ll base[N][N];
	node(){
		memcpy(base,Base,sizeof(base));
	}
	void cl(){
		memset(data,0,sizeof(data));
		memset(can,0,sizeof(can));
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
	void update_base(int x,int y){
		for (int i=0;i<N;++i){
			for (int j=0;j<N;++j)
			base[i][j]=min(base[i][j],(ll)abs(i-x)+(ll)abs(j-y)+Beta);
		}
		for (int i=max(0,x-SZ);i<=min(N-1,x+SZ);++i){
			for (int j=max(0,y-SZ);j<=min(N-1,y+SZ);++j) can[i][j]=1;
		}
	}
};
//1->mine -1->enemy 0>empty
ll calc_p(node*t,int x,int y,int type,int wh){
	int lx,rx,ly,ry,emp,cnt,lx2,rx2,ly2,ry2,tlx,trx,tly,ttry;
	ll ans=0;
	//横 
	ly=ry=tly=ttry=y;
	emp=0;
	cnt=0;
	while (ly>0&&(*t).data[x][ly-1]==type) --ly;
	while (tly>0&&((*t).data[x][tly-1]==type||(*t).data[x][tly-1]==0)) --tly;
	ly2=ly;
	if (ly>0&&(*t).data[x][ly-1]==0){
		++emp;
		if (type==wh){
			while (ly>1&&(*t).data[x][ly-2]==type) --ly,++cnt;
			ans-=val[cnt];
		}
	}
	while (ry<N-1&&(*t).data[x][ry+1]==type) ++ry;
	while (ttry<N-1&&((*t).data[x][ttry+1]==type||(*t).data[x][ttry+1]==0)) ++ttry;
	if (ttry-tly>=4){
		ry2=ry;
		if (ry<N-1&&(*t).data[x][ry+1]==0){
			++emp;
			if (type==wh){
				while (ry<N-0&&(*t).data[x][ry+2]==type) ++ry,++cnt;
				ans-=val[cnt];
			}
		}
		if (ry2-ly2+1+(type==wh)>=5) ans+=INF;
		if (emp){
			if (type==wh) ans+=cnt?(val2[ry-ly+emp]>>1):val2[ry-ly+emp];
			else ans+=cnt?(val[ry-ly+emp]>>1):val[ry-ly+emp];
		}
	}
	//竖
	lx=rx=tlx=trx=x;
	emp=0;
	cnt=0;
	while (lx>0&&(*t).data[lx-1][y]==type) --lx;
	while (tlx>0&&((*t).data[tlx-1][y]==type||(*t).data[tlx-1][y]==0)) --tlx;
	lx2=lx;
	if (lx>0&&(*t).data[lx-1][y]==0){
		++emp;
		if (type==wh){
			while (lx>1&&(*t).data[lx-2][y]==type) --lx,++cnt;
			ans-=val[cnt];
		}
	}
	while (rx<N-1&&(*t).data[rx+1][y]==type) ++rx;
	while (trx<N-1&&((*t).data[trx+1][y]==type||(*t).data[trx+1][y]==0)) ++trx;
	if (trx-tlx>=4){
		rx2=rx;
		if (rx<N-1&&(*t).data[rx+1][y]==0){
			++emp;
			if (type==wh){
				while (rx<N-2&&(*t).data[rx+2][y]==type) ++rx,++cnt;
				ans-=val[cnt];
			}
		}
		if (rx-lx+1+(type==wh)>=5) ans+=INF;
		if (emp){
			if (type==wh) ans+=cnt?(val2[rx-lx+emp]>>1):val2[rx-lx+emp];
			else ans+=cnt?(val[rx-lx+emp]>>1):val[rx-lx+emp];
		}
	}
	//主对角
	lx=rx=tlx=trx=x;
	ly=ry=tly=ttry=y;
	emp=0;
	cnt=0;
	while (lx>0&&ly>0&&(*t).data[lx-1][ly-1]==type) --lx,--ly;
	while (tlx>0&&tly>0&&((*t).data[tlx-1][tly-1]==type||(*t).data[tlx-1][tly-1]==0)) --tlx,--tly;
	lx2=lx;
	if (lx>0&&ly>0&&(*t).data[lx-1][ly-1]==0){
		++emp;
		if (type==wh){
			while (lx>1&&ly>1&&(*t).data[lx-2][ly-2]==type) --lx,--ly,++cnt;
			ans-=val[cnt];
		}
	}
	while (rx<N-1&&ry<N-1&&(*t).data[rx+1][ry+1]==type) ++rx,++ry;
	while (trx<N-1&&ttry<N-1&&((*t).data[trx+1][ttry+1]==type||(*t).data[trx+1][ttry+1]==0)) ++trx,++ttry;
	if (trx-tlx>=4){
		rx2=rx;
		if (rx<N-1&&ry<N-1&&(*t).data[rx+1][ry+1]==0){
			++emp;
			if (type==wh){
				while (rx<N-2&&ry<N-2&&(*t).data[rx+2][ry+2]==type) ++rx,++ry,++cnt;
				ans-=val[cnt];
			}
		}
		if (rx-lx+1+(type==wh)>=5) ans+=INF;
		if (emp){
			if (type==wh) ans+=cnt?(val2[rx-lx+emp]>>1):val2[rx-lx+emp];
			else ans+=cnt?(val[rx-lx+emp]>>1):val[rx-lx+emp];
		}
	}
	//次对角 
	lx=rx=tlx=trx=x;
	ly=ry=tly=ttry=y;
	emp=0;
	cnt=0;
	while (lx>0&&ry<N-1&&(*t).data[lx-1][ry+1]==type) --lx,++ry;
	while (tlx>0&&ttry<N-1&&((*t).data[tlx-1][ttry+1]==type||(*t).data[tlx-1][ttry+1]==0)) --tlx,++ttry;
	lx2=lx;
	if (lx>0&&ry<N-1&&(*t).data[lx-1][ry+1]==0){
		++emp;
		if (type==wh){
			while (lx>1&&ry<N-2&&(*t).data[lx-2][ry+2]==type) --lx,++ry,++cnt;
			ans-=val[cnt];
		}
	}
	while (rx<N-1&&ly>0&&(*t).data[rx+1][ly-1]==type) ++rx,--ly;
	while (trx<N-1&&tly>0&&((*t).data[trx+1][tly-1]==type||(*t).data[trx+1][tly-1]==0)) ++trx,--tly;
	if (trx-tlx>=4){
		rx2=rx;
		if (rx<N-1&&ly>0&&(*t).data[rx+1][ly-1]==0){
			++emp;
			if (type==wh){
				while (rx<N-2&&ly>1&&(*t).data[rx+2][ly-2]==type) ++rx,--ly,++cnt;
				ans-=val[cnt];
			}
		}
		if (rx-lx+1+(type==wh)>=5) ans+=INF;
		if (emp){
			if (type==wh) ans+=cnt?(val2[rx-lx+emp]>>1):val2[rx-lx+emp];
			else ans+=cnt?(val[rx-lx+emp]>>1):val[rx-lx+emp];
		}
	}
	return ans;
}
ll calc(node*t,int wh){
	ll ans=0;
	wh=wh?1:-1;
	for (int i=0;i<N;++i){
		for (int j=0;j<N;++j){
			if ((*t).data[i][j]==1)
			ans+=calc_p(t,i,j,1,wh)+(*t).base[i][j]*Alpha;
			if ((*t).data[i][j]==-1)
			ans-=calc_p(t,i,j,-1,wh)+(*t).base[i][j]*Alpha;
		}
	}
	return ans;
}
int X,Y;
bool check_five(node*t){
	ll mx=-MX;
	for (int i=0;i<N;++i){
		for (int j=0;j<N;++j)if((*t).can[i][j]&&!(*t).data[i][j]){
			node now=(*t);
			now.data[i][j]=1;
			ll tmp=calc(&now,0);
			if (tmp>mx){
				mx=tmp;
				X=i,Y=j;
			}
		}
	}
}
ll dfs(int depth,int wh,node*t,ll a,ll b){
	if (depth==MX_deep) return calc(t,wh);
	ll tmp=calc(t,wh);
	if (abs(tmp)>=INF){
		if (depth>1) return tmp;
		else{
			check_five(t);
			return tmp;
		}
	}
	bool vis[N][N],gfg=0;
	memset(vis,0,sizeof(vis));
	double process=0;
	for (int i=1;i<N-1;++i){
		for (int j=1;j<N-1;++j)if(!(*t).data[i][j]&&((*t).data[i-1][j]||(*t).data[i+1][j]||(*t).data[i][j-1]||(*t).data[i][j+1])){
			if (depth==1) process+=1,cerr<<process*100./(N*N)<<"% ";
			vis[i][j]=1;
			node now=(*t);
			now.data[i][j]=wh?1:-1;
			now.update_base(i,j);
			ll v=dfs(depth+1,wh^1,&now,a,b);
			if (wh){
				if (v>a){
					if (depth==1) X=i,Y=j;
					a=v;
				}
			}else b=min(b,v);
			if (a>=b){gfg=1;break; }
		}
		if (gfg) break;
	}
	if (gfg){
		if (depth==1) cerr<<"\n100%\n\n";
		return wh?a:b;
	}
	for (int thx=1;thx<=T;++thx){
		int i=rand()%N,j=rand()%N;
		while (vis[i][j]||(*t).can[i][j]) i=rand()%N,j=rand()%N;
		vis[i][j]=1;
		if(!(*t).data[i][j]){
			if (depth==1) process+=1,cerr<<process*100./(N*N)<<"% ";
			node now=(*t);
			now.data[i][j]=wh?1:-1;
			now.update_base(i,j);
			ll v=dfs(depth+1,wh^1,&now,a,b);
			if (wh){
				if (v>a){
					if (depth==1) X=i,Y=j;
					a=v;
				}
			}else b=min(b,v);
			if (a>=b){gfg=1;break;}
		}
	}
	if (gfg){
		if (depth==1)cerr<<"\n100%\n\n";
		return wh?a:b;
	}
	for (int i=0;i<N;++i){
		for (int j=0;j<N;++j){
			if (!vis[i][j]) if (depth==1) process+=1,cerr<<process*100./(N*N)<<"% ";
			if((*t).can[i][j]&&!vis[i][j]&&!(*t).data[i][j]){
				node now=(*t);
				now.data[i][j]=wh?1:-1;
				ll v=dfs(depth+1,wh^1,&now,a,b);
				if (wh){
					if (v>a){
						if (depth==1) X=i,Y=j;
						a=v;
					}
				}else b=min(b,v);
				if (a>=b){gfg=1;break;}
			}	
		}
		if (gfg) break;
	}
	if (depth==1) cerr<<"\n100%\n\n";
	return wh?a:b;
}
int main(){
	srand((unsigned ll)new char);
	init();
/*	freopen("data1.cpp","r",stdin);
	node ttt;
	for (int i=0;i<N;++i) int x=read();
	for (int i=0;i<N;++i){
		int x=read();
		for (int j=0;j<N;++j){
			char t=getchar();
			while (t==' ') t=getchar();
			if (t=='+') ttt.data[i][j]=0;
			if (t=='X') ttt.data[i][j]=1,ttt.update_base(i,j);
			if (t=='O') ttt.data[i][j]=-1,ttt.update_base(i,j);
		}
	}
	fclose(stdin);
	ttt.print();
	cout<<calc(&ttt,1)<<endl;
	Player=1;
//	return 0;
	node noww=ttt;
		while(1){
			ll tmp=dfs(1,1,&noww,-MX,MX);
			if (tmp<-INF) X=0,Y=0;
			noww.data[X][Y]=1;
			noww.update_base(X,Y);
			noww.print();
			Pair step=get();
			if (step.x==N) return 0;
			noww.data[step.x][step.y]=-1;
			noww.update_base(step.x,step.y);
		}
	return 0;
/*	int n=read();
	ttt.cl();
	node ttt;
	for (int i=1;i<=n;++i){
		int x=read(),y=read(),vv=read();
		ttt.data[x][y]=vv;
		ttt.print();
	}
	cout<<calc(&ttt,1);
	return 0;*/
//	cerr<<Filename_in<<endl<<Filename_out<<endl;
	node now;
	now.cl();
	now.can[N>>1][N>>1]=1;
	if (Player){
		X=(N>>1),Y=(N>>1);
		out(X,Y);
		now.data[X][Y]=1;
		now.update_base(X,Y);
		now.print();
		while(1){
			Pair step=get();
			if (step.x==N) return 0;
			now.data[step.x][step.y]=-1;
			now.update_base(step.x,step.y);
			now.print();
			ll tmp=dfs(1,1,&now,-MX,MX);
		//	if (tmp<-INF) X=N,Y=N;
			out(X,Y);
			now.data[X][Y]=1;
			now.update_base(X,Y);
			now.print();
		}
	}
	else{
		while(1){
			Pair step=get();
			if (step.x==N) return 0;
			now.data[step.x][step.y]=-1;
			now.update_base(step.x,step.y);
			now.print();
			ll tmp=dfs(1,1,&now,-MX,MX);
		//	if (tmp<-INF) X=N,Y=N;
			out(X,Y);
			now.data[X][Y]=1;
			now.update_base(X,Y);
			now.print();
		}
	}
	return 0;
}
