When compiling badTimer.c || intTimer.c:
add -lpthread -lrt
lrt is realtime library for gettimeofday function
intTimer stands for interruptTimer, probably best timer I have found
badTimer is bad because using usleep, the time will be more than 1 sec (being: 1 + (very small time using other function like loop,call,etc))
