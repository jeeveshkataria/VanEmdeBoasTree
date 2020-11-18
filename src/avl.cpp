#include<bits/stdc++.h>
#include<iostream>
#include<string.h>
//#define debug(x) cout<<"Checkpoint : "<<x<<endl



 
using namespace std;
using namespace std::chrono; 
int count1=0;
struct node
{
    int data;
    struct node *left,*right;
    int height;
    struct node *parent;
    int kthindex;
    int duplicate;
    vector<pair<int,int>> vtr_pair;
};


int kcalculate(struct node *root)
{
    if(!root)
    return 0;
    else
    return root->kthindex;
}



int height(struct node *root)
{
    if(!root)
    return 0;
    else
    return root->height;
}

int balance_factor(struct node * root)
{
    int a,b;
    if(root->left!=NULL)
     a=root->left->height;
    else
      a=0;
    if(root->right!=NULL)
       b=root->right->height;
    else
        b=0;
    return a-b;
}



struct node* extractmin(struct node *root )
{
    struct node* current=root;
    while(current->left!=NULL)
    {
        current=current->left;

    }
    return current;
}



struct node* right_rotate(struct node *root)
{
        struct node *temp,*temp1;
        temp=root->left;
        temp1=root->left->right;
        temp->right=root;
        root->left=temp1;
       
     
      
      int left_h=root->left?root->left->height:0;
      int right_h=root->right?root->right->height:0;
      root->height=((left_h>right_h) ? left_h : right_h )+1;
      
      
      int left_k=root->left?root->left->kthindex:0;
      int right_k=root->right?root->right->kthindex:0;
      root->kthindex=left_k+right_k+1;
      
      
      
     
      
      
      int temp_left_h=temp->left?temp->left->height:0;
      int temp_right_h=temp->right?temp->right->height:0;
      temp->height=(temp_left_h>temp_right_h?temp_left_h:temp_right_h)+1;
      
      
      
      
      
      
      
      int temp_left_k=temp->left?temp->left->kthindex:0;
      int temp_right_k=temp->right?temp->right->kthindex:0;
      temp->kthindex=temp_left_k+temp_right_k+1;
      
      
      return temp;
}
 
struct node* left_rotate(struct node *root)
{
        struct node *temp,*temp1;
        temp=root->right;
        temp1=root->right->left;
        temp->left=root;
        root->right=temp1;



        int left_h=root->left?root->left->height:0;
      int right_h=root->right?root->right->height:0;
      root->height=((left_h>right_h) ? left_h : right_h )+1;



  
          int left_k=root->left?root->left->kthindex:0;
      int right_k=root->right?root->right->kthindex:0;
      root->kthindex=left_k+right_k+1;



int temp_left_h=temp->left?temp->left->height:0;
      int temp_right_h=temp->right?temp->right->height:0;
      temp->height=(temp_left_h>temp_right_h?temp_left_h:temp_right_h)+1;
      
      

     int temp_left_k=temp->left?temp->left->kthindex:0;
      int temp_right_k=temp->right?temp->right->kthindex:0;
      temp->kthindex=temp_left_k+temp_right_k+1;
      
     
        return temp;
}

struct node* insert(struct node *root,int x,int y,int value)
{
 
    if(root==NULL)
    {
        struct node *temp;
    temp= new node;
    temp->data=value;
    temp->left=NULL;
    temp->right=NULL;
    temp->height=1;
    temp->kthindex=1;
         temp->vtr_pair.clear();
        temp->vtr_pair.push_back(make_pair(x,y));
         temp->duplicate=1;
        return temp;
    }
    if(value==root->data)
    {
        root->vtr_pair.push_back(make_pair(x,y));
        root->duplicate+=1;
    }
    else if(value<root->data)
           { 
               root->left=insert(root->left,x,y,value);
               root->left->parent=root;
           }
    else
        {
            root->right=insert(root->right,x,y,value);
            root->right->parent=root;
        }
    
    root->height=max(height(root->left),height(root->right))+1;
    root->kthindex=kcalculate(root->left)+kcalculate(root->right)+1;
    int lh=height(root->left);
    int rh=height(root->right);
    if(lh-rh>1)
    {
       
       int ll=balance_factor(root->left);
       if(ll>=0)
       {
              return right_rotate(root);
       }
       else
       {
             root->left=left_rotate(root->left);
             root->left->parent=root;
             return right_rotate(root);
       }
    }
    if(rh-lh>1)
    {
       
       int ll=balance_factor(root->right);
       if(ll>=0)
       {
               root->right=right_rotate(root->right);
               root->right->parent=root;
             return left_rotate(root);
       }
       else
       {
           return left_rotate(root); 
       }
    }
    return root;
   
 }

 
