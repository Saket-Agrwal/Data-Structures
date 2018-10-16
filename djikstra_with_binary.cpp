#include<bits/stdc++.h>
using namespace std;
#define IM 1000000000

int parent(int num)
{
return num/2;
}

int left(int num)
{
return 2*num+1;
}

int right(int num)
{
return 2*num+2;
}

void swap1(int a,int b,int arr[])
{
int temp;
temp=arr[a];
arr[a]=arr[b];
arr[b]=temp;
}

void swap2(int a,int b,int arr[][2])
{
int temp;
temp=arr[a][0];
arr[a][0]=arr[b][0];
arr[b][0]=temp;
temp=arr[a][1];
arr[a][1]=arr[b][1];
arr[b][1]=temp;
}

void Decrease_key(int arr[][2],int index[],int i,int x)
{
arr[i][0]=x;
int a,b;
while(i>0&&arr[parent(i)][0]>arr[i][0])
    {
    a=arr[i][1];
    b=arr[parent(i)][1];
    swap1(a,b,index);
    swap2(parent(i),i,arr);
    i=parent(i);
    }
return;
}

void Heapify(int arr[][2],int index[],int size,int i)
{
int l=left(i),r=right(i),a,b;
int smaller=i;
if(l<size&&arr[l][0]<arr[smaller][0])
    smaller=l;
if(r<size&&arr[r][0]<arr[smaller][0])
    smaller=r;
if(smaller!=i)
    {
    a=arr[i][1];
    b=arr[smaller][1];
    swap1(a,b,index);
    swap2(i,smaller,arr);
    Heapify(arr,index,size,smaller);
    }
}

void Extract(int arr[][2],int index[],int size)
{
arr[0][0]=arr[size][0];
arr[0][1]=arr[size][1];
index[arr[0][1]]=0;
Heapify(arr,index,size,0);
return ;
}

void Djikstra(int arr[],int parent[],int s,int v,vector < pair<int,int> > vect[])
{
int mark[v];
int dist[v][2];
int index[v];
int i,j,k,temp,w,si;
for(i=0;i<v;i++)
	{
	mark[i]=0;
	dist[i][0]=1000000000;
	dist[i][1]=i;
	index[i]=i;
	}
Decrease_key(dist,index,s,0);
parent[s]=s;
for(i=0;i<v-1;i++)
	{
	temp=dist[0][1];
	arr[temp]=dist[0][0];
	mark[temp]=1;
	Extract(dist,index,v-1-i);
	si=vect[temp].size();
	for(j=0;j<si;j++)
		{
		k=vect[temp][j].first;
		w=vect[temp][j].second;
		if(mark[k]==1)
			continue;
		else if(arr[temp]+w>=dist[index[k]][0])
			continue;
		else
            {
			Decrease_key(dist,index,index[k],arr[temp]+w);
            parent[k]=temp;
            }
		}
	}
	temp=dist[0][1];
	arr[temp]=dist[0][0];
}

void Display_path(int parent[],int b)
{
if(parent[b]==b)
	cout<<b+1<<" ";
else
	{
	Display_path(parent,parent[b]);
	cout<<b+1<<" ";
	}
}

int main()
{
int v,e;
cout<<"Enter number of vertices and edges:";
cin>>v>>e;
vector <pair <int,int> > vect[v];
int i,a,b,c,si,j;
for(i=0;i<e;i++)
    {
    cin>>a>>b>>c;
    vect[a-1].push_back(make_pair(b-1,c));
    vect[b-1].push_back(make_pair(a-1,c));
    }
for(i=0;i<v;i++)
	{
    si=vect[i].size();
	for(j=0;j<si;j++)
		cout<<vect[i][j].first<<"-->"<<vect[i][j].second<<" ";
	cout<<endl;
	}
int *dist[v];
int *parent[v];
for(i=0;i<v;i++)
	{
    dist[i]=(int*)malloc(v*sizeof(int));
	parent[i]=(int*)malloc(v*sizeof(int));
	}
for(i=0;i<v;i++)
    Djikstra(dist[i],parent[i],i,v,vect);
for(i=0;i<v;i++)
	{
    cout<<"Shortest distance of all vertices from "<<i+1<<":"<<endl;
	for(j=0;j<v;j++)
		cout<<j<<"->"<<dist[i][j]<<" ";
	cout<<endl;
	}
while(1)
	{
	cout<<"Enter shortest path between two vertices:";
	cin>>a>>b;
	if(a<0||b<0)
        break;
	Display_path(parent[a-1],b-1);
	cout<<endl;
	}
}
/*
1 2 4
1 8 8
2 3 8
2 8 11
3 4 7
3 6 4
3 9 2
4 5 9
4 6 14
5 6 10
6 7 2
7 8 1
7 9 6
8 9 7
*/
