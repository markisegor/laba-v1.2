#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <cstdlib>

struct DataBase 
{
    void* matrix_1;
    void* matrix_2;
    void* matrix_3;
	int size; 
    int type; 
};
struct DataBase db;
bool iden=true;
void vvod_int(void *a)
{
	scanf("%d",(int*)a);
}
void vvod_double(void *a)
{
	scanf("%lf",(double*)a);
}
void vvod_complex(void *a)
{
	scanf("%d", (int*)a);
}
void* start(int type, int c) 
{
    int i;
    void* a = calloc(db.size*db.size,db.type);
    void (*fptr [])(void *)={NULL, vvod_int, vvod_double, vvod_complex};
    if (c == 'n' || c == 'N')
	{
    	if (iden)
    	printf ("Enter matrix A:\n");
    	else
    	printf("Enter matrix B:\n");
        for (i = 0; i < db.size*db.size; i++) 
		{  
			if (type==3)
			{
				if (iden)
		    	printf("Real_a[%d][%d] = ", i/db.size+1, i%db.size+1);
		    	else
		    	printf("Real_b[%d][%d] = ", i/db.size+1, i%db.size+1);
		    	fptr[type](a+i*db.type);
		    	if (iden)
		    	printf("Imaginary_a[%d][%d] = ", i/db.size+1, i%db.size+1);
		    	else
		    	printf("Imaginary_b[%d][%d] = ", i/db.size+1, i%db.size+1);
		    	fptr[type](a+i*db.type+db.type/2);
		    } 
			else 
			{
				   	   
				if (iden)
		    	printf("a[%d][%d] = ", i/db.size+1, i%db.size+1);
		    	else
		    	printf("b[%d][%d] = ", i/db.size+1, i%db.size+1); 	
		       	fptr[type](a+i*db.type);
			}//вызывает из массива указателей функцию с номером type    
        }
        printf("\n");
    }
    if(c=='y'||c=='Y')
    {
    	 for (i = 0; i < db.size*db.size; i++) 
		 {
            if (type != 3) 
			{
                printf("a[%d][%d] = ", i/db.size+1, i%db.size+1);
                if (type == 1) 
				{
                    *((int*)a+i) = rand() % 100;
                    printf("%d\n", *((int*)a+i));
                }
                else if (type == 2) 
				{
                    *((double*)a+i) = ((double)(rand() % 100000))/1000;
                    printf("%f\n", *((double*)a+i));
                }
            }
            else 
			{
                if (i%db.size == 0)
                    printf("\n");
                *((int*)a+i*2) = rand() % 100;
                *((int*)a+i*2+1) = rand() % 100;
                printf("%10d + %di", *((int*)a+i*2), *((int*)a+i*2+1));
            }
        }
        printf("\n");
	}
     iden=!iden;
     return a;
}
void vivod_int(void *a)
{
	printf("%5d", *(int*)a);
}
void vivod_double(void *a)
{
		printf("%5f    ", *((double*)a));
}
void vivod_complex(void *a)
{
	printf("%10d ", *((int*)a));
	a+=db.type/2;
	printf("+ %di" , *((int*)a));
}
void vivod(void *a,int type) 
{
    int i, j;
    void (*fptr [])(void *)={NULL, vivod_int, vivod_double, vivod_complex};
    for (i = 0; i < db.size; i++) {
        for (j = 0; j < db.size; j++) 
            fptr[type](a+i*db.type*db.size+j*db.type);//вызывает из массива указателей функцию с номером type
        printf("\n");
        }
        printf("\n");
    
    printf("\n");
}
void sum_int(void*a, void*b, void*c)
{
	*((int*)c)=*((int*)a)+*((int*)b);
}
void sum_double(void*a, void*b, void*c)
{
	*(double*)c=*(double*)a+*(double*)b;
}

