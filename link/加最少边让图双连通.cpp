#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXV=5000+7,MAXE=10000+7;
struct edge{
	int from,to,next;
	bool isCut;
}es[MAXE*2];
int tot,head[MAXV],du[MAXV];
void init(){
	tot=0;
	memset(head,-1,sizeof(head));
}
void addEdge(int a,int b){
	es[tot].from=a;
	es[tot].to=b;
	es[tot].next=head[a];
	es[tot].isCut=0;
	head[a]=tot++;
}
int dfn[MAXV],low[MAXV],dfs_clock,res;
int par[MAXV];
int find(int x){
	return par[x]==x?par[x]:par[x]=find(par[x]);
}
void inline unit(int a,int b){
	a=find(a);
	b=find(b);
	if(a!=b)par[a]=b;
}
void dfs(int u,int id){
	dfn[u]=low[u]=++dfs_clock;
	for(int i=head[u];~i;i=es[i].next){
		int v=es[i].to;
		if((i^1)==id)continue;
		if(!dfn[v]){
			dfs(v,i);
			low[u]=min(low[u],low[v]);
			if(low[v]>dfn[u]){
				es[i].isCut=true;
				es[i^1].isCut=true;
			}
		}else
			low[u]=min(low[u],dfn[v]);
	}
}
int main(){
	int F,R;scanf("%d%d",&F,&R);
	init();
	dfs_clock=0;
	res=0;
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	for(int i=0;i<R;++i){
		int a,b;scanf("%d%d",&a,&b);
		addEdge(a,b);
		addEdge(b,a);
	}
	dfs(1,-1);
	for(int i=1;i<=F;++i)par[i]=i;
	for(int i=0;i<tot;i+=2){
		if(es[i].isCut)continue;
		int u=es[i].from,v=es[i].to;
		unit(u,v);
	}
	
	for(int i=0;i<tot;i+=2){
		if(es[i].isCut){
			int u=es[i].from,v=es[i].to;
			du[par[u]]++;
			du[par[v]]++;
		}
	}
	for(int i=1;i<=F;++i){//(叶子节点个数+1)/2
		if(du[i]==1)++res;
	}
	printf("%d\n",(res+1)/2);
	return 0;
}