struct node * inorder_successor(struct node* root)
{
    struct node* temp=root;
    while (temp->left)
        temp = temp->left;
 
    return temp;
}
 
struct node* delete1(struct node* root,int start1,int end1, int value)
{
 
    if (!root)
    {
        return root;
    }
    else if ( value < root->data )
        root->left = delete1(root->left,start1,end1,value);
    else if( value > root->data )
        root->right = delete1(root->right,start1,end1,value);
    else
    {
        if( (root->left == NULL) || (root->right == NULL) )
        {
           struct node *temp;
          if(root->left==NULL&&root->right==NULL)
          temp=NULL;
          else if(root->left!=NULL)
          temp=root->left;
          else
          temp=root->right;
 
            if (!temp)
            {
                temp = root;
                root = NULL;
            }
            else 
             *root = *temp; 
            free(temp);
        }
        else
        {
            struct node* temp = inorder_successor(root->right);
             root->data = temp->data;
             root->vtr_pair.clear();
             for(int i=0;i<temp->duplicate;i++)
             {
                 root->vtr_pair.push_back(temp->vtr_pair[i]);
             }
            root->duplicate=temp->duplicate;
            root->right = delete1(root->right,start1,end1,temp->data);
        }
    }
 
    if (!root)
      return root;
    
 
root->height=max(height(root->left),height(root->right))+1;
    root->kthindex=kcalculate(root->left)+kcalculate(root->right)+1;
    int lh=height(root->left);
    int rh=height(root->right);
  if(lh-rh>1)
  {
       
       int l1=balance_factor(root->left);
       if(l1>=0)
       {
              return right_rotate(root);
       }
       else
       {
             root->left=left_rotate(root->left);
             root->left->parent=root;
             return right_rotate(root);
       }
  }
  if(rh-lh>1)
  {
       
       int l1=balance_factor(root->right);
       if(l1>=0)
       {
               root->right=right_rotate(root->right);
               root->right->parent=root;
             return left_rotate(root);
       }
       else
       {
           return left_rotate(root); 
       }
  }
  return root;
   
 }
 
struct node* msmall(struct node *root,int y)
{
    int t=kcalculate(root->left);
   if(t==y-1)
   return root;
   else if(t>y-1)
   {
   return msmall(root->left,y);
   }
   else
   {
   return msmall(root->right,y-(t)-1);
   }
   
   
}
int main()
{
    // freopen("outputavl.txt", "a", stdout);
    auto vtr_pair = high_resolution_clock::now(); 
    int n,m,x;
    cin>>n>>m;
    vector<vector<pair<int,int>>> v(100005);
    int visited[100005]={0};
    int w,y,i;
    for(i=0;i<m;i++)
    {
        cin>>x>>y>>w;
        --x;
        --y;
        v[x].push_back(make_pair(y,w));
        v[y].push_back(make_pair(x,w));
    }
    int count1=1;
     struct node *root1=NULL;
     root1=insert(root1,0,0,0);
    int sum=0;
 
    while(count1!=n+1)
    {
           struct node *temp=extractmin(root1);//msmall(root1,1);
           int r=temp->vtr_pair[0].first;
           int s=temp->vtr_pair[0].second;
           
           bool flag=false;
           if(visited[r]==0)
           {
               int n1=v[r].size();
               for(i=0;i<n1;i++)
               {
                 if(visited[v[r][i].first]==0)
                 {
                     root1=insert(root1,r,v[r][i].first,v[r][i].second);
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
                     root1=insert(root1,s,v[s][i].first,v[s][i].second);
                 }
               }
               visited[s]=1;
               flag=true;
               
           }
           if(flag==true)
               {
                   sum=sum+temp->data;
                   count1++;
               }
           if(temp->duplicate>1)
           {
               temp->duplicate--;
               temp->vtr_pair.erase(temp->vtr_pair.begin());
           }
           else
           {
           root1=delete1(root1,r,s,temp->data);
           }
    }
    cout<<sum<<endl;
     auto stop = high_resolution_clock::now(); 
  
     auto duration = duration_cast<microseconds>(stop - vtr_pair); 
    
     cout<< duration.count()<< endl; 
    return 0;
}