void sum_complex(void*a, void*b, void*c)
{
 	*((int*)c)=*((int*)a)+*((int*)b);
 	a+=db.type/2;
 	b+=db.type/2;
 	c+=db.type/2;
 	*((int*)c)=*((int*)a)+*((int*)b);
}

void* sum(void *a, void *b, int type)
{
	int i;
	int j;
	void* c = calloc(db.size*db.size,db.type);
	void (*fptr[])(void *,void *, void *)={NULL,sum_int,sum_double, sum_complex};
	for (i = 0; i < db.size*db.size; i++) 
		fptr[type](a+i*db.type,b+i*db.type,c+i*db.type);	
	return c;
}
void mult_int(void*a, void*b, void*c)
{
	*((int*)c)+=*((int*)a)**((int*)b);
}
void mult_double(void*a, void*b, void*c)
{
	*((double*)c)+=*((double*)a)**((double*)b);	
}
void mult_complex(void*a, void*b, void*c)
{
	void* c1=c;
	void* a1=a;
	void* b1=b;
	a1+=db.type/2;
	b1+=db.type/2;
	c1+=db.type/2;
	*((int*)c)+=*((int*)a)**((int*)b)-*((int*)a1)**((int*)b1);
	*((int*)c1)+=*((int*)a)**((int*)b1)+*((int*)a1)**((int*)b);
	
}
void* mult(void* a, void* b, int type)
{	
	int i,j,k;
	void* c = calloc(db.size*db.size,db.type);
	void (*fptr[])(void *,void *, void *)={NULL,mult_int,mult_double, mult_complex};
	
	for(i = 0; i < db.size; i++)
    for(j = 0; j < db.size; j++)
    {
        for(k = 0; k < db.size; k++)
        fptr[type](a+i*db.type*db.size+k*db.type,b+k*db.type*db.size+j*db.type,c+i*db.size*db.type+j*db.type); 
    }
	
	return c;
}
void vvod_int1(void *a,int b)
{
	*((int *)a)=b;
}
void vvod_double1(void *a,double b)
{
	*((double *)a)=b;
}

int srav_int(void *a,int b)
{
	if (*((int *)a)!=b)
	return 1;
	else 
	return 0;
}
int srav_double(void *a,double b)
{
	if (fabs(*((double *)a)-b)>0.0000001)
	return 1;
	else 
	return 0;
}

