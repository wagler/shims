#define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include "kutrace_lib.h"

static int (*real_pthread_rwlock_init) 		(pthread_rwlock_t *__restrict __rwlock, const pthread_rwlockattr_t *__restrict __attr) = NULL;
static int (*real_pthread_rwlock_destroy)	(pthread_rwlock_t *__rwlock) = NULL;
static int (*real_pthread_rwlock_rdlock)	(pthread_rwlock_t *__rwlock) = NULL;
static int (*real_pthread_rwlock_tryrdlock) (pthread_rwlock_t *  rwlock) = NULL;
static int (*real_pthread_rwlock_wrlock) 	(pthread_rwlock_t *__rwlock) = NULL;
static int (*real_pthread_rwlock_trywrlock) (pthread_rwlock_t *__rwlock) = NULL;
static int (*real_pthread_rwlock_unlock)	(pthread_rwlock_t *__rwlock) = NULL;

void __attribute__((constructor)) init(void)
{
	printf("In the libpthread.so init function\n");
	kutrace::mark_b("shm_i");

	// Load the real functions

	// pthread_rwlock_init
	real_pthread_rwlock_init = reinterpret_cast<int(*)(pthread_rwlock_t*, const pthread_rwlockattr_t*)>(dlsym(RTLD_NEXT, "pthread_rwlock_init"));
	if (real_pthread_rwlock_init == NULL)
	{
		printf("Couldn't find real pthread_rwlock_init()\n");
		exit(255);
	}
	printf("Loaded real pthread_rwlock_init\n");

	// pthread_rwlock_destroy
	real_pthread_rwlock_destroy = reinterpret_cast<int(*)(pthread_rwlock_t*)>(dlsym(RTLD_NEXT, "pthread_rwlock_destroy"));
	if (real_pthread_rwlock_destroy == NULL)
	{
		printf("Couldn't find real pthread_rwlock_destroy()\n");
		exit(255);
	}
	printf("Loaded real pthread_rwlock_destroy\n");

	// pthread_rwlock_rdlock
	real_pthread_rwlock_rdlock = reinterpret_cast<int(*)(pthread_rwlock_t*)>(dlsym(RTLD_NEXT, "pthread_rwlock_rdlock"));
	if (real_pthread_rwlock_rdlock == NULL)
	{
		printf("Couldn't find real pthread_rwlock_rdlock()\n");
		exit(255);
	}
	printf("Loaded real pthread_rwlock_rdlock\n");

	// pthread_rwlock_tryrdlock
	real_pthread_rwlock_tryrdlock = reinterpret_cast<int(*)(pthread_rwlock_t*)>(dlsym(RTLD_NEXT, "pthread_rwlock_tryrdlock"));
	if (real_pthread_rwlock_tryrdlock == NULL)
	{
		printf("Couldn't find real pthread_rwlock_tryrdlock()\n");
		exit(255);
	}
	printf("Loaded real pthread_rwlock_tryrdlock\n");

	// pthread_rwlock_wrlock
	real_pthread_rwlock_wrlock = reinterpret_cast<int(*)(pthread_rwlock_t*)>(dlsym(RTLD_NEXT, "pthread_rwlock_wrlock"));
	if (real_pthread_rwlock_wrlock == NULL)
	{
		printf("Couldn't find real pthread_rwlock_wrlock()\n");
		exit(255);
	}
	printf("Loaded real pthread_rwlock_wrlock\n");

	// pthread_rwlock_trywrlock
	real_pthread_rwlock_trywrlock = reinterpret_cast<int(*)(pthread_rwlock_t*)>(dlsym(RTLD_NEXT, "pthread_rwlock_trywrlock"));
	if (real_pthread_rwlock_trywrlock == NULL)
	{
		printf("Couldn't find real pthread_rwlock_trywrlock()\n");
		exit(255);
	}
	printf("Loaded real pthread_rwlock_trywrlock\n");

	// pthread_rwlock_unlock
	real_pthread_rwlock_unlock = reinterpret_cast<int(*)(pthread_rwlock_t*)>(dlsym(RTLD_NEXT, "pthread_rwlock_unlock"));
	if (real_pthread_rwlock_unlock == NULL)
	{
		printf("Couldn't find real pthread_rwlock_unlock()\n");
		exit(255);
	}
	printf("Loaded real pthread_rwlock_unlock\n");

	kutrace::mark_b("/shm_i");
}

extern "C" int pthread_rwlock_init (pthread_rwlock_t *__restrict __rwlock, const pthread_rwlockattr_t *__restrict __attr)
{
	kutrace::mark_b("pinit");
	printf("Inside pthread_rwlock_init\n");
	kutrace::mark_b("/pinit");
	return real_pthread_rwlock_init(__rwlock, __attr);
}

extern "C" int pthread_rwlock_destroy(pthread_rwlock_t *rwlock)
{
	kutrace::mark_b("pdest");
	printf("Inside pthread_rwlock_destroy\n");
	kutrace::mark_b("/pdest");
	return real_pthread_rwlock_destroy(rwlock);
}

extern "C" int pthread_rwlock_rdlock(pthread_rwlock_t *__rwlock)
{
	kutrace::mark_b("prdlk");
	printf("Inside pthread_rwlock_rdlock\n");
	kutrace::mark_b("/prdlk");
	return real_pthread_rwlock_rdlock(__rwlock);
}

extern "C" int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock)
{
	kutrace::mark_b("ptrlk");
	printf("Inside pthread_rwlock_tryrdlock\n");	
	kutrace::mark_b("/ptrlk");
	return real_pthread_rwlock_tryrdlock(rwlock);
}

extern "C" int pthread_rwlock_wrlock(pthread_rwlock_t *__rwlock)
{
	kutrace::mark_b("pwrlk");
	printf("Inside pthread_rwlock_wrlock\n");
	kutrace::mark_b("/pwrlk");
	return real_pthread_rwlock_wrlock(__rwlock);
}

extern "C" int pthread_rwlock_trywrlock(pthread_rwlock_t *__rwlock)
{
	kutrace::mark_b("ptwlk");
	printf("Inside pthread_rwlock_trywrlock\n");
	kutrace::mark_b("/ptwlk");
	return real_pthread_rwlock_trywrlock(__rwlock);
}

extern "C" int pthread_rwlock_unlock(pthread_rwlock_t *__rwlock)
{
	kutrace::mark_b("pulk");
	printf("Inside pthread_rwlock_unlock\n");
	kutrace::mark_b("/pulk");
	return real_pthread_rwlock_unlock(__rwlock);
}

