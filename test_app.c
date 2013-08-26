#include <stdio.h>
#include "CL/opencl.h"
//#include "client.h"

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

				for(i=0; i<num_devices; i++){
					printf("[main] Device[%d] %p\n", i, devices[i]);
				}


				cl_context ctx;

				ctx = clCreateContext(NULL, num_devices, devices, NULL, NULL, &err);
				if(err != CL_SUCCESS){
                                        printf("clCreateContext failed with err %d\n", err);
                                        exit(-1);
                                }
				
				printf("[main] Context %p\n", ctx);

				int j;

				cl_command_queue cmd_q[num_devices];

				for(j=0; j<num_devices; j++){

					cmd_q[j] = clCreateCommandQueue(ctx, devices[j], 0, &err);

					if(err != CL_SUCCESS){
						printf("clCreateCommandQueue failed with err %d\n", err);
						exit(-1);
					}

					printf("[main] Command Queue[%d] %p\n", j, cmd_q[j]);

				}
			}

		}
	}
	

	return 0;

}
