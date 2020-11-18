#include<bits/stdc++.h>

using namespace std;
using namespace std::chrono; 


typedef struct node
{

       int key;
       node *parent;
       char color;
       node *left;
       node *right;
       int dup;
       vector<pair<int,int>> vtr_pair;
};
class RBtree
{

      node *root;
      node *q;


   public :
      RBtree()
      {
              q=NULL;
              root=NULL;
      }
      void insert(int x,int y ,int weight);
      void insertfix(node *);
      node* empty1();
      void leftrotate(node *);
      void rightrotate(node *);
      void erase(int start1,int end1 ,int weight);
      node* successor(node *);
      void delfix(node *);
      void disp();

      void display( node *);
      void find1(int weight,int vertex);
      node* extractmin();
};
void RBtree::insert(int x,int y ,int weight)
{

     int z,i=0;
     //cout<<"\nEnter key of the node to be inserted: ";
     //cin>>z;
     z=weight;
     node *p,*q;
     node *t=new node;


     t->key=z;
     t->left=NULL;
     t->right=NULL;
     t->color='r';
            t->dup=1;
            t->vtr_pair.clear();//
                              t->vtr_pair.push_back(make_pair(x,y));//

     p=root;
     q=NULL;


     if(root==NULL)
     {
           root=t;
           t->parent=NULL;

           

     }
     else
     {
         while(p!=NULL)
         {
              q=p;
              if(p->key<t->key)
                  p=p->right;
              else
                  p=p->left;
         }
        
         t->parent=q;
         if(q->key<t->key)
              q->right=t;
         else
              q->left=t;
     }
     insertfix(t);
}


void RBtree::insertfix(node *z)
{
if (z->parent != NULL && z->parent->parent != NULL)
{
while (z != NULL && z->parent != NULL &&
z->parent->parent != NULL && !z->parent->color == 'b')
// ass long as color is not black, thus red
{
if (z->parent == z->parent->parent->left)
{
node *y = z->parent->parent->right;
if (y != NULL && y->color == 'r')
{
z->parent->color = 'b';
y->color = 'b';
z->parent->parent->color = 'r';
z = z->parent->parent;
}
else if (z == z->parent->right)
{
z = z->parent;
leftrotate(z);
}
z->parent->color = 'b';
z->parent->parent->color = 'r';
rightrotate(z->parent->parent);

}
else
{

node *y = z->parent->parent->left; // left instead of right
if (y != NULL && y->color == 'r') // is red?
{
z->parent->color = 'b'; // color = black
y->color = 'b'; // color = black
z->parent->parent->color = 'r'; // color = red
z = z->parent->parent;
}
else
{
if (z == z->parent->left) // left instead of right
{
z = z->parent;
rightrotate(z);
}
z->parent->color = 'b'; // color is black
z->parent->parent->color = 'r'; // color is red
leftrotate(z->parent->parent);
}
}
}
}
}




void RBtree::erase(int start,int end,int weight)
{

     if(root==NULL)
     {
         //  cout<<"\nEmpty Tree." ;
           return ;
     }
     int x=weight;
     //cout<<"\nEnter the key of the node to be deleted: ";
     //cin>>x;
     node *p;
     p=root;
     node *y=NULL;
     node *q=NULL;
     int found=0;
     while(p!=NULL&&found==0)
     {
           if(p->key==x)
               found=1;
           if(found==0)
           {
                 if(p->key<x)
                    p=p->right;
                 else
                    p=p->left;
           }
     }
     if(found==0)
     {
          //  cout<<"\nElement Not Found.";
            return ;
     }
     else
     {
        // cout<<"\nDeleted Element: "<<p->key;
        // cout<<"\nColour: ";
         if(p->color=='b');
    // cout<<"Black\n";
    //else
    // cout<<"Red\n";

         if(p->parent!=NULL);
             //  cout<<"\nParent: "<<p->parent->key;
      //   else
             //  cout<<"\nThere is no parent of the node.  ";
         if(p->right!=NULL);
             //  cout<<"\nRight Child: "<<p->right->key;
        // else
             //  cout<<"\nThere is no right child of the node.  ";
         if(p->left!=NULL);
              // cout<<"\nLeft Child: "<<p->left->key;
         //else
              // cout<<"\nThere is no left child of the node.  ";
        // cout<<"\nNode Deleted.";
         if(p->left==NULL||p->right==NULL)
              y=p;
         else
              y=successor(p);
         if(y->left!=NULL)
              q=y->left;
         else
         {
              if(y->right!=NULL)
                   q=y->right;
              else
                   q=NULL;
         }
         if(q!=NULL)
              q->parent=y->parent;
         if(y->parent==NULL)
              root=q;
         else
         {
             if(y==y->parent->left)
                y->parent->left=q;
             else
                y->parent->right=q;
         }
         if(y!=p)
         {
             p->color=y->color;
             p->key=y->key;
         }
         if(y->color=='b')
             delfix(q);
     }


}

