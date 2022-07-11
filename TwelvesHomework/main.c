#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define THREAD_NMB 4

int stopFlags[THREAD_NMB - 1];

struct thread{
    pthread_spinlock_t * spin_list;
    pthread_spinlock_t * private_spin;
    int *shops;
    int tnum;
    int need;
};

void *customer(void*  info){
    struct thread * tinfo = (struct thread *) info;

    while(tinfo->need > 0){
        for(int i = 0; i<5; ++i){
            pthread_spin_lock(tinfo->spin_list + i);

            int value;

            if(tinfo->need >= tinfo->shops[i]){
                value = tinfo->shops[i];
                tinfo->need -= value;
            }else{
                value = tinfo->need;
                tinfo->need = 0;
            }

            printf("Customer #%d bought in shop #%d value: %d", tinfo->tnum, i + 1, value);

            pthread_spin_unlock(tinfo->spin_list + i);

            pthread_spin_lock(tinfo->private_spin);

            if(tinfo->need <=0){
                stopFlags[tinfo->tnum - 1] = 1;
            }

            pthread_spin_unlock(tinfo->private_spin);

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
        pthread_spin_lock(tinfo->spin_list + i);

        int value;
        tinfo->shops[i] += 500;
        printf("Put in shop #%d, now value is in shop #%d", i + 1, tinfo->shops[i]);

        pthread_spin_unlock(tinfo->spin_list + i);

        int stopFlag = 1;

        for(int i = 0; (i < THREAD_NMB - 1) && (stopFlag != 0) ; ++i){
            pthread_spin_lock(tinfo->private_spin + i);

            if(1 == stopFlags[i]){
                stopFlag = 1;
            }else{
                stopFlag = 0;
            }

            pthread_spin_unlock(tinfo->private_spin + i);
        }
        
        if(1 == stopFlag){
            break;
        }
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
    pthread_spinlock_t private_spinlock_list[3];
    int shops[5];

    for(int i = 0; i < 5; ++i){
        pthread_spin_init(spinlock_list + i, PTHREAD_PROCESS_SHARED);
        shops[i] = 1000;
    }

    for(int i = 0; i < 3; ++i){
        pthread_spin_init(private_spinlock_list + i, PTHREAD_PROCESS_SHARED);
    }

    for(int i = 0; i < THREAD_NMB; ++i){
        threads[i].shops = shops;
        threads[i].spin_list = spinlock_list;
        threads[i].need = 5000;
        threads[i].tnum = i + 1;
        if(i < THREAD_NMB - 1){
            threads[i].private_spin = private_spinlock_list + i;
        }else{
            threads[i].private_spin = private_spinlock_list;
        }
    }

	int i;
	int index1;
	int *s;
	pthread_t thread[THREAD_NMB];
	
	for(i = 1; i <= THREAD_NMB - 1; i++){
		pthread_create(&thread[i-1], NULL, customer, threads + i - 1);
	}
    pthread_create(&thread[THREAD_NMB - 1], NULL, shop_empl, threads + THREAD_NMB - 1);
	
	for(index1 = 0; index1 < THREAD_NMB; index1++){
		pthread_join(thread[index1], (void **) &s);
	}
	
	return 0;
}