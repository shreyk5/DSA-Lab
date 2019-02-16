#include<stdio.h>
#include<stdlib.h>

const int inf=1e6;
const int MAX=1e6;

int min(int a,int b)
{
  if(a<b) return a;
  return b;

}

int build_tree(int *tree,int *a,int idx,int start,int end)
{
  if(start==end)  tree[idx]=a[start];

  else
  {
      int mid=(start+end)/2;
      tree[2*idx+1]=build_tree(tree,a,2*idx+1,start,mid);
      tree[2*idx+2]=build_tree(tree,a,2*idx+2,mid+1,end);
      tree[idx]=min(tree[2*idx+1],tree[2*idx+2]);  
  }
   
  return tree[idx];
}

void update(int *tree,int idx)
{
  
   tree[idx]=min(tree[2*idx+1],tree[2*idx+2]);
   if(idx==0) return;
   update(tree,idx/2);
}


int main()
{
  FILE *fp;
  FILE *fo;
  fp=fopen("input.txt","r");
  fo=fopen("output.txt","w");
  int n,i,j;  
  int a[MAX];
  char *ch=(char *)malloc(sizeof(char)*1000000);
  while(fscanf(fp," %[^\n]s",ch)!=EOF)
  {
    j=0;	   
    for(i=0;i<strlen(ch);i++)
    {
        n=0;
        while(i<strlen(ch)&&ch[i]!=' ')
       {
        n=n*10+ch[i]-48;
        i++;
       } 
      
      a[j++]=n;
    }

   n=j;
   int *tree=(int*)malloc(sizeof(int)*(2*n-1));
   if(n==1) fprintf(fo,"%d\n",a[0]);
   
   else
  {
   int ans;
   tree[0]=build_tree(tree,a,0,0,n-1);
   //for(int i=0;i<2*n-1;i++)
    //printf("%d ",tree[i]); 
    //printf("\n");
   
   if(tree[0]==tree[1])
   {
     if(tree[0]!=tree[3]) ans=tree[3];
     else                 ans=tree[4];
   }   
   
   else
   {
     if(tree[0]!=tree[5]) ans=tree[5];
     else                 ans=tree[6];
   }

   fprintf(fo,"%d\n",ans); 
   }
  }  
  return 0;
}

