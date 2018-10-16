#include <bits/stdc++.h>
using namespace std;

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

void swap(int a,int b,int arr[])
{
int temp;
temp=arr[a];
arr[a]=arr[b];
arr[b]=temp;
}

void Insert(int arr[],int num,int *size)
{
if(*size==100000)
    {
    cout<<"Can't"<<endl;
    return ;
    }
*size+=1;
int i=*size;
arr[i]=num;
while(i>1&&arr[parent(i)]>arr[i])
    {
    swap(parent(i),i,arr);
    i=parent(i);
    }
return;
}

void Decrease(int arr[],int num,int x,int *size)
{
if(num>*size)
    {
    cout<<"Can't";
    return ;
    }
arr[num]=x;
int i=num;
while(i>1&&arr[parent(i)]>arr[i])
    {
    swap(parent(i),i,arr);
    i=parent(i);
    }
return;
}

void Heapify(int arr[],int *size,int i)
{
int l=left(i),r=right(i);
int smaller;
if(l<=*size&&arr[l]<arr[smaller])
    smaller=l;
if(r<=*size&&arr[r]<arr[smaller])
    smaller=r;
if(smaller!=i)
    {
    swap(i,smaller,arr);
    Heapify(arr,size,smaller);
    }
}

int Extract(int arr[],int *size)
{
int num=arr[1];
arr[1]=arr[*size];
*size-=1;
Heapify(arr,size,1);
return num;
}

void Delete(int arr[],int num,int *size)
{
if(num>*size)
    {
    cout<<"Can't";
    return;
    }
Decrease(arr,num,-100000,size);
int n=Extract(arr,size);
return;
}

void Display(int arr[],int *size)
{
int i;
for(i=1;i<=(*size);i++)
    cout<<arr[i]<<" ";
cout<<endl;
}

int main()
{
int n,x;
cout<<"Enter number of operations:";
cin>>n;
int size=0;
int a,num;
int arr[100001],i;
cout<<"1.Insert"<<endl;
cout<<"2.Delete"<<endl;
cout<<"3.Extract min"<<endl;
cout<<"4.Decrease key"<<endl;
cout<<"5.Display"<<endl;
for(i=0;i<n;i++)
    {
    cout<<"Enter:";
    cin>>a;
    switch(a)
        {
        case 1:
            cout<<"Enter key:";
            cin>>num;
            Insert(arr,num,&size);
            break;
        case 2:
            cout<<"Enter key:";
            cin>>num;
            Delete(arr,num,&size);
            break;
        case 3:
            cout<<"Minimum key:"<<Extract(arr,&size);
            break;
        case 4:
            cout<<"Enter key and value:";
            cin>>num>>x;
            Decrease(arr,num,x,&size);
            break;
        default:
            Display(arr,&size);
        }
    cout<<endl;
    cout<<"1.Insert"<<endl;
    cout<<"2.Delete"<<endl;
    cout<<"3.Extract min"<<endl;
    cout<<"4.Delete key"<<endl;
    cout<<"5.Decrease key"<<endl;
    cout<<"6.Display"<<endl;
    }

}
