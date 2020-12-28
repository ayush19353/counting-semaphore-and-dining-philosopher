/*
Ayush Mahant
2019353

*/


#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

int k;
void *func(void* n);

pthread_t ph[1000];//value of k should be let to under 1000 for the codee
pthread_mutex_t a1;

typedef struct mystruct//struct made of name my_semaphore
{
	pthread_cond_t cv;//it puts a condition wait to thread on availabilty of semapohre locks
	pthread_mutex_t mutex;//mutex ensures synchronization to the shared variable 
	int f;//counting semaphore initialzies with this value
	
}my_semaphore;




my_semaphore* bowl;
my_semaphore** forks;

void my_semaphore_init(my_semaphore **s)
{
	*s=(my_semaphore *) malloc(sizeof(my_semaphore));
	pthread_mutex_init(&((*s)->mutex),NULL);
	pthread_cond_init(&((*s)->cv),NULL);

(*s)->f=1;
}

void signalprint(my_semaphore* printValue)//this would print the signal state of the semaphore if it is acquired or free
{ pthread_mutex_lock(&(printValue->mutex));

	printf("%d\n", (printValue->f));//printf("%s\n","RRRHRHRRH");
	       pthread_mutex_unlock(&(printValue->mutex));

}


void wait(my_semaphore *s)
{
        pthread_mutex_lock(&(s->mutex));//here we try to get an acees to s->f
        s->f--;
        if(s->f < 0) {
 pthread_cond_wait(&(s->cv),&(s->mutex));//her ethe current thread would be block on s->cv 
       
        }

        pthread_mutex_unlock(&(s->mutex));//wher we unlock the s-> mutex such tat other threads can get access to bowl and forks 


}

void signal(my_semaphore *s)// 
{
 pthread_mutex_lock(&(s->mutex));//here we try to get an acees to s->f
        s->f++;
       if(s->f <= 0) {
    pthread_cond_signal(&(s->cv));//it would signal the blocked thread to restart only if it is in blocked state
     }
        pthread_mutex_unlock(&(s->mutex));//wher we unlock the s-> mutex such tat other threads can get access to bowl and forks 
}

//ignore
void de(int gg)//fucntion for error reporting if any
{if(gg!=0)
{
printf("%s\n"," destroyed mutex \n");
exit(1);
}}

void big(int d)//function for errror reporting if any
{if(d!=0)
{
printf("%s \n"," creation of threads failed \n");
exit(1);
}}
//ognore

void initize(int ff)
{
	//for(int i=0;i<2;i++)
	my_semaphore_init(&bowl);// calling fuction which would then initialize the bowl semaphore 
int i=0;
while(i<k)
	{//printf("%d\n",i );
		my_semaphore_init(&forks[i]);//calling function which would then initialze the forks semaphores
		i++;
	}
}

int main()
{
			// printf("hello\n");
			int i;
			void *message;
			int kp;
			scanf("%d", &k);//taking input of k for number of philosophers and forks
			int filo[k]; 

			forks= (my_semaphore **) malloc(k*sizeof(my_semaphore));//initiating malloc for allocatig size to the semophore forks
			// printf("before initize\n");
			initize(0);//calling function to initialize the bowl and forks semaphore


				for(int i=0;i<k;i++)

			{
				filo[i]=i;
			kp=pthread_create(&ph[i],NULL,(void *)func,(void *) &filo[i]);//creating threads of philosopher nad thus sending the function to eat using forks and bowl through func function
			big(kp);// for error reporting

			//printf("%d\n",i );
			}
			i=0;
			while(i<k)
			{
			kp=pthread_join(ph[i],&message);// pthread join for philosophers
			de(kp);
			i++;

			}
			free(forks);//freeeing the allocated malloc
			//free(bowl);

			return 0;
}
void *func(void* n1)
		{
					int n= *(int *) n1;
					//printf("\n %s \n ","-----------");
					int dd=0;
					while(1)
					{
						dd++;
				printf("Philiosopher %d is going to pick up bowl\n",n+1);
				wait(bowl);
				printf("Philiosopher %d is aboutn to pick up forks %d and %d\n",n+1,n+1,(n+1)%k +1);
				wait(forks[n]);
				wait(forks[(n+1)%k]);
				printf("%s\n","----------------------------------" );
				printf("Philiosopher %d is eating using forks %d and %d ,and has the bowl \n",n+1,n+1,(n+1)%k +1);
			printf("%s\n", "-------------------------------------");
			//	printf("%s%d %s%d %s%d\n ","--p",n+1,"-f",(n+1),"-f",(n+1)%k+1 );
				printf("Philiosopher %d has kept forks %d and %d\n",n+1,n+1,(n+1)%k +1);
		//signalprint(forks[n]);
			

				signal(forks[(n+1)%k ]);
	//signalprint(forks[(n+1)%k ]);
				signal(forks[n]);
			//	signalprint(forks[n]);
				printf("Philiosopher %d kept the bowl\n",n+1);
				signal(bowl);
}}