void RBtree::delfix(node *p)
{
    node *s;
    while(p!=root&&p->color=='b')
    {
          if(p->parent->left==p)
          {
                  s=p->parent->right;
                  if(s->color=='r')
                  {
                         s->color='b';
                         p->parent->color='r';
                         leftrotate(p->parent);
                         s=p->parent->right;
                  }
                  if(s->right->color=='b'&&s->left->color=='b')
                  {
                         s->color='r';
                         p=p->parent;
                  }
                  else
                  {
                      if(s->right->color=='b')
                      {
                             s->left->color=='b';
                             s->color='r';
                             rightrotate(s);
                             s=p->parent->right;
                      }
                      s->color=p->parent->color;
                      p->parent->color='b';
                      s->right->color='b';
                      leftrotate(p->parent);
                      p=root;
                  }
          }
          else
          {
                  s=p->parent->left;
                  if(s->color=='r')
                  {
                        s->color='b';
                        p->parent->color='r';
                        rightrotate(p->parent);
                        s=p->parent->left;
                  }
                  if(s->left->color=='b'&&s->right->color=='b')
                  {
                        s->color='r';
                        p=p->parent;
                  }
                  else
                  {
                        if(s->left->color=='b')
                        {
                              s->right->color='b';
                              s->color='r';
                              leftrotate(s);
                              s=p->parent->left;
                        }
                        s->color=p->parent->color;
                        p->parent->color='b';
                        s->left->color='b';
                        rightrotate(p->parent);
                        p=root;
                  }
          }
       p->color='b';
       root->color='b';
    }
}

node* RBtree::empty1()
{
    if(!root) return NULL;
    else return root;
}


void RBtree::leftrotate(node *p)
{
     if(p->right==NULL)
           return ;
     else
     {
           node *y=p->right;
           if(y->left!=NULL)
           {
                  p->right=y->left;
                  y->left->parent=p;
           }
           else
                  p->right=NULL;
           if(p->parent!=NULL)
                y->parent=p->parent;
           if(p->parent==NULL)
                root=y;
           else
           {
               if(p==p->parent->left)
                       p->parent->left=y;
               else
                       p->parent->right=y;
           }
           y->left=p;
           p->parent=y;
     }
}
void RBtree::rightrotate(node *p)
{
     if(p->left==NULL)
          return ;
     else
     {
         node *y=p->left;
         if(y->right!=NULL)
         {
                  p->left=y->right;
                  y->right->parent=p;
         }
         else
                 p->left=NULL;
         if(p->parent!=NULL)
                 y->parent=p->parent;
         if(p->parent==NULL)
               root=y;
         else
         {
             if(p==p->parent->left)
                   p->parent->left=y;
             else
                   p->parent->right=y;
         }
         y->right=p;
         p->parent=y;
     }
}

node* RBtree::successor(node *p)
{
      node *y=NULL;
     if(p->left!=NULL)
     {
         y=p->left;
         while(y->right!=NULL)
              y=y->right;
     }
     else
     {
         y=p->right;
         while(y->left!=NULL)
              y=y->left;
     }
     return y;
}

