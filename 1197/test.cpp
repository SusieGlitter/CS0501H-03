const int N=5e5+100;
using namespace std;
#include<cstdio>
#include<iostream>
#include<cmath>
#include<queue>
struct edge{
	int next,to;
}e[N],E[N];int H[N],Tot,h[N],tot;
inline void add(int a,int b){
	e[++tot]=(edge){h[a],b};h[a]=tot;
}
inline void ADD(int a,int b){
	E[++Tot]=(edge){H[a],b};H[a]=Tot;
}
bool have_a_bar[N];
int n,m,s,p,value[N];
void read_the_data(){
	cin>>n>>m;//专司输入 
	for(int i=1,u,v;i<=m;i++){
		cin>>u>>v;add(u,v);
	}
	for(int i=1;i<=n;i++)
		cin>>value[i];
	cin>>s>>p;
	for(int i=1;i<=p;i++)
	{
		int a;
		cin>>a;
		have_a_bar[a]=1;
	}
}
int Stack[N],stack_top;
int dfn[N],low[N],dfscnt;
int belong[N],scc,num[N];
int money[N];bool bar[N];
void tarjan(int u){
	Stack[++stack_top]=u;
	low[u]=dfn[u]=++dfscnt;
	for(int i=h[u];i;i=e[i].next){
		register int to=e[i].to;
		if (dfn[to]==0){
			tarjan(to);//递归进行计算 
			low[u]=min(low[u],low[to]);
		}
		else if (belong[to]==0)
			low[u]=min(low[u],dfn[to]);
	}
	if (dfn[u]==low[u]){
		num[belong[u]=++scc]=1;
		bar[scc]=have_a_bar[u];
		money[belong[u]]=value[u];
		while (Stack[stack_top]!=u){
			int t=Stack[stack_top];
			num[belong[t]=scc]++;
			money[scc]+=value[t];
			bar[scc]|=have_a_bar[t];
			--stack_top;
		}
		--stack_top;
	}
}
int ind[N],dp[N],ans;
void build_new_picture(){
	for(int u=1;u<=n;u++)
		for(int i=h[u];i;i=e[i].next){
			register int to=e[i].to;
			if (belong[u]!=belong[to]){
				++ind[belong[to]];
				ADD(belong[u],belong[to]);
			}
		}
}
void topo_algorithm_and_dp(){
	queue<int> q;//拓扑所需的队列 
	for(int i=1;i<=scc;i++)
		if (ind[i]==0) q.push(i);
	dp[belong[s]]=money[belong[s]];
	while (q.size()){
		int u=q.front();q.pop();
		for(int i=H[u];i;i=E[i].next){
			register int to=E[i].to;
			dp[to]=max(dp[to],dp[u]+money[to]);
			if ((--ind[to])==0) q.push(to);
		}
	}
}
void print_the_answer(){
	for(int i=1;i<=scc;i++)
		if (bar[i]&&dp[i]>ans)
			ans=dp[i];
	printf("%d",ans);
}
int main(){
	freopen("1197.in","r",stdin);
	read_the_data();
	for(int i=1;i<=n;i++)
		if (!dfn[i]) tarjan(i);
	build_new_picture();
	topo_algorithm_and_dp();
	print_the_answer();
	return 0;
}