Ripped pthread_test from an example of pthread rw locks I found on IBM's website.
Ripped the cuda test from Nvidia's Cuda basic demo webpage.

Just run the compile_all.sh script to do all the compilation. You might have to change the path to the cuda directory in the script first though.

To run the cuda example, you can run "LD_PRELOAD=./cuda_shim.so ./cuda_test"
To run the pthread example, you can run "LD_PRELOAD=./pthread_shim.so ./pthread_test"
