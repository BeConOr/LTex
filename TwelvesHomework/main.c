#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define THREAD_NMB 4

int stopFlags[THREAD_NMB - 1];

struct thread{
    pthread_spinlock_t * spin_list;
    int *shops;
    int tnum;
    int need;
};

void *customer(void*  info){
    struct thread * tinfo = (struct thread *) info;
    while(tinfo->need > 0){
        for(int i = 0; i<5; ++i){
            pthread_spin_lock(spin_list + i);
            int value;
            if(tinfo->need >= shops[i]){
                value = shops[i];
                tinfo->need -= value;
            }else{
                value = tinfo->need;
                tinfo->need = 0;
            }
            printf("Customer #%d bought in shop #%d value: %d", tinfo->tnum, i + 1, value);
            if(tinfo->need <=0){
                stopFlags[tinfo->tnum - 1] = 1;
            }
            pthread_spin_unlock(spin_list + i);
            if(1 == stopFlags[tinfo->tnum - 1]){
                break;
            }
        }
    }
    return NULL;
}
void *shop_empl(void*  info){
    struct thread * tinfo = (struct thread *) info;
    for(int i = 0; i<5; ++i){
        pthread_spin_lock(spin_list + i);
        int value;
        shops[i] += 500;
        printf("Put #%d in shop #%d", shops[i], i + 1);
        pthread_spin_unlock(spin_list + i);
        for(int i = 0; i < THREAD_NMB - 1; ++i){
            
        }
    }
    return NULL;
}


void *thread_start(void *args){
	int i;
	long tmp;
	
	for(i = 0; i < 100000; i++){
		tmp = a;
		tmp++;
		a = tmp;
	}
	
	return NULL;
}

int main(void){
	int index[THREAD_NMB];

    for(int i = 0; i < THREAD_NMB - 1; ++i){
        stopFlags[i] = 0;
    }

    struct thread threads[THREAD_NMB];
    pthread_spinlock_t spinlock_list[5];
    int shops[5]
    for(int i = 0; i < 5; ++i){
        pthread_spin_init(spinlock_list + i, PTHREAD_PROCSS_SHARED);
        shops[i] = 1000;
    }
    for(int i = 0; i < THREAD_NMB; ++i){
        threads[i].shops = shops;
        threads[i].spin_list = spinlock_list;
        threads[i].need = 5000;
        threads[i].tnum = i + 1;
    }

	int i;
	int index1;
	int *s;
	pthread_t thread[THREAD_NMB];
	
	for(i = 1; i <= THREAD_NMB - 1; i++){
		pthread_create(&thread[i-1], NULL, customer, threads + i - 1);
	}
	
	for(index1 = 0; index1 < THREAD_NMB; index1++){
		pthread_join(thread[index1], (void **) &s);
	}
	
	return 0;
}