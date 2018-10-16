 #include<bits/stdc++.h>
using namespace std;
#define IM 1000000000

struct nodes
{
    int data;
    int weight;
    struct nodes* next;
};

struct adjlist
{
    struct nodes *head;
};

struct Graph
{
    int v;
    int e;
    struct adjlist* array;
};

struct node
{
int data;
int degree;
struct node *parent;
struct node *sibling;
struct node *child;
};

map <int,struct node*> mp;
map <int,struct node*>::iterator it;

void display_heap(struct node *h)
{
if (h == NULL)
    return ;
cout<<h->data<<" ";
if(h->child!=NULL)
    display_heap(h->child);
if(h->sibling != NULL)
    display_heap(h->sibling);
}

struct node *create_node(int data)
{
struct node* temp=(struct node*)malloc(sizeof(struct node));
temp->data=data;
temp->degree=1;
temp->parent=NULL;
temp->sibling=NULL;
temp->child=NULL;
return temp;
}

struct node* find_min(struct node *h)
{
if(h==NULL)
	return NULL;
int min=h->data;
struct node* x=h;
h=h->sibling;
while(h!=NULL)
	{
	if(min>h->data)
		{
		min=h->data;
		x=h;
		}
	h=h->sibling;
	}
return x;
}

struct node *merge_them(struct node* H1,struct node* H2)
{
    struct node* H = NULL;
    struct node* y;
    struct node* z;
    struct node* a;
    struct node* b;
    y=H1;
    z=H2;
    if(y!=NULL)
        {
        if(z!=NULL)
            {
            if(y->degree<=z->degree)
                H=y;
            else if(y->degree>z->degree)
                H=z;
            }
        else
            H=y;
        }
    else
        H=z;
    while(y!=NULL&&z!=NULL)
        {
        if(y->degree<z->degree)
            {
            y=y->sibling;
            }
        else if(y->degree==z->degree)
            {
            a=y->sibling;
            y->sibling=z;
            y=a;
            }
        else
            {
            b=z->sibling;
            z->sibling=y;
            z=b;
            }
    }
    return H;
}

struct node *union_key(struct node *h1,struct node *h2)
{
struct node *h=merge_them(h1,h2);
if(h==NULL)
	return NULL;
if(h->sibling==NULL)
	return h;
struct node * x=h;
struct node *next=x->sibling;
struct node *prev=NULL;
while(next!=NULL)
    {
    if((x->degree!=next->degree))
        {
        prev=x;
        x=next;
        next=x->sibling;
        }
    else if((next->sibling!=NULL)&&(next->degree==next->sibling->degree))
        {
        prev=x;
        x=next;
        next=x->sibling;
        }
    else
        {
        if(x->data<=next->data)
            {
            x->sibling=next->sibling;
            next->parent=x;
            next->sibling=x->child;
            x->child=next;
            x->degree+=1;
            next=x->sibling;
            }
        else
            {
            if(prev==NULL)
                h=next;
            else
                prev->sibling=next;
            x->parent=next;
            x->sibling=next->child;
            next->child=x;
            next->degree+=1;
            x=next;
            next=x->sibling;
            }
        }
    }
return h;
}

struct node * insert_key(struct node *h1,int data)
{
struct node *h2=create_node(data);
mp[data]=h2;
h1=union_key(h1,h2);
return h1;
}

struct node* rev_list(struct node *z)
{
struct node *y=NULL;
struct node *x;
struct node *a;
while(z!=NULL)
    {
    x=z;
    z=z->sibling;
    a=y;
    y=x;
    y->sibling=a;
    }
return y;
}

struct node *link_this(struct node *p)
{
struct node *children=p->child;
struct node *x=children;
while(x!=NULL)
	{
	x->parent=NULL;
	x=x->sibling;
	}
struct node *y=NULL;
y=rev_list(children);
return y;
}

struct node* extract_min(struct node *h1)
{
if(h1==NULL)
	{
	cout<<"Heap is empty"<<endl;
	return NULL;
	}
if(h1->sibling==NULL)
	{
	cout<<"Minimum key node has data="<<h1->data<<endl;
	it=mp.find(h1->data);
	mp.erase (it);
	h1=link_this(h1);
	return h1;
	}
struct node *p=find_min(h1);
struct node *h2=NULL;
if(h1->data==p->data)
	{
	cout<<"Minimum key node has data="<<h1->data<<endl;
	it=mp.find(h1->data);
	mp.erase (it);
	h2=link_this(h1);
	h1=h1->sibling;
	h1=union_key(h1,h2);
	return h1;
	}
else
	{
	struct node *x=h1;
	while(x->sibling->data!=p->data)
		x=x->sibling;
    cout<<"Minimum key node has data="<<p->data<<endl;
	it=mp.find(x->sibling->data);
	mp.erase (it);
	h2=link_this(x->sibling);
	x->sibling=x->sibling->sibling;
	h1=union_key(h1,h2);
	return h1;
	}
}

