#include<cstdio>//分支限界 
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=25;
struct Edge{
    int u,w,next;
};
struct Node{
    int p,num,tot,tag,father;
    friend bool operator < (Node x,Node y){
        return x.tot>y.tot;
    }
};
class Dag{
    public:
    int n,ans,idx,pmax;
    int in[maxn],vis[maxn],head[maxn],status[maxn],mp[maxn][maxn];

    Dag(){
        idx=0;
        ans=maxn;
        memset(p,0,sizeof(p));
        memset(in,0,sizeof(in));
        memset(mp,0,sizeof(mp));
        memset(topo,0,sizeof(topo));
        for(int i=1;i<=maxn;i++)head[i]=-1;
    }

    void addedge(int u,int v,int w);
    void toposort();
    void work2();

    private:
    int cnt,p[maxn],topo[maxn];
    Edge edge[500];

};
void Dag::addedge(int u,int v,int w){
    edge[idx].u=v;
    edge[idx].w=w;
    edge[idx].next=head[u];
    in[v]++;
    head[u]=idx++;
    if(!mp[v][u])mp[v][u]=w;
    mp[v][u]=min(mp[v][u],w);
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
void Dag::work2(){
    priority_queue<Node>q;
    Node tree[10240];
    int tag=0;
    Node tmp;
    tmp.p=pmax;tmp.tot=0;tmp.num=1;tmp.tag=++tag,tmp.father=0;
    q.push(tmp);
    tree[tmp.tag]=tmp;
    while(!q.empty()){
        tmp=q.top();q.pop();
        if(tmp.num==n){
            ans=tmp.tot;
            break;
        }
        int v=topo[tmp.num+1];
        Node grand=tree[tmp.tag];
        tmp.num++;tmp.p=-1;
        while(grand.tag){
            if(mp[v][topo[grand.num]]){
                tmp.p=max(tmp.p,tree[grand.tag].p-mp[v][topo[grand.num]]);
            }
            grand=tree[grand.father];
        }
        tmp.father=tmp.tag;
        tmp.tag=++tag;
        bool f=0;
        for(int i=head[v];i!=-1;i=edge[i].next){
            int w=edge[i].w;
            if(tmp.p-w<0){
                f=1;
                break;
            }
        }
        if(tmp.p>=0&&!f){
            q.push(tmp);
            tree[tmp.tag]=tmp;
            tmp.tag=++tag;
        }
        tmp.tot++;tmp.p=pmax;tree[tmp.tag]=tmp;
        q.push(tmp);
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
    d.work2();
    printf("%d",d.ans);
    return 0;
}
