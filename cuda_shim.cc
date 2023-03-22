#define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include "kutrace_lib.h"

static cudaError_t(*real_cudaMemcpyAsync)(void*, const void*, size_t, cudaMemcpyKind, cudaStream_t) = NULL;
static cudaError_t(*real_cudaLaunchKernel)(const void*, dim3, dim3, void**, size_t, cudaStream_t) = NULL; 

void __attribute__((constructor)) init(void)
{
	printf("In the shim init function\n");
	real_cudaMemcpyAsync = 
		reinterpret_cast<cudaError_t(*)( void*, const void*, size_t, cudaMemcpyKind, cudaStream_t)>
					(dlsym(RTLD_NEXT, "cudaMemcpyAsync"));

	real_cudaLaunchKernel = 
		reinterpret_cast<cudaError_t(*)(const void*, dim3, dim3, void**, size_t, cudaStream_t)>
					(dlsym(RTLD_NEXT, "cudaLaunchKernel"));
}


extern "C" cudaError_t cudaMemcpyAsync ( void* dst, const void* src, size_t count, cudaMemcpyKind kind, cudaStream_t str )
{
    printf("Inside cudaMemcpyAsync shim\n");
    return real_cudaMemcpyAsync( dst, src, count, kind, str );
}

extern "C" cudaError_t cudaLaunchKernel(const void* func, dim3 gridDim, dim3 blockDim, void** args, size_t sharedMem, cudaStream_t stream)
{
	printf("Inside cudaLaunchKernel\n");
	return real_cudaLaunchKernel(func, gridDim, blockDim, args, sharedMem, stream);
}
