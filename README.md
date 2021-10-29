Number of items and size of the buffer.
Declared two semaphore avail and fill. If semaphore has value 0, caller will be blocked, and it must wait until someone does a post.
sem_wait() and sem_post().
pshared is 0, semaphore is shared among all threads of a process. 
mutex can be unlocked only by whoever locked it.
pthread initialize *mutex, If attr is NULL, a default set of attributes is used.
rand() set random item.
mutex_lock locks the mutex and caller will be blocked until mutex is unlocked(mutex_unlock).
producer and consumer both lock and unlock to produce or consume the item.
destroy avail, fill, mutex, those become uninitialized.
gcc producer-consumer.c -pthread
