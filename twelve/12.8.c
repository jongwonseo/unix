#include "apue.h"
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

extern int makethread(void* (*)(void*), void*);

struct to_info{
	void (*to_fn) (void*);
	void* to_arg;
	struct timespec to_wait;
};

#define SECTONSEC 1000000000
#define USECTONSEC 1000

void* timeout_helper(void* arg){
	struct to_info* tip;

	tip = (struct to_info*)arg;
	nanosleep(&tip->to_wait, NULL);
	(*tip->to_fn)(tip->to_arg);
	return 0;
}

void timeout(const struct timespec* when, void(*func)(void*), void* arg){
	struct timespec now;
	struct timeval tv;
	struct to_info* tip;
	int err;

	gettimeofday(&tv, NULL);
	now.tv_sec = tv.tv_sec;
	now.tv_nsec = tv.tv_usec * USECTONSEC;
	if((when->tv_sec > now.tv_sec) || (when->tv_sec == now.tv_sec && when->tv_nsec > now.tv_nsec)){
		if(tip != NULL){
			tip->to_fn = func;
			tip->to_arg = arg;	
			tip->to_wait.tv_sec = when->tv_sec - now.tv_sec;
			if(when->tv_nsec >= now.tv_nsec){
				tip->to_wait.tv_nsec = when->tv_nsec - now.tv_nsec;
			}else{
				tip->to_wait.tv_sec--;
				tip->to_wait.tv_nsec = SECTONSEC - now.tv_nsec + when->tv_nsec;
			}
		
			err = makethread(timeout_helper, (void*)tip);
			if(err ==0)
				return;
		}
	}
}

pthread_mutexattr_t attr;
pthread_mutex_t mutex;

void retry(void* arg){
	pthread_mutex_lock(&mutex);
	pthread_mutex_unlock(&mutex);
}

int main(){
	int err, condition, arg;
	struct timespec when;

	if((err = pthread_mutexattr_init(&attr)) != 0)
		printf("mutex fail");
	if((err= pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE)) !=0)
		printf("can`t set recursive type");
	if((err=pthread_mutex_init(&mutex,&attr))!=0)
		printf("can`t create recursive mutex");

	pthread_mutex_lock(&mutex);
	if(condition){
		timeout(&when, retry, (void*)arg);
	}

	pthread_mutex_unlock(&mutex);
	exit(0);
}
