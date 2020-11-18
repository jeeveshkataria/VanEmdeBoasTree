#include<iostream>
#include<math.h>
#include<bits/stdc++.h>
#define ll long long
using namespace std::chrono;


using namespace std;
struct VEB
{
    int universe;
    int min;
    int max;
    VEB *sum;
    VEB **cluster;
};
ll VEB_MAXIMUM(VEB *&V)
{
    return V->max;
}


ll VEB_MINIMUM(VEB *&V)
{
    return V->min;
}
void VEB_C(VEB *v, int size)
{
        v->universe = size;
        v->min= -1;
        v->max= -1;
	if (size == 2) 
	{
	    v->sum = NULL;
            v->cluster =NULL;

	}
else
{

        int k = (int)(sqrt(size));
	VEB *sum = new VEB;
	VEB_C(sum, k);
	v->sum = sum;
	VEB **temp =  (VEB**)malloc(k*sizeof(VEB));
	v->cluster = temp;
	for(int i =0; i < k; i++)
	{
		v->cluster[i] = (VEB *)malloc(sizeof(VEB));
		VEB_C(v->cluster[i], k);

        }
}
}
void insert(VEB *V,int size)
{
    if(V->min == -1)
	V->max=V->min=size;

else
{
    if(size < V->min)
    swap(size, V->min);
    if(V->universe > 2)
{
    int k = (int)sqrt(V->universe);
    VEB *t1=((V->cluster[(size/k)]));
if(t1->min == -1)
{
                insert(V->sum,(size/k));
                VEB *t2=V->cluster[(size/k)];
                t2->min=t2->max=size%k;
}
else
            insert(V->cluster[size/k], size%k);
}
if(size > V->max)
        V->max = size;
}
}

void print(VEB *V, int tabs)
{
if(V != NULL)
{
for(int i =0; i < tabs; ++i)
cout<<" ";
cout<<"SUMMARY: "<<V->universe<<" ( "<<V->min<<" , "<<V->max<<" ) "<<endl;
if(V->universe != 2)
print(V->sum, tabs + 1);
if(V->universe != 2)
{
for(int i =0; i <= tabs; ++i)
cout<<" ";
cout<<"CLUSTER: "<<V->universe<<endl;
int k = (int)sqrt(V->universe);
for(int i =0; i < k; ++i)
print(V->cluster[i], tabs + 1);
}
}

}
void delet(VEB *V ,ll key)
{
    ll cluster_size=(ll)sqrt(V->universe);
    if(V->min == V->max)
    {
        V->min = -1;
        V->max = -1;
    }
    else if ( V->universe == 2)
    {
        if(key == 0)
        {
            V->min = 1;
        }
        else
        {
            V->min=0;
        }
        V->max=V->min;

    }
    else
    {
        if ( key == V->min )
        {
            ll cluster_first=VEB_MINIMUM(V->sum);//check with modi for summary name
            key = cluster_first*cluster_size + VEB_MINIMUM(V->cluster[cluster_first]);
            V->min=key;

        }
        delet(V->cluster[key/cluster_size],key%cluster_size);

        if( VEB_MINIMUM(V->cluster[key/cluster_size]) == -1)
        {
            delet(V->sum, key/cluster_size);
            if(key == V->max)
            {
                ll summary_max = VEB_MAXIMUM(V->sum);
                if(summary_max == -1)
                    V->max = V->min;
                else
                    V->max = summary_max*cluster_size + VEB_MAXIMUM(V->cluster[summary_max]);


            }
        }
        else if( key == V->max )
            V->max = (key/cluster_size)*cluster_size + VEB_MAXIMUM(V->cluster[key/cluster_size]);

    }

}
int main()
{
   milliseconds mil(1000);
   mil = mil * 60;

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);   
    //freopen("outputvb.txt", "a", stdout);
	VEB *V = new VEB;
    VEB *head = V;
    VEB_C(head, 256);
   auto start = high_resolution_clock::now();
   int n,m,x;
    cin>>n>>m;
    vector<vector<pair<int,int>>> v1(100005);
    vector<vector<pair<int,int>>> v(100005);
    int visited[100005]={0};
    int w,y,i;
    v1[0].push_back({0,0});
    for(i=0;i<m;i++)
    {
        cin>>x>>y>>w;
        v[x].push_back(make_pair(y,w));
        v[y].push_back(make_pair(x,w));
    }
    int count1=1;
    insert(V,0);
    struct node *root1=NULL;
    int sum=0;
    while(count1!=n+1)
    {
           int temp=V->min;
           int r=v1[temp][0].first;
           int s=v1[temp][0].second;
           bool flag=false;
           if(visited[r]==0)
           {
               int n1=v[r].size();
               for(i=0;i<n1;i++)
               {
                 if(visited[v[r][i].first]==0)
                 {
                    v1[v[r][i].second].push_back(make_pair(r,v[r][i].first));
                    if(v1[v[r][i].second].size()==1)
                     insert(V, v[r][i].second);
                }
               }
               visited[r]=1;
               flag=true;
               
           }
           if(visited[s]==0)
           {
               int n1=v[s].size();
               for(i=0;i<n1;i++)
               {
                 if(visited[v[s][i].first]==0)
                 {
                    v1[v[s][i].second].push_back(make_pair(s,v[s][i].first));
                    if(v1[v[s][i].second].size()==1)
                    {
                    insert(V, v[s][i].second);
                    }
                 }
                 
               }
               visited[s]=1;
               flag=true;
           }
           if(flag==true)
        {
               sum=sum+temp;
            count1++;
        }
           v1[temp].erase(v1[temp].begin());
           if(v1[temp].size()==0);
          delet(V, temp);
    }
     cout<<sum<<endl;
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start); 
    cout<<duration.count()<<endl;
     std::cout << (mil.count() * milliseconds::period::num /
                               milliseconds::period::den);
	

    return 0;

}
