#include<stdio.h>
#include<stdlib.h>

#define MAX 101
FILE *fp;
FILE *fo;
int *arr[MAX];
int power[20];
int n;

int* merge(int *a1,int n1,int *a2,int n2,int *b)
{
   //b=(int*)malloc(sizeof(int)*(n1+n2));

   int i=0,j=0,k=0;

   while(1)
   {
      if(j<=(n1-1) && k<=(n2-1)) 
      {
        if(a1[j]<=a2[k])
	   b[i++]=a1[j++];  
	 
        else
	   b[i++]=a2[k++];
      }      

      else if(j<=(n1-1))
       b[i++]=a1[j++];
     
      else if(k<=(n2-1))
       b[i++]=a2[k++];

      else break;
   }

   return b;
}

void insert(int x)
{
  int i=0;
  int *b[MAX];
  for(i=0;i<MAX;i++)
    b[i]=(int*)malloc(sizeof(int)*1000);

  i=0;
  b[0][0]=x;
  int num=n;
  while(num%2==1)
  {
    b[i+1]=merge(arr[i],power[i],b[i],power[i],b[i+1]);  
    num=num/2;
    i++;
  }

  arr[i]=b[i];

}

void print()
{
  int j=0,i=0;

  for(j=0;j<32;j++)
  {
    if(n&(1<<j))
    {
      for(i=0;i<power[j];i++)
	   fprintf(fo,"%d ",arr[j][i]);
    }
  }
  fprintf(fo,"\n");

}

void search(int x)
{
   int i=0,j=0;

   for(j=0;j<32;j++)
   {
     if(n&(1<<j))
     {
       int l=0,r=power[j]-1;

       while(l<r)
       {
         int mid=(l+r)/2;

	 if(arr[j][mid]==x)
         {
	   printf("%d ",mid);
	   break;
	 }
	 
	 else if(arr[j][mid]<x)
	     l=mid+1;

	 else 
             r=mid-1;
       }
     }
   
   }




}


int main()
{
  fp=fopen("input.txt","r");
  fo=fopen("output.txt","w");
  int i;
  char ch;

  for(i=0;i<MAX;i++) 
    arr[i]=(int*)malloc(sizeof(int)*1000);

  power[0]=1;
  
  for(i=1;i<10;i++)
   power[i]=2*power[i-1];
  	
  while(fscanf(fp,"%c",&ch)!=EOF)
  {
     if(ch=='x') break;

     else if(ch=='i') 
     {
	fscanf(fp,"%d",&i);
	insert(i);
	n++;
     }

     else if(ch=='p')
	print();

     else if(ch=='s')
     {
       fscanf(fp,"%d",&i);
       search(i);
     }	
      
  }


  return 0;
}

