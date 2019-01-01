#include "producer.h"

Producer::Producer()
{

}

Producer::Producer(Store* s) {
    store = s;
}

void* Producer::produce() {
    for(int i = 0; i < 20; i++) {
        pthread_mutex_lock(&store->busy);

        store->setNum(i, i);

        pthread_cond_signal(&store->cond);
        pthread_mutex_unlock(&store->busy);
        sleep(1);
    }
    pthread_exit(nullptr);
};