int Test(int type)
{
	int i;
	 int *s;
	   int a[4]={1,2,3,4};
	     int b[4]={5,6,7,8};
	     int c[4]={6,8,10,12};
	     int d[4]={19,22,43,50};
	  double a1[4]={1.1,2.2,3.3,4.4};
	     double b1[4]={5.5,6.6,7.7,8.8};
	     double c1[4]={6.6,8.8,11.0,13.2};
	     double d1[4]={22.99,26.62,52.03,60.5};
	  db.size=2;
	  db.matrix_1 = calloc(db.size*db.size,db.type);
	     	db.matrix_2 = calloc(db.size*db.size,db.type);
		if (type == 1)
		{
	 		    for (i=0;i<db.size*db.size;i++)
				vvod_int1(db.matrix_1+i*db.type,a[i]);
				for (i=0;i<db.size*db.size;i++)
				vvod_int1(db.matrix_2+i*db.type,b[i]);
				db.matrix_3=sum(db.matrix_1,db.matrix_2,type);
			for (i=0;i<db.size*db.size;i++)
			{
				if(srav_int(db.matrix_3+i*db.type,c[i]))
				return 1;
				}	
				free(db.matrix_3);
			    db.matrix_3=	mult(db.matrix_1,db.matrix_2,type);
					for (i=0;i<db.size*db.size;i++)
			{
				if(srav_int(db.matrix_3+i*db.type,d[i]))
				return 2;
				}
	    }
	    else if (type == 2)
	    {
	     for (i=0;i<db.size*db.size;i++)
				vvod_double1(db.matrix_1+i*db.type,a1[i]);
				for (i=0;i<db.size*db.size;i++)
				vvod_double1(db.matrix_2+i*db.type,b1[i]);
				db.matrix_3=sum(db.matrix_1,db.matrix_2,type);
			
			for (i=0;i<db.size*db.size;i++)
			{
				if(srav_double(db.matrix_3+i*db.type,c1[i]))
				return 1;
				}	
				free(db.matrix_3);
			    db.matrix_3=	mult(db.matrix_1,db.matrix_2,type);
					for (i=0;i<db.size*db.size;i++)
			{
				if(srav_double(db.matrix_3+i*db.type,d1[i]))
				return 2;
				}
	    }
	    else if (type == 3)
	    {
	    int a2[8]={1,2,3,4,5,6,7,8};
	    int b2[8]={3,2,5,4,5,1,2,3};
	    int c2[8]={4,4,8,8,10,7,9,11};
	    int d2[8]={10,31,-9,31,30,75,-9,87};
	    for (i=0;i<db.size*db.size;i++)
	    {
				vvod_int1(db.matrix_1+i*db.type,a2[i*2]);
				vvod_int1(db.matrix_1+i*db.type+db.type/2,a2[i*2+1]);
			}
				for (i=0;i<db.size*db.size;i++)
	    {
				vvod_int1(db.matrix_2+i*db.type,b2[i*2]);
				vvod_int1(db.matrix_2+i*db.type+db.type/2,b2[i*2+1]);
			}
				db.matrix_3=sum(db.matrix_1,db.matrix_2,type);
				for (i=0;i<db.size*db.size;i++)
			{
				if(srav_int(db.matrix_3+i*db.type,c2[i*2])||srav_int(db.matrix_3+i*db.type+db.type/2,c2[i*2+1]))
				return 1;
				}
					free(db.matrix_3);
			db.matrix_3=	mult(db.matrix_1,db.matrix_2,type);
					for (i=0;i<db.size*db.size;i++)
			{
				if(srav_int(db.matrix_3+i*db.type,d2[i*2])||srav_int(db.matrix_3+i*db.type+db.type/2,d2[i*2+1]))
				return 2;
				}	
		}		
return 0;
}
int main()
{
	system("color 71");	
    char c; 
    int type;
	int res; 
    printf("Choose data type\n");
	printf("1.Integer\n2.Double\n3.Complex\n");
	scanf("%d", &type);
	scanf("%*c");
	if (type == 1)
	        db.type = sizeof(int);
	    else if (type == 2)
	        db.type = sizeof(double);
	    else if (type == 3)
	        db.type = 2*sizeof(int);
    printf("Start test? (Y/N)\n");
    scanf("%c" , &c);
    scanf("%*c");
    if (c == 'Y' || c  == 'y') 
	{           
        res= Test(type);   
        	if (res==0)
		printf("Ok"); 
		if (res==1)
		printf("Error in adding");  
		if (res==2)
		printf("Error in multyplying"); 
		free(db.matrix_1);
			free(db.matrix_2);
			free(db.matrix_3);         
    }  
    else if (c == 'N' || c == 'n') 
	{

	        printf("Enter size of matrix:\n");
	        scanf("%d", &db.size);
	        printf("Would you like to generate values? (Y/N)\n");
	        scanf("%*c");
	        scanf("%c", &c);
	        db.matrix_1 = start(type,c);
	        db.matrix_2 = start(type,c);
	        db.matrix_3=sum(db.matrix_1, db.matrix_2,type);
	        printf("Adding result\n");
			vivod(db.matrix_1,type);
			vivod(db.matrix_2,type); 
			printf("Adding result\n"); 
			vivod(db.matrix_3,type);  
			free(db.matrix_3);
			db.matrix_3=mult(db.matrix_1, db.matrix_2,type);
			printf("Multyplying result\n");
			vivod(db.matrix_3,type); 
			free(db.matrix_1);
			free(db.matrix_2);
			free(db.matrix_3);
	}
    return 0;
}
