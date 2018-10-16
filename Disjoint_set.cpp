#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007

long long int C = 0;
long long int P = 1;
long long int H = 0;
long long int size = 1;
bool prime[100001];

bool isprime(long long int x)
{
    return prime[x];
}

void SieveOfEratosthenes() 
{  
    memset(prime, true, sizeof(prime)); 
    long long int n = 100000;
    prime[1] = false;
    for (long long int p=2; p*p<=n; p++) 
    { 
        if (prime[p] == true) 
        { 
            for (long long int i=p*2; i<=n; i += p) 
                prime[i] = false; 
        } 
    } 
} 

long long int root (long long int parent[] ,long long int i)
{
    if(i==parent[i])
        return i;
    parent[i] = root(parent,parent[i]);
    return parent[i];
}

void initialize(long long int parent[], long long int rank[],long long int maxi[],long long int arr[], long long int N)
{
    for(long long int i=0;i<N;i++)
    {
        parent[i] = i ;
        rank[i] = 1;
        maxi[i] = arr[i];
    }
}

long long int inverse(long long int a,long long int b)
{
    if(b==0)
        return 1;
    if(b%2)
    {
        long long int x = inverse(a,b/2);
        long long int ans = (x*x)%mod;
        ans = (ans*a)%mod;
        return ans;
    }
    else
    {
        long long int x = inverse(a,b/2);
        long long int ans = (x*x)%mod;
        return ans;
    }
}

void weight_union(long long int parent[],long long int rank[],long long int maxi[],long long int A,long long int B)
{
    long long int root_A = root(parent,A);
    long long int root_B = root(parent,B);

    if(root_A == root_B)
        return;
    if(isprime(rank[root_A]))
        C--;

    P = (P*inverse(rank[root_A],mod-2) )%mod;

    if(isprime(rank[root_B]))
        C--;

    P = (P*inverse(rank[root_B],mod-2) )%mod;
    
    if(rank[root_A] < rank[root_B])
    {
        parent[ root_A ] = parent[root_B];
        rank[root_B] += rank[root_A];
        maxi[root_B] = max(maxi[root_B],maxi[root_A]);

        long long int x = rank[root_B];
        long long int y = maxi[root_B];

        if(x==size)
            H = max(H,y);
        else if(x>size)
        {
            size = x;
            H = y;
        }

        if(isprime(rank[root_B]))
            C++;

        P = (P*rank[root_B])%mod;
    }
    else
    {
        parent[ root_B ] = parent[root_A];
        rank[root_A] += rank[root_B];
        maxi[root_A] = max(maxi[root_B],maxi[root_A]);

        long long int x = rank[root_A];
        long long int y = maxi[root_A];

        if(x==size)
            H = max(H,y);
        else if(x>size)
        {
            size = x;
            H = y;
        }

        if(isprime(rank[root_A]))
            C++;

        P = (P*rank[root_A])%mod;
    }
}

int main() 
{ 
    SieveOfEratosthenes();
    long long int t;
    cin>>t;
    while(t--)
    {
        long long int n,q;
        cin>>n>>q;
        long long int arr[n];
        C = 0;
        P = 1;
        size = 1;
        for(long long int i=0;i<n;i++)
        {
            cin>>arr[i];
            H = max(H,arr[i]);
        }
        long long int parent[n],rank[n],maxi[n];
        initialize(parent,rank,maxi,arr,n);
        while(q--)
        {
            long long int a,b;
            cin>>a>>b;
            a--;b--;
            weight_union(parent,rank,maxi,a,b);
            cout<<H<<" "<<C<<" "<<P<<endl;
        }
    }
    return 0; 
} 