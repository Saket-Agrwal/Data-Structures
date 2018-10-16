#include<bits/stdc++.h>
using namespace std;

struct node
{
int data;
int degree;
struct node *right;
struct node *left;
struct node *parent;
struct node *child;
int mark;
};

struct node *Create_node(int data)
{
struct node *temp=(struct node*)malloc(sizeof(struct node));
temp->data=data;
temp->parent=NULL;
temp->child=NULL;
temp->left=temp;
temp->right=temp;
temp->degree=1;
temp->mark=0;
return temp;
}

void Display(struct node *h)
{
if(h==NULL)
	return;
else
	{
	struct node *x=h;
	   do
		{
		cout<<x->data<<" ";
		Display(x->child);
		x=x->right;
		}
		while(x!=h);
	}
}

struct node *Union(struct node *h,struct node *p)
{
struct node *y=p;
struct node *x;
if(p!=NULL)
{
   do
	{
	x=p;
	p=p->right;
	x->right=NULL;
	x->left=NULL;
	if(h==NULL)
		{
		h=x;
		h->left=h;
		h->right=h;
		continue;
		}
	x->right=h;
	x->left=h->left;
	(h->left)->right=x;
	h->left=x;
	if(x->data<h->data)
		h=x;
	}
	while(p!=y);
}
return h;
}

struct node *Insert(struct node *h,int data)
{
struct node *temp=Create_node(data);
h=Union(h,temp);
return h;
}

struct node *link_children(struct node *h)
{
struct node *temp=h->child;
struct node *x=temp;
if(x!=NULL)
    {
    do
        {
        x->parent=NULL;
        x=x->left;
            }
        while(x!=temp);
    }
return temp;
}

struct node *consolidate(struct node *h,int num)
{
if(h==NULL)
	return NULL;
int d=0;
while(num!=0)
	{
	d++;
	num=num/2;
	}
struct node *arr[d];
int i;
for(i=0;i<d;i++)
    arr[i]=NULL;
struct node *z=h;
struct node *x;
struct node *y;
int temp;
   do
	{
	x=z;
	z=z->left;
	x->left=x;
	x->right=x;
	temp=x->degree;
	while(arr[temp-1]!=NULL)
		{
		y=arr[temp-1];
		if(x->data>y->data)
			{
			x->parent=y;
			y->degree+=1;
			struct node *children=y->child;
			y->child=x;
			if(children!=NULL)
				{
				x->left=children->left;
				x->right=children;
				children->left->right=x;
				children->left=x;
				}
			x=y;
			arr[temp-1]=NULL;
			temp=x->degree;
			}
		else
			{
			y->parent=x;
			x->degree+=1;
			struct node *children=x->child;
			x->child=y;
			if(children!=NULL)
				{
				y->left=children->left;
				y->right=children;
				children->left->right=y;
				children->left=y;
				}
			arr[temp-1]=NULL;
			temp=x->degree;
			}
		}
	arr[temp-1]=x;
	}
	while(z!=h);
h=NULL;
for(i=0;i<d;i++)
	{
	if(arr[i]==NULL)
		continue;
	else
		{
		if(h==NULL)
			h=arr[i];
		else
			{
			x=arr[i];
			x->right=h;
			x->left=h->left;
			h->left->right=x;
			h->left=x;
			if(x->data<h->data)
				h=x;
			}
		}
	}
return h;
}

struct node * Extract_min(struct node *h,int num)
{
struct node *p=link_children(h);
if(h->left==h)
	{
	struct node *x=NULL;
	h=Union(x,p);
	}
else
	{
	h->left->right=h->right;
	h->right->left=h->left;
	h=h->right;
	h=Union(h,p);
	}
h=consolidate(h,num);
return h;
}

