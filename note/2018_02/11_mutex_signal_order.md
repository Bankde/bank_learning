# Mutex lock/unlock and signal order

This topic is about order of pthread_mutex_lock, pthread_mutex_unlock and pthread_cond_signal order.  

It has always been confusing whether signal should be inside the mutex lock. According to the linux manual:  

> The pthread_cond_broadcast() or pthread_cond_signal() functions may be called by a thread whether or not it currently owns the mutex that threads calling pthread_cond_wait() or pthread_cond_timedwait() have associated with the condition variable during their waits; however, if predictable scheduling behavior is required, then that mutex shall be locked by the thread calling pthread_cond_broadcast() or pthread_cond_signal().  

We can easily conclude that calling signal both inside/outside the mutex scope are working fine.

Before going deeper, let's see the answer from stackoverflow: https://stackoverflow.com/questions/4544234/calling-pthread-cond-signal-without-locking-mutex  

The top answer is somewhat misleading. The interleaving of instruction there does not come from using signal outside the mutex scope, the issue directly comes from both thread sharing the variable `condition` without proper lock.

    Process A                             Process B

    pthread_mutex_lock(&mutex);
    while (condition == FALSE)

                                          condition = TRUE;
                                          pthread_cond_signal(&cond);

    pthread_cond_wait(&cond, &mutex);

The above issue wouldn't exist if we properly lock the `condition` variable

    Process B.1                           Process B.2

    pthread_mutex_lock(&mutex);           pthread_mutex_lock(&mutex);  
    condition = TRUE;                     condition = TRUE;
    pthread_cond_signal(&cond);           pthread_mutex_unlock(&mutex);
    pthread_mutex_unlock(&mutex);         pthread_cond_signal(&cond);

The deadlock won't happen in both B.1 and B.2 so the real question here is which is better, B.1 or B.2 ?  
Fortunately, there is a comment from R that clear this up properly.  

> For what it's worth, it seems the question of whether to unlock before or after the signal is actually non-trivial to answer. Unlocking after ensures that a lower-priority thread won't be able to steal the event from a higher-priority one, but if you're not using priorities, unlocking before the signal will actually reduce the number of system calls/context switches and improve overall performance. – R.. Sep 29 '11 at 19:41

And also this stackoverflow: https://stackoverflow.com/questions/6419117/signal-and-unlock-order

So it depends on what job we are coding for.  
- For a serious predictable/scheduling/realtime job, we need B.1 so that we know the next high-priority thread will receive a mutex. However, it comes with a system call cost (implementation of signal/lock/unlock handling).  

- For any other job, B.2 seems to be better decision so we can reduce number of hidden system handling. The cost here is that it is possible there might be the third thread who just recently comes and steals the priority from the first thread who is still waiting and cond_signal.  

I don't have time and skill to go deeper than this but this should already be clear enough for us to decide. For me, it still does not matter much to most systems. Choose whatever version you like unless the benchmark says otherwise.
