#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const int N=1e5;

int min(int a,int b)
{
    if(a<=b) return a;
    return b;
}

int max(int a,int b)
{
    if(a>=b) return a;
    return b;
}

struct node
{
   int data;
   int height;
   struct node *left;
   struct node *right;
   struct node *p;  // parent node
};

struct binaryTree
{
    struct node* root;

};

struct binaryTree* new_tree()
{
    struct binaryTree* tree=(struct binaryTree*)malloc(sizeof(struct binaryTree));
    tree->root=NULL;
    return tree;
}

int findIndex(char *a,int i)
{
    int count=0;
    int flag=0;
    int j;

    for(j=i;j<strlen(a);j++)
    {
       if(flag&&count==0)
            break;

       if(a[j]=='(')
       {
           flag=1;
           count++;
       }
        else if(a[j]==')')
         count--;
    }
    return j-1;
}

int number(char *a,int i)
{
    int num=0;
    int j;
    for(j=i;j<strlen(a);j++)
    {
        if(a[j]=='('||a[j]==')')
            break;
        num=num*10+(a[j]-48);
    }
    return num;
}

struct node* construct(int i,char *a,struct node* root)
{
    if(a[i]==')') return NULL;

    else
    {
       struct node* new_node=(struct node*)malloc(sizeof(struct node));
       new_node->data=number(a,i);
       new_node->height=-2;
       new_node->left=NULL;
       new_node->right=NULL;
       root=new_node;

       int idx=findIndex(a,i);

       root->left=construct(i+log10(new_node->data)+2,a,root->left);
       root->right=construct(idx+2,a,root->right);

       if(root->left) root->left->p=root;
       if(root->right) root->right->p=root;

       return root;
    }
}

void mirror(struct node* root)
{
  if(root==NULL) return;
  else
  {
      mirror(root->left);
      mirror(root->right);

      struct node* temp=(struct node*)malloc(sizeof(struct node));
      temp=root->left;
      root->left=root->right;
      root->right=temp;
  }

}

void preorder(struct node* root)
{
    if(root!=NULL)
    {
     printf("%d",root->data);
     printf("(");
     preorder(root->left);
     printf(")");
     printf("(");
     preorder(root->right);
     printf(")");
    }

}

int main()
{
    //char *s=(char *)malloc(sizeof(char)*100000);
    char ch;
    int j,i;
    struct binaryTree* tree=new_tree();
    while(1)
    {
     scanf("%c",&ch);

     if(ch=='c')
     {  
       j=0;
       char *a=(char*)malloc(sizeof(char)*10000);
       
       scanf(" %[^\n]s",a);  
       //printf("hi"); 
       //printf("%s",a);
       char *s=(char*)malloc(sizeof(char)*10000);
       
      for(i=0;i<strlen(a);i++)
      {
        if(a[i]!=' ')
        s[j++]=a[i];
      }
      
       tree->root=construct(1,s,tree->root);
 
     }
     else if(ch=='p')
     {
         printf("(");
         preorder(tree->root);
         printf(")");
     }

     else if(ch=='m')
     {
         
         mirror(tree->root);
         printf("(");
         preorder(tree->root);
         printf(")");
     }

     else if(ch=='s') break;

    }
    return 0;
}
