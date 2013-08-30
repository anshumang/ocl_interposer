#include <stdio.h>
#include "CL/opencl.h"
//#include "client.h"
#include <netdb.h> //For debugging gethostbyname()

int main(){

	cl_int err = CL_SUCCESS;

	cl_uint num_platforms = 0;

	err = clGetPlatformIDs(0, NULL, &num_platforms);

	if(err != CL_SUCCESS){
		printf("clGetPlatformIDs failed with err %d\n", err);
		exit(-1);
	}

	printf("[main] Num OpenCL platforms found %d\n", num_platforms);

	if(num_platforms > 0){
	
		cl_platform_id platforms[num_platforms];

		err = clGetPlatformIDs(num_platforms, platforms, NULL);

		if(err != CL_SUCCESS){
			printf("clGetPlatformIDs failed with err %d\n", err);
			exit(-1);
		}

		int i;
		for(i=0; i<num_platforms; i++){
			printf("[main] platforms[%d]=%p\n", i, platforms[i]);


			cl_uint num_devices = 0;

			/*CL_DEVICE_TYPE_CPU/ACCELERATOR fails*/
			/*CL_DEVICE_TYPE_CUSTOM is not defined*/
			err = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_GPU, 0, NULL, &num_devices); /*CL_DEVICE_TYPE_DEFAULT/ALL*/

			if(err != CL_SUCCESS){
				printf("clGetDeviceIDs failed with err %d\n", err);
				exit(-1);
			}

			printf("[main] Num OpenCL devices found %d\n", num_devices);

			if(num_devices > 0){

				cl_device_id devices[num_devices];

				/*CL_DEVICE_TYPE_CPU/ACCELERATOR fails*/
				/*CL_DEVICE_TYPE_CUSTOM is not defined*/
				err = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_GPU, num_devices, devices, NULL); /*CL_DEVICE_TYPE_DEFAULT/ALL*/

				if(err != CL_SUCCESS){
					printf("clGetDeviceIDs failed with err %d\n", err);
					exit(-1);
				}

				int j;
				for(j=0; j<num_devices; j++){
					printf("[main] Device[%d] %p\n", j, devices[j]);
				}


				cl_context ctx;

				ctx = clCreateContext(NULL, num_devices, devices, NULL, NULL, &err);
				if(err != CL_SUCCESS){
                                        printf("clCreateContext failed with err %d\n", err);
                                        exit(-1);
                                }
				
				printf("[main] Context %p\n", ctx);

				cl_command_queue cmd_q[num_devices];

				for(j=0; j<num_devices; j++){

					printf("[main] Calling clCreateCommandQueue...\n");
					cmd_q[j] = clCreateCommandQueue(ctx, devices[j], 0, &err);

					if(err != CL_SUCCESS){
						printf("clCreateCommandQueue failed with err %d\n", err);
						exit(-1);
					}

					printf("[main] Command Queue[%d] %p\n", j, cmd_q[j]);

				}

				size_t size = 1024*1024;

				void *host_ptr = malloc(size);

				cl_mem mem;

				//mem = clCreateBuffer(ctx, CL_MEM_ALLOC_HOST_PTR, size, NULL, &err);
				//mem = clCreateBuffer(ctx, CL_MEM_COPY_HOST_PTR, size, host_ptr, &err);
				mem = clCreateBuffer(ctx, CL_MEM_USE_HOST_PTR, size, host_ptr, &err);
				if(err != CL_SUCCESS){
                                        printf("clCreateBuffer failed with err %d\n", err);
                                        exit(-1);
                                }
			}

		}
	}
	

	return 0;

}
