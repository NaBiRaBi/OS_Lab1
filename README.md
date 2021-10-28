Number of items and size of the buffer.
Sem_t sem;
Declared two semaphore empty and full. If semaphore has value 0, caller will be blocked, and it must wait until someone does a post.

pshared is 0, semaphore is shared among all threads of a process. 
