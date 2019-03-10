#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define print(x)     printf("%d ",x)
#define sprint(s)    printf("%s ",s);
#define forn(i,a,n)  for(int i=a;i<n;i++)

FILE *fp;
FILE *fo;

struct dynamic_array
{
  int size;
  int capacity;
  int *arr;
};

typedef struct dynamic_array dynamic_array;

dynamic_array* init()
{
  dynamic_array* vect=(dynamic_array*)malloc(sizeof(dynamic_array));
  vect->capacity=1;
  vect->size=0;

  vect->arr=(int*)malloc(sizeof(int));

  return vect;
}

int length(dynamic_array* vect)
{
  return vect->size;
}

dynamic_array* append(dynamic_array* vect,int x)
{
  if(vect->size==vect->capacity)
  {
    int *new_arr=(int*)malloc(sizeof(int)*(2*(vect->capacity)));

    forn(i,0,vect->size)
	new_arr[i]=vect->arr[i];

    vect->arr=new_arr;
    vect->capacity=2*vect->capacity;
 }

  vect->arr[vect->size]=x;
  vect->size++;

  return vect;	
}

dynamic_array* concatenate(dynamic_array* a,dynamic_array* b)
{
  forn(i,0,b->size)
  { 
    a=append(a,b->arr[i]);
  }
  
  return a;
}

void slice(dynamic_array* vect,int a,int b)
{
  if(b>=a && a>=1 && b<=vect->size)
  {
    forn(i,a-1,b)
    {
	if(i==(b-1)) fprintf(fo,"%d",vect->arr[i]);    
	else         fprintf(fo,"%d ",vect->arr[i]);
    }
   // fprintf(fo,"\n");
  }

  else
  {
    fprintf(fo,"INVALID RANGE\n");
  }

}

int member(dynamic_array* vect,int x)
{
   forn(i,0,vect->size)
   {
     if(vect->arr[i]==x)
	     return 1;
   }
  
   return 0;
}


int main()
{
  fp=fopen("input.txt","r");
  fo=fopen("output.txt","w");
  
  char ch;
  char *str;
  int i,j,n,num;

  while(fscanf(fp,"%c",&ch)!=EOF)
  {
     str=(char*)malloc(sizeof(char)*100);	  
     if(ch=='x')
	     break;

     else if(ch=='a')
     {
        fscanf(fp,"%[^\n]s",str);   
	dynamic_array *vect=init();

	n=strlen(str);
        
	for(i=2;i<n;i++)
	{
	    num=0;
	   while(!(str[i]==' ' || str[i]==')'))
	   { 
	     num=num*10;
	     num+=(str[i]-48);
	     i++;
             
	     if(str[i]==')') break;
	   }

         vect=append(vect,num);
	 if(str[i]==')') break;
	} 
	 i+=2;
         num=0;
	 for(;i<n;i++)
           num=num*10+(str[i]-48);
       	 vect=append(vect,num);

	 fprintf(fo,"(");
         slice(vect,1,vect->size);
	 fprintf(fo,")\n");
     }
    
     else if(ch=='c')
     {
       dynamic_array* vect1=init();
       dynamic_array* vect2=init();

       fscanf(fp,"%[^\n]s",str);
       n=strlen(str);
       
       for(i=2;i<n;i++)
       {
         num=0;

	 while(!(str[i]==' ' || str[i]==')'))
         {
	   num=num*10+(str[i]-48);
	   i++;
	 }
       	 vect1=append(vect1,num);
	 if(str[i]==')')
	 {
	    i+=3;
	    break;
	 } 
       }

       for(;i<n;i++)
       {
         num=0;
	 while(!(str[i]==' ' || str[i]==')'))
	{
	  num=num*10+(str[i]-48);
	  i++;
	}
      
	 vect2=append(vect2,num);
         if(str[i]==')')
		 break;
       }

       vect1=concatenate(vect1,vect2);

       fprintf(fo,"(");
       slice(vect1,1,vect1->size);
       fprintf(fo,")\n");
     }

     else if(ch=='m')
     {
        fscanf(fp,"%[^\n]s",str);   
	dynamic_array *vectm=init();

	n=strlen(str);
        for(i=2;i<n;i++)
	{
	    num=0;
	   while(!(str[i]==' ' || str[i]==')'))
	   { 
	     num=num*10;
	     num+=(str[i]-48);
	     i++;
             
	     if(str[i]==')') break;
	   }
         vectm=append(vectm,num);
	 if(str[i]==')') break;
	} 
	 i+=2;
         num=0;
	 for(;i<n;i++)
           num=num*10+(str[i]-48);
         
         fprintf(fo,"%d\n",member(vectm,num));         

     }

     else if(ch=='l')
     {
       fscanf(fp,"%[^\n]s",str);   
       dynamic_array *vectl=init();

	n=strlen(str);
        
	for(i=2;i<n;i++)
	{
	    num=0;
	   while(!(str[i]==' ' || str[i]==')'))
	   { 
	     num=num*10;
	     num+=(str[i]-48);
	     i++;
             
	     if(str[i]==')') break;
	   }

         vectl=append(vectl,num);
	 if(str[i]==')') break;
	} 
      
	fprintf(fo,"%d\n",length(vectl));
     
     }

     else if(ch=='s')
     {
       fscanf(fp,"%[^\n]s",str);   
	dynamic_array *vects=init();

	n=strlen(str);
        for(i=2;i<n;i++)
	{
	    num=0;
	   while(!(str[i]==' ' || str[i]==')'))
	   { 
	     num=num*10;
	     num+=(str[i]-48);
	     i++;
             
	     if(str[i]==')') break;
	   }
         vects=append(vects,num);
	 if(str[i]==')') break;
	} 
	 i+=2;
         int a=0;
	 for(;str[i]!=' ';i++)
           a=a*10+(str[i]-48);
         
	 i++;

	 int b=0;
	 for(;i<n;i++)
            b=b*10+(str[i]-48);
          
         slice(vects,a,b);
	 fprintf(fo,"\n");
     }

   }

  return 0;

}



