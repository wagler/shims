g++ -I./kutrace -I/usr/local/cuda-10.2/include -fPIC -shared -o cuda_shim.so cuda_shim.cc -ldl -L/usr/local/cuda-10.2/targets/x86_64-linux/lib -lcudart
g++ -I./kutrace kutrace/kutrace_lib.cc -fPIC -shared -o pthread_shim.so pthread_shim.cc -ldl 
nvcc -o cuda_test cuda_test.cu -cudart shared
g++ -I./kutrace pthread_test.cc kutrace/kutrace_lib.cc -pthread -g -o pthread_test
# Run with LD_LIBRARY_PATH=/usr/local/cuda-10.2/lib64 LD_PRELOAD=./cuda_shim.so ./cuda_test
