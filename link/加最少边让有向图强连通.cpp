#include<cstdio>
#include<cstring>
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)
const int MAXV=107,MAXE=1e4+7;
struct edge{
	int to,next;
}es[MAXE*2];
int tot,head[MAXV];
void init(){
	tot=0;
	memset(head,-1,sizeof(head));
}
void addEdge(int a,int b){
	es[tot].to=b;
	es[tot].next=head[a];
	head[a]=tot++;
}
int dfn[MAXV],instack[MAXV],low[MAXV],scc=0;
int belong[MAXV],stack[MAXV],top=0,time=0;
int in[MAXV],out[MAXV];
void dfs(int u){
	dfn[u]=low[u]=++time;
	stack[top++]=u;
	instack[u]=1;
	for(int i=head[u];~i;i=es[i].next){
		int v=es[i].to;
		if(!dfn[v]){
			dfs(v);
			low[u]=min(low[u],low[v]);
		}else if(instack[v]) low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		++scc;
		int cnt=0;
		for(;;){
			int now=stack[--top];
			instack[now]=0;
			belong[now]=scc;
			++cnt;
			if(now==u)break;
		}
	}
}
int main(){
	int N;
	while(~scanf("%d",&N)){
		init();
		for(int i=1;i<=N;++i){
			int to;
			while(1){
				scanf("%d",&to);
				if(to==0)break;
				addEdge(i,to);
			}
		}
		scc=top=time=0;
		int inMax=0,outMax=0;
		memset(dfn,0,sizeof(dfn));
		memset(low,0,sizeof(low));
		memset(instack,0,sizeof(instack));
		memset(in,0,sizeof(in));
		memset(out,0,sizeof(out));
		for(int i=1;i<=N;++i){
			if(!dfn[i])dfs(i);
		}
		for(int u=1;u<=N;++u){ for(int i=head[u];~i;i=es[i].next){ int v=es[i].to;
				if(belong[u]==belong[v])continue;
				out[belong[u]]++;in[belong[v]]++;
			}
		}
		for(int i=1;i<=scc;++i){
			if(in[i]==0)inMax++;
			if(out[i]==0)outMax++;
		}
		if(scc==1)printf("1\n0\n");
		else printf("%d\n%d\n",inMax,max(inMax,outMax));
	}
	return 0;
}