struct node* Find(node* H, int k)
{
    node* x = H;
    if(x==NULL)
    	return NULL;
    else
   		{
   		do
   			{
   			if(x->data==k)
   				return x;
   			else
   				{
   				struct node *z=Find(x->child,k);
   				if(z!=NULL)
   					return z;
   				}
   			x=x->right;
   			}
   			while(x!=H);
   		return NULL;
    	}
}

struct node * Cut(struct node *p)
{
struct node *y=p->right;
struct node *par=p->parent;
p->parent=NULL;
if(y==p)
    {
	par->child=NULL;
	return p;
    }
else
	{
	par->child=y;
	p->left->right=y;
	y->left=p->left;
	p->left=p;
	p->right=p;
	p->parent=NULL;
	return p;
	}
}

struct node *Decrease_key(struct node *H,struct node *p,int m)
{
if(p->parent==NULL)
	{
	p->data=m;
	if(H->data>p->data)
		H=p;
	return H;
	}
else
	{
	struct node *par=p->parent;
	p->data=m;
	if(par->data<=p->data)
        return H;
    else
        {
        p=Cut(p);
        par->degree=1;
        H=Union(H,p);
        struct node *z;
        while(par->parent!=NULL&&par->mark==1)
            {
            cout<<"HELLO"<<endl;
            z=par;
            z->mark=0;
            par=par->parent;
            par->degree=1;
            p=Cut(z);
            H=Union(H,p);
            }
        if(par->parent!=NULL)
            par->mark=1;
        return H;
        }
	}
}

struct node *Delete_key(struct node *H,struct node *p,int num)
{
H=Decrease_key(H,p,-1000000000);
H=Extract_min(H,num);
return H;
}

int main()
{
struct node *H=NULL;
struct node *p=NULL;
int l,n,m;
int flag=0;
int num=0;
while(1)
	{
	cout<<"1.Insert Element in the heap"<<endl;
   	cout<<"2.Find Minimum key node"<<endl;
    cout<<"3.Extract Minimum key node"<<endl;
    cout<<"4.Decrease key of a node"<<endl;
    cout<<"5.Delete a node"<<endl;
    cout<<"6.Display Heap"<<endl;
    cout<<"7.Find if a node exist in the heap"<<endl;
    cout<<"8.Exit"<<endl;
    cout<<"Enter Your Choice:";
    cin>>l;
	switch(l)
		{
		case 1:
		    cout<<"Enter key to be inserted:";
			cin>>n;
			num++;
			H=Insert(H,n);
			break;
		case 2:
			if(H==NULL)
				cout<<"Heap is empty"<<endl;
			else
				cout<<"Minimum key is:"<<H->data<<endl;
			break;
		case 3:
			if(H==NULL)
				cout<<"Heap is empty"<<endl;
			else
				{
				num--;
				cout<<"Minimum key is:"<<H->data<<endl;
				H=Extract_min(H,num);
				}
			break;
		case 4:
			cout<<"Enter key to be decreased:";
			cin>>n;
			p=Find(H,n);
			if(p==NULL)
	 			cout<<"Key not found"<<endl;
			else
				{
				cout<<"Enter new value:";
				cin>>m;
				if(m>=n)
					cout<<"New value is greater than equal to original value for the same key"<<endl;
				else
					H=Decrease_key(H,p,m);
				}
			break;
		case 5:
			cout<<"Enter key to be deleted:";
			cin>>n;
			p=Find(H,n);
			if(p==NULL)
				cout<<"Key not found"<<endl;
			else
                {
                num--;
				H=Delete_key(H,p,num);
                }
			break;
		case 6:
            if(H==NULL)
                cout<<"Heap is empty";
            else
                Display(H);
            cout<<endl;
			break;
        case 7:
            cout<<"Enter node to be searched:";
            cin>>n;
            p=Find(H,n);
            if(p==NULL)
                cout<<"Not found"<<endl;
            else
                cout<<"Found"<<endl;
            break;
		case 8:
			flag=1;
			break;
		}
	if(flag==1)
		break;
	}
}
