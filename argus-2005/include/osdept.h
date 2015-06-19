/**
  * \file osdept.h
  * \author Dong Wei
  */
#ifndef __OSDEPS__
#define __OSDEPS__
#include <time.h>

#define THREAD_STACK 4096

#ifdef LINUX
#define __int64 long long

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <pthread.h>
#include <semaphore.h>
typedef void *(*thread_routine_f) (void *);

#define DECLARE_MUTEX(n) pthread_mutex_t n
#define MUTEX_CREATE(n)	pthread_mutex_init(&(n), NULL)
#define MUTEX_LOCK(n)	pthread_mutex_lock(&(n))
#define MUTEX_UNLOCK(n)	pthread_mutex_unlock(&(n))
#define MUTEX_DESTROY(n) pthread_mutex_destroy(&(n))

#define DECLARE_SEMAPHORE(s) sem_t s
#define SEMAPHORE_CREATE(s, n) sem_init(&(s), 0, n)
#define SEMAPHORE_WAIT(s) sem_wait(&(s))
#define SEMAPHORE_POST(s) sem_post(&(s))
#define SEMAPHORE_DESTROY(s) sem_destroy(&(s))

#define DECLARE_THREAD(n) pthread_t n

#define THREAD_CREATE(thread, routine, arg) \
		pthread_create(&(thread), NULL, (thread_routine_f)routine, arg)

#define THREAD_EXIT(n) pthread_exit(n)
#define THREAD_DESTROY(n) do { pthread_cancel(n); } while (0)

/*
#define THREAD_PRIORITY_MAX()	sched_get_priority_max(SCHED_OTHER)
#define THREAD_PRIORITY_MIN()	sched_get_priority_min(SCHED_OTHER)

#define THREAD_CREATE_PRIORITY(thread, routine, arg, p) \
do {	\
	int res;	\
	struct sched_param param;	\
	pthread_attr_t attr;	\
	res = pthread_attr_init(&attr);	\
	assert(res == 0);	\
	param.__sched_priority = p;	\
	res = pthread_attr_setschedparam(&attr, &param);	\
	assert(res == 0);	\
	pthread_create(&(thread), &attr, (thread_routine_f)routine, arg);\
	pthread_attr_destroy(&attr);	\
} while (0)
*/
#include <dlfcn.h>
typedef void *lib_handle_t;

#define LIBRARY_INVALID_HANDLE(n) (n == NULL)
#define LIBRARY_LOAD(name) dlopen(name, RTLD_NOW)
#define LIBRARY_SYMBOL(lib, name) dlsym(lib, name)
#define LIBRARY_CLOSE(lib) dlclose(lib)

#define SLEEP(n) sleep(n)

#endif

#ifdef WIN32
#include <windows.h>
#include <process.h>

typedef void (*thread_routine_f) (void *);

#define DECLARE_MUTEX(n) HANDLE n
#define MUTEX_CREATE(n)	do {n=CreateMutex(NULL, FALSE, NULL); assert(n != NULL);} while (0)
#define MUTEX_LOCK(n)	WaitForSingleObject(n, INFINITE)
#define MUTEX_UNLOCK(n)	ReleaseMutex(n)
#define MUTEX_DESTROY(n) CloseHandle(n)

#define DECLARE_SEMAPHORE(s) HANDLE s
#define SEMAPHORE_CREATE(s, n) do {s = CreateSemaphore(NULL, 0, n, NULL); assert(s != NULL); } while (0)
#define SEMAPHORE_WAIT(s) WaitForSingleObject(s, INFINITE)
#define SEMAPHORE_POST(s) ReleaseSemaphore(s, 1, NULL)
#define SEMAPHORE_DESTROY(s) CloseHandle(s)

#define DECLARE_THREAD(n) HANDLE n

#define THREAD_CREATE(thread, routine, arg) \
		do {thread = (HANDLE)_beginthread(routine, THREAD_STACK, arg);} while (0)

#define THREAD_EXIT(n) _endthread()
#define THREAD_DESTROY(n) do { TerminateThread(n, 0);  CloseHandle(n);} while(0)


typedef HANDLE lib_handle_t;

#define LIBRARY_INVALID_HANDLE(n) (n == NULL)
#define LIBRARY_LOAD(name) LoadLibrary(name)
#define LIBRARY_SYMBOL(lib, name) GetProcAddress(lib, name)
#define LIBRARY_CLOSE(lib) CloseHandle(lib)

#define strcasecmp(a,b) strcmpi(a,b)

int gettimeofday (struct timeval *, void *);

#define SLEEP(n) Sleep(n*1000)

#endif

#ifdef WIN32
#ifndef BORLANDC
static __inline void *alloca (size_t size)
{
	return _alloca(size);
}
static __inline void bzero(void *s, int n)
{
	memset(s, 0, n);
}
#endif
#endif

static __inline int TIME (void)
{
	return time(NULL);
}


#endif

