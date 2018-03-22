void dfs(int u,int pre){
	dfn[u]=low[u]=++dfs_clock;
	int child=0;
	for(auto v:G[u]){
		if(v==pre)continue;
		if(!dfn[v]){
			++child;
			dfs(v,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>=dfn[u]){
				if(!iscut[u]){
					iscut[u]=1;
					++cutCnt;
				}
			}
		}else low[u]=min(low[u],dfn[v]);
	}
	if(pre==-1&&child==1){//如果只有一个孩子,那么根节点不是割点
		--cutCnt;
		iscut[u]=0;
	}
}
