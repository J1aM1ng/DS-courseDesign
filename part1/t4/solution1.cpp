#include<cstdio>//»ØËÝ 
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=25;
struct Edge{
    int u,w,next;
};
class Dag{
    public:
    int n,ans,idx,pmax;
    int in[maxn],vis[maxn],head[maxn],status[maxn];

    Dag(){
        idx=0;
        ans=maxn;
        memset(p,0,sizeof(p));
        memset(in,0,sizeof(in));
        memset(vis,0,sizeof(vis));
        memset(status,0,sizeof(status));
        for(int i=1;i<=maxn;i++)head[i]=-1;
    }

    void addedge(int u,int v,int w);
    void toposort();
    void work1(int x,int tot);
    void dfs(int x);
    void judge();

    private:
    int cnt,p[maxn],topo[maxn];
    bool flag;
    Edge edge[500];

};
void Dag::addedge(int u,int v,int w){
    edge[idx].u=v;
    edge[idx].w=w;
    edge[idx].next=head[u];
    in[v]++;
    head[u]=idx++;
}
void Dag::toposort(){
    priority_queue<int>q;
    cnt=0;
    for(int i=1;i<=n;i++)
        if(!in[i])q.push(-i);
    while(!q.empty()){
        int u=-q.top();q.pop();
        topo[++cnt]=u;
        for(int i=head[u];i!=-1;i=edge[i].next){
            int v=edge[i].u;
            if(--in[v]==0)q.push(-v);
        }
    }
}
void Dag::work1(int x,int tot){
    if(tot>ans)return;
    if(x>n){
        judge();
        if(flag){
            ans=min(ans,tot);
        }
        return;
    }
    status[x]=1;
    work1(x+1,tot+1);
    status[x]=0;
    work1(x+1,tot);
}
void Dag::judge(){
    status[1]=1;
    for(int i=1;i<=n;i++){
        vis[i]=0;
        if(status[i])p[i]=pmax;
        else p[i]=-1;
    }
    for(int i=1;i<=cnt;i++){
        int u=topo[i];
        for(int j=head[u];j!=-1;j=edge[j].next){
            int v=edge[j].u,w=edge[j].w;
            p[v]=max(p[v],p[u]-w);
        }
    }
    flag=1;
    for(int i=1;i<=n;i++){
        if(p[i]<0){
            flag=0;
            return;
        }
    }
    dfs(1);
}
void Dag::dfs(int x){
    if(!flag)return;
    vis[x]=1;
    for(int i=head[x];i!=-1;i=edge[i].next){
        int u=edge[i].u,w=edge[i].w;
        if(p[x]>=w){
            if(vis[u])continue;
            vis[u]=1;
            dfs(u);
        }
        else{
            flag=0;
            return;
        }
    }
}
int main(){
    freopen("a.in","r",stdin);
    Dag d;
    int n,m,l,u,v,w;
    scanf("%d%d%d",&n,&m,&l);
    d.n=n,d.pmax=l;
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&u,&v,&w);
        d.addedge(u,v,w);
    }
    d.toposort();
    d.work1(2,0);
    printf("%d\n",d.ans);
    return 0;
}
