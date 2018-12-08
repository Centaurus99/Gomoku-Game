#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<ctime>
#include"game.h"
using namespace std;
int main(){
	init();
	Pair t;
	system("start write.exe");
	while (1){
		l1:
		int x,y;
		freopen("tmp","r",stdin);
		while (scanf("%d%d",&x,&y)==EOF){
			fclose(stdin);
			stop(500);
			goto l1;
		}
		fclose(stdin);
		freopen("tmp","w",stdout);
		fclose(stdout);
		out(x,y);
	}
	return 0;
}
