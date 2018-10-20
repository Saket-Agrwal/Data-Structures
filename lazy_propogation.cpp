#include<bits/stdc++.h>
using namespace std;
int arr[100000];
int tree[400001] = {0};
int lazy[400001] = {0};
int n;

void build(int node,int s,int e)
{
    if(s==e)
        tree[node] = arr[s];
    else
    {
        int mid = (s+e)/2;
        build(2*node+1,s,mid);
        build(2*node+2,mid+1,e);
        tree[node] = tree[2*node+1]+tree[2*node+2];
    }
}

void update(int node,int l,int r,int s,int e,int val)
{
    if(s>r||e<l||s>e)
        return;
    if(lazy[node]!=0)
    {
        tree[node] += (e-s+1)*lazy[node];
        if(s!=e)
        {
            lazy[2*node+1] = lazy[node];
            lazy[2*node+2] = lazy[node];
        } 
        lazy[node] = 0;
    }
    if(s>=l&&e<=r)
    {
        tree[node] += (r-l+1)*val;
        if(s!=e)
        {
            lazy[2*node+1] = lazy[node];
            lazy[2*node+2] = lazy[node];
        }
        return;
    }
    int mid = (s+e)/2;
    update(2*node+1,l,r,s,mid,val);
    update(2*node+2,l,r,mid+1,e,val);
    tree[node] = tree[2*node+1]+tree[2*node+2];
}

int sum(int node,int l,int r,int s,int e)
{
    if(s>r||e<l)
        return 0;
    if(lazy[node]!=0)
    {
        tree[node] += (e-s+1)*lazy[node];
        if(s!=e)
        {
            lazy[2*node+1] = lazy[node];
            lazy[2*node+2] = lazy[node];
        } 
        lazy[node] = 0;
    }
    if(s>=l&&e<=r)
        return tree[node];
    int mid = (s+e)/2;
    int p1 = sum(2*node+1,l,r,s,mid);
    int p2 = sum(2*node+2,l,r,mid+1,e);
    return p1+p2;
}

int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>arr[i];
    build(0,0,n-1);
    int q;
    cin>>q;
    while(q--)
    {
        int a;
        cin>>a;
        if(a==1)
        {
            int x,y;
            cin>>x>>y;
            cout<<sum(0,x,y,0,n-1)<<endl;
        }
        else
        {  
            int x,y,z;
            cin>>x>>y>>z;
            update(0,x,y,0,n-1,z);
        }
    }
    return 0;
}