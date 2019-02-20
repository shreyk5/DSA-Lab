#include<stdio.h>
#include<stdlib.h>

#define print(x)     printf("%d ",x)
#define sprint(s)    printf("%s ",s);
#define forn(i,a,n)  for(int i=a;i<n;i++)

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
     print(vect->arr[i]);

    printf("\n");
  }

  else
  {
    printf("INVALID RANGE\n");
  }

}

int main()
{
  dynamic_array *vect=init();
  dynamic_array* vect2=init();

  forn(i,1,10)
	vect=append(vect,i);
  
  forn(i,20,24) vect2=append(vect2,i);

  slice(vect,1,9);
  vect=concatenate(vect,vect2);

  slice(vect,1,12);
  
  print(vect->size);
  print(vect2->size);

  return 0;

}



