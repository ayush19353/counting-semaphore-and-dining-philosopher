
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

void my_semaphore_init(my_semaphore **s,int count)
{
	*s=(my_semaphore *) malloc(sizeof(my_semaphore));
	pthread_mutex_init(&((*s)->mutex),NULL);
	pthread_cond_init(&((*s)->cv),NULL);

(*s)->f=count;
}


void wait(my_semaphore *s)
{//here we will check if other philosopher has the bowl or tehe chopstick
		while(s->f<=0);//busy waiting does not enter as long as s<=0
		
		while(pthread_mutex_trylock(&s->mutex)!=0);//trylock retruns 0 if it acquires the lock means no other thread is inside the lock
		s->f--;
		pthread_mutex_unlock(&s->mutex);
}

void signal(my_semaphore *s)
{
		while(pthread_mutex_trylock(&s->mutex)!=0);	//trylock retruns 0 if it acquires the lock means no other thread is inside the lock
	
		s->f++;
		pthread_mutex_unlock(&s->mutex);
}
void signalprint(my_semaphore* printValue)//this would print the signal state of the semaphore if it is acquired or free
{ pthread_mutex_lock(&(printValue->mutex));

	printf("%d\n", (printValue->f));//printf("%s\n","RRRHRHRRH");
	       pthread_mutex_unlock(&(printValue->mutex));

}


//ignore
void de(int gg)//function for errror reporting if any
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
	my_semaphore_init(&bowl,1);// calling fuction which would then initialize the bowl semaphore 

int i=0;
	while(i<k)
	//for(int i=0;i<k;i++)
	{//printf("%d\n",i );
		my_semaphore_init(&forks[i],1);//calling function which would then initialze the forks semaphores
	
	i++;}
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
			big(kp);
//
		//	printf("%d\n",i );
			}
			i=0;
			while(i<k)
			{
			kp=pthread_join(ph[i],&message);// pthread join for philosophers
			
			i++;
			de(kp);

			}
			free(forks);//freeeing the allocated malloc
			//free(bowl);

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
				printf("Philiosopher %d is eating using forks %d and  %d and has the bowl\n",n+1,n+1,(n+1)%k +1);
				// printf("%s%d %s%d %s%d\n ","--p",n+1,"-f",(n+1),"-f",(n+1)%k+1 );
				printf("Philiosopher %d has kept %d and %d\n",n+1,n+1,(n+1)%k +1);

				signal(forks[(n+1)%k ]);
				signal(forks[n]);
				printf("Philiosopher %d kept the bowl\n",n+1);
				signal(bowl);
}}