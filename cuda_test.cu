#include <stdio.h>

__global__
void saxpy(int n, float a, float *x, float *y)
{
  int i = blockIdx.x*blockDim.x + threadIdx.x;
  if (i < n) y[i] = a*x[i] + y[i];
}

int main(void)
{
  printf("cudaMemcpyAsync addr: %p\n", cudaMemcpyAsync);
  cudaStream_t stream1;
  cudaStreamCreate(&stream1);
 
  int N = 1<<20;
  float *x, *y, *d_x, *d_y;
  x = (float*)malloc(N*sizeof(float));
  y = (float*)malloc(N*sizeof(float));

  cudaMalloc(&d_x, N*sizeof(float)); 
  cudaMalloc(&d_y, N*sizeof(float));

  for (int i = 0; i < N; i++) {
    x[i] = 1.0f;
    y[i] = 2.0f;
  }

  cudaMemcpyAsync(d_x, x, N*sizeof(float), cudaMemcpyHostToDevice, stream1);
  cudaMemcpyAsync(d_y, y, N*sizeof(float), cudaMemcpyHostToDevice, stream1);

  // Perform SAXPY on 1M elements
  //saxpy<<<(N+255)/256, 256, 0, stream1>>>(N, 2.0f, d_x, d_y);
  unsigned int blocks = (N+255)/256;
  unsigned int threads = 256;
  float a = 2.0f;
  void *params[] = { (void*)&N, (void*)&a, (void*)&d_x, (void*)&d_y };
  cudaLaunchKernel((void*)saxpy, dim3(blocks), dim3(threads), params, 0, stream1);

  cudaMemcpyAsync(y, d_y, N*sizeof(float), cudaMemcpyDeviceToHost, stream1);

  float maxError = 0.0f;
  for (int i = 0; i < N; i++)
    maxError = max(maxError, abs(y[i]-4.0f));
  printf("Max error: %f\n", maxError);

  cudaFree(d_x);
  cudaFree(d_y);
  free(x);
  free(y);
  cudaStreamDestroy(stream1);
}
