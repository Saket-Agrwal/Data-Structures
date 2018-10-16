#include<bits/stdc++.h>
using namespace std;

long long int getMid(long long int s, long long int e) { return s + (e - s)/2; } 

void updateValueUtil(vector <long long int> &tree, long long int ss, long long int se, long long int i, long long int diff, long long int si) 
{ 
    if (i < ss || i > se) 
        return; 
    tree[si] = tree[si] + diff; 
    if (se != ss) 
    { 
        long long int mid = getMid(ss, se); 
        updateValueUtil(tree, ss, mid, i, diff, 2*si + 1); 
        updateValueUtil(tree, mid+1, se, i, diff, 2*si + 2); 
    } 
} 

void updateValue(vector <long long int> &vect, vector <long long int> &tree, long long int n, long long int i, long long int new_val) 
{ 
    long long int diff = new_val - vect[i]; 

    vect[i] = new_val; 

    updateValueUtil(tree, 0, n-1, i, diff, 0); 
} 

long long int getSumUtil(vector <long long int> &tree, long long int ss, long long int se, long long int qs, long long int qe, long long int si) 
{ 
    if (qs <= ss && qe >= se) 
        return tree[si]; 
    if (se < qs || ss > qe) 
        return 0; 
    long long int mid = getMid(ss, se); 
    return getSumUtil(tree, ss, mid, qs, qe, 2*si+1) + 
        getSumUtil(tree, mid+1, se, qs, qe, 2*si+2); 
}

long long int getSum(vector <long long int> &tree, long long int n, long long int qs, long long int qe) 
{ 
    return getSumUtil(tree, 0, n-1, qs, qe, 0); 
} 

long long int constructSTUtil(vector <long long int> &vect, long long int ss, long long int se, vector <long long int> &tree, long long int si) 
{ 
    if (ss == se) 
    { 
        tree[si] = vect[ss]; 
        return vect[ss]; 
    } 
    long long int mid = getMid(ss, se); 
    tree[si] = constructSTUtil(vect, ss, mid, tree, si*2+1) + 
            constructSTUtil(vect, mid+1, se, tree, si*2+2); 
    return tree[si]; 
} 

void constructST(vector <long long int> &vect, vector <long long int> &tree, long long int n) 
{ 
    constructSTUtil(vect, 0, n-1, tree, 0); 
} 

int main() 
{ 
    long long int t;
    cin>>t;
    while(t--)
    {
        long long int n,q;
        cin>>n>>q;
        string s;
        cin>>s;
        vector <vector <long long int> > vect;
        vector <vector <long long int> > tree;
        long long int x = (long long int)(ceil(log2(n))); 
        long long int max_size = 2*(long long int)pow(2, x) - 1; 

        for(long long int i=0;i<26;i++)
        {
            vector <long long int> vec(n,0);
            vect.push_back(vec);
            vector <long long int> vec2(max_size,0);
            tree.push_back(vec2);
        }
        for(long long int i=0;i<s.size();i++)
        {
            long long int x = s[i]-97;
            vect[x][i] = 1;  
        }

        for(long long int i=0;i<26;i++)
            constructST(vect[i],tree[i],n);

        while(q--)
        {
            long long int a;
            cin>>a;
            if(a==1)
            {
                long long int l,r,k;
                cin>>l>>r>>k;
                l--; r--;
                long long int arr[26];
                for(long long int i=0;i<26;i++)
                    arr[i] = getSum(tree[i], n, l, r);
                long long int ans = 0;
                for(long long int i=0;i<26;i++)
                {
                    if(i+k<26)
                    {
                        ans += arr[i]*arr[i+k];
                        ans = ans%1000000007;
                    }
                    else
                        break;
                }
                cout<<ans<<endl;
            }
            else
            {
                long long int id;
                char ch;
                cin>>id>>ch;
                id--;
                long long int x = s[id]-97;
                long long int y = ch-97;
                s[id] = ch;
                updateValue(vect[x], tree[x], n, id, 0);
                updateValue(vect[y], tree[y], n, id, 1);
            }
        }
    }
    return 0; 
} 