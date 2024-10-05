#include<iostream>
#include <queue>
#include <vector>
const int MAXN=50004;
const int MAXM=100005;

int n,m;
long long s,t,dis;

long long shortest[MAXN];
int head[MAXN],next[MAXM*2],edto[MAXM*2],ecnt;
long long edle[MAXM*2];
bool visited[MAXN];
void ins(int s,int t,long long dis)
{
    next[++ecnt]=head[s];
    head[s]=ecnt;
    edto[ecnt]=t;
    edle[ecnt]=dis;
}
void ins2(int s,int t,long long dis)
{
    ins(s,t,dis);
    ins(t,s,dis);
}
struct node
{
    long long dis;
    int t;
    node(){}
    node(long long dis,int t):dis(dis),t(t) {}
    bool operator>(const node &that)const
    {
        return dis>that.dis;
    }
    bool operator<(const node &that)const
    {
        return dis<that.dis;
    }
};
std::priority_queue<node, std::vector<node>, std::greater<node> > stdpq;
void dijk(int source)
{
    for(int i=1;i<=n;i++)
    {
        shortest[i]=2100000000;
        visited[i]=false;
    }
    shortest[source]=0;
    while(!stdpq.empty())stdpq.pop();
    stdpq.push(node(0,source));
    while(!stdpq.empty())
    {
        node top=stdpq.top();stdpq.pop();
        int now=top.t;
        if(visited[now])continue;
        visited[now]=true;
        for(int i=head[now];i;i=next[i])
        {
            int son=edto[i],len=edle[i];
            if(shortest[now]+len<shortest[son])
            {
                shortest[son]=shortest[now]+len;
                stdpq.push(node(shortest[son],son));
            }
        }
    }
}
int a[6];
long long between[6][6];
long long ans=0x7fffffffffffffff;
int cnt=0;
void dfs(int now,long long sum)
{
    visited[now]=true;
    cnt++;
    if(cnt==6)
        ans=std::min(ans,sum);
    for(int i=0;i<=5;i++)
    {
        if(!visited[i])
            dfs(i,sum+between[now][i]);
    }
    visited[now]=false;
    cnt--;
}

int main()
{
    a[0]=1;
    std::cin>>n>>m>>a[1]>>a[2]>>a[3]>>a[4]>>a[5];
    for(int i=1;i<=m;i++)
    {
        std::cin>>s>>t>>dis;
        ins2(s,t,dis);
    }
    for(int i=0;i<=5;i++)
    {
        dijk(a[i]);
        for(int j=0;j<=5;j++)
            between[i][j]=shortest[a[j]];
    }
    for(int i=0;i<=5;i++)
    {
        visited[i]=false;
    }
    dfs(0,0);
    std::cout<<ans;
}