void decrease_key(struct node *h,int m,int l)
{
if(l>=m)
	{
	cout<<"Provided key is greater than or equal to actual key"<<endl;
	return ;
	}
it=mp.find(m);
if(it==mp.end())
	{
	cout<<"Key not found"<<endl;
	return ;
	}
struct node *p=it->second;
mp.erase (it);
mp[l]=p;
p->data=l;
struct node* z=p->parent;
while(z!=NULL&&z->data>p->data)
	{
	int temp;
	temp=p->data;
	p->data=z->data;
	z->data=temp;
	mp[z->data]=z;
	mp[p->data]=p;
	p=z;
	z=p->parent;
	}
cout<<"Key reduced"<<endl;
}

struct node * delete_key(struct node *h,int m)
{
it=mp.find(m);
if(it==mp.end())
	{
	cout<<"Key not found"<<endl;
	return h;
	}
decrease_key(h,m,-1000000000);
h=extract_min(h);
return h;
}

int DJ(int src,struct Graph * graph)
{
    int v=graph->v;
    int dist[v],i;
    bool sptSet[v];
    for (int i = 0; i < v; i++)
        dist[i] = IM, sptSet[i] = false;
    dist[src] = 0;
    FibonacciHeap fh;
    node* p;
    node* H;
    H = fh.InitializeHeap();

    for(i=0;i<v;i++)
        {
        p = fh.Create_node(dist[i],i);
        H = fh.Insert(H,p);
        }
    for (int count = 0; count < v-1; count++)
        {
        p = fh.Extract_Min(H);
        int u=p->index;
        cout<<u<<endl;
        sptSet[u] = true;

        struct nodes * xyz=graph->array[u].head;
        while(xyz!=NULL)
            {
            //cout<<xyz->data<<" "<<xyz->weight<<endl;
            if(!sptSet[xyz->data]&& dist[u]!=IM &&dist[u]+xyz->weight<dist[xyz->data])
                {
                dist[xyz->data] = dist[u] + xyz->weight;
                fh.Decrease_key(H, dist[xyz->data], xyz->data);
                }
            xyz=xyz->next;
            }
        }
    fh.Display(H);
    for(i=0;i<v;i++)
        cout<<dist[i]<<" ";
    cout<<endl;
    int maxi=0;
    for(i=0;i<v;i++)
        {
        if(i==src||dist[i]==IM)
            continue;
        else if(dist[i]>maxi)
            maxi=dist[i];
        }
    return maxi;
}

struct nodes *Crate(int x,int w)
{
struct nodes * nod=(struct nodes*)malloc(sizeof(struct nodes));
nod->data=x;
nod->weight=w;
nod->next=NULL;
return nod;
}

struct Graph *Crategraph(int v,int e)
{
struct Graph *graph=(struct Graph*)malloc(sizeof(struct Graph));
graph->v=v;
graph->e=e;
graph->array=(struct adjlist*)malloc(v*sizeof(struct adjlist));
int i;
for(i=0;i<v;i++)
    graph->array[i].head=NULL;
return graph;
}

void addedge(struct Graph* graph,int x,int y,int p)
{
struct nodes *nod=Crate(y,p);
nod->next=graph->array[x].head;
graph->array[x].head=nod;

nod=Crate(x,p);
nod->next=graph->array[y].head;
graph->array[y].head=nod;
}

int main()
{
    int v,e;
    cin>>v>>e;
    struct Graph *graph=Crategraph(v,e);
    int i,x,y,p;
    for(i=0;i<e;i++)
        {
        cin>>x>>y>>p;
        addedge(graph,x-1,y-1,p);
        }

    int max=0,maxi;
    for(i=0;i<v;i++)
        {
        maxi=DJ(i,graph);
        if(maxi>max)
            max=maxi;
        }
    cout<<max<<endl;
}

int main()
{
ios_base::sync_with_stdio(false);
struct node *H=NULL;
int flag=0,l,data,m,x;
struct node *p;
while(1)
	{
    cout<<"1.Insert Element in the heap"<<endl;
   	cout<<"2.Find Minimum key node"<<endl;
    cout<<"3.Extract Minimum key node"<<endl;
    cout<<"4.Decrease key of a node"<<endl;
    cout<<"5.Delete a node"<<endl;
    cout<<"6.Display Heap"<<endl;
    cout<<"7.Exit"<<endl;
    cout<<"Enter Your Choice:";
    cin>>l;
    switch(l)
    	{
    	case 1:
    		cout<<"Enter key:";
    		cin>>data;
    		H=insert_key(H,data);
    		break;
    	case 2:
    		p=find_min(H);
    		if(p==NULL)
    			cout<<"Heap is empty"<<endl;
    		else
    			cout<<"Minimum key node has data="<<p->data<<endl;
    		break;
    	case 3:
    		H=extract_min(H);
    		break;
    	case 4:
    		cout<<"Enter key to be decreased:";
    		cin>>m;
    		cout<<"Enter new value:";
    		cin>>x;
    		mp[x]=p;
    		decrease_key(H,m,x);
    		break;
    	case 5:
    		cout<<"Enter key to be deleted:";
    		cin>>m;
    		H=delete_key(H,m);
    		break;
    	case 6:
    		display_heap(H);
    		cout<<endl;
    		break;
    	case 7:
    		flag=1;
    		break;
    	}
    if(flag==1)
    	break;
	}
return 0;
}
