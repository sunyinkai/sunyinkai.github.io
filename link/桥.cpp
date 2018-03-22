void dfs(int u,int par){
	dfn[u]=low[u]=++dfs_clock;
	for(int i=head[u];~i;i=es[i].next){
		int v=es[i].to;
		if((i^1)==par)continue;
		if(!dfn[v]){
			dfs(v,i);
			low[u]=min(low[u],low[v]);
			if(low[v]>dfn[u]){
				es[i].isCut=es[i^1].isCut=1;
			}
		}else{
			low[u]=min(low[u],dfn[v]);
		}
	}
}