void RBtree::disp()
{
     display(root);
}
node* RBtree:: extractmin( )
{
     node* current=root;
     if(!current) return NULL;

    		 while(current->left!=NULL)
    {
        current=current->left;

    }
    return current;
}

void RBtree::display(node *p)
{
     if(root==NULL)
     {
          cout<<"\nEmpty Tree.";
          return ;
     }
     if(p!=NULL)
     {
                cout<<"\n\t NODE: ";
                cout<<"\n Key: "<<p->key;
                cout<<"\n Colour: ";
    if(p->color=='b')
     cout<<"Black";
    else
     cout<<"Red";
                if(p->parent!=NULL)
                       cout<<"\n Parent: "<<p->parent->key;
                else
                       cout<<"\n There is no parent of the node.  ";
                if(p->right!=NULL)
                       cout<<"\n Right Child: "<<p->right->key;
                else
                       cout<<"\n There is no right child of the node.  ";
                if(p->left!=NULL)
                       cout<<"\n Left Child: "<<p->left->key;
                else
                       cout<<"\n There is no left child of the node.  ";
                cout<<endl;
    if(p->left)
    {
                 cout<<"\n\nLeft:\n";
     display(p->left);
    }
    /*else
     cout<<"\nNo Left Child.\n";*/
    if(p->right)
    {
     cout<<"\n\nRight:\n";
                 display(p->right);
    }
    /*else
     cout<<"\nNo Right Child.\n"*/
     }
}
void RBtree::find1(int weight,int vertex)
{
     if(root==NULL)
     {
           cout<<"\nEmpty Tree\n" ;
           return  ;
     }
     int x=weight;
    //  cout<<"\n Enter key of the node to be searched: ";
    //  cin>>x;
     node *p=root;

     int found=0;
     while(p!=NULL&& found==0)
     {
            if(p->key==x)
                found=1;
            if(found==0)
            {
                 if(p->key<x)
                      p=p->right;
                 else
                      p=p->left;
            }
     }
     if(found==0)
          cout<<"\nElement Not Found.";
     else
     {
                cout<<"\n\t FOUND NODE: ";
                cout<<"\n Key: "<<p->key;
                cout<<"\n Colour: ";
    if(p->color=='b')
     cout<<"Black";
    else
     cout<<"Red";
                if(p->parent!=NULL)
                       cout<<"\n Parent: "<<p->parent->key;
                else
                       cout<<"\n There is no parent of the node.  ";
                if(p->right!=NULL)
                       cout<<"\n Right Child: "<<p->right->key;
                else
                       cout<<"\n There is no right child of the node.  ";
                if(p->left!=NULL)
                       cout<<"\n Left Child: "<<p->left->key;
                else
                       cout<<"\n There is no left child of the node.  ";
                cout<<endl;

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
    //node *root1=NULL;
    RBtree obj;
     obj.insert(0,0,0);
    int sum=0;

    while(count1!=n+1)
    {
            node *temp=obj.extractmin();//msmall(root1,1);

           int r=temp->vtr_pair[0].first;
           int s=temp->vtr_pair[0].second;
         //  cout<<"r:"<<r<<" "<<"s:"<<s<<" "<<"key"<<temp->key<<endl;
           bool flag=false;
           if(visited[r]==0)
           {
               int n1=v[r].size();
               for(i=0;i<n1;i++)
               {
                 if(visited[v[r][i].first]==0)
                 {
                     obj.insert(r,v[r][i].first,v[r][i].second);
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
                     obj.insert(s,v[s][i].first,v[s][i].second);
                 }
               }
               visited[s]=1;
               flag=true;

           }
           if(flag==true)
               {
                   sum=sum+temp->key;
                   count1++;
               }
           if(temp->dup>1)
           {
               temp->dup--;
               temp->vtr_pair.erase(temp->vtr_pair.begin());
           }
           else
           {
           obj.erase(r,s,temp->key);
           }
    }
    cout<<sum<<endl;
     auto stop = high_resolution_clock::now();

     auto duration = duration_cast<microseconds>(stop - vtr_pair);

     cout<< duration.count()<< endl;
    return 0;
}

