#include <stdio.h>
#include "CL/opencl.h"
//#include "client.h"
#include <netdb.h> //For debugging gethostbyname()

const char *program_str[] = {
"__kernel void helloworld(__global int* in, __global int* out){int num = get_global_id(0);out[num] = in[num] + 1;}"
};


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

				size_t size_g = 16*1024;

				void *host_ptr = malloc(size_g);
				void *host_ptr_in = malloc(size_g);
				void *host_ptr_out = malloc(size_g);

				cl_mem mem_in, mem_out;

				//mem_in = clCreateBuffer(ctx, CL_MEM_ALLOC_HOST_PTR, size_g, NULL, &err);
				//mem_in = clCreateBuffer(ctx, CL_MEM_COPY_HOST_PTR, size_g, host_ptr, &err);
				mem_in = clCreateBuffer(ctx, CL_MEM_USE_HOST_PTR, size_g, host_ptr_in, &err);
				if(err != CL_SUCCESS){
                                        printf("clCreateBuffer failed with err %d\n", err);
                                        exit(-1);
                                }
				printf("[main] Mem %p\n", mem_in);

				//mem_out = clCreateBuffer(ctx, CL_MEM_ALLOC_HOST_PTR, size_g, NULL, &err);
				//mem_out = clCreateBuffer(ctx, CL_MEM_COPY_HOST_PTR, size_g, host_ptr, &err);
				mem_out = clCreateBuffer(ctx, CL_MEM_USE_HOST_PTR, size_g, host_ptr_out, &err);
				if(err != CL_SUCCESS){
                                        printf("clCreateBuffer failed with err %d\n", err);
                                        exit(-1);
                                }
				printf("[main] Mem %p\n", mem_out);

				cl_program prog;

				prog = clCreateProgramWithSource(ctx, sizeof(program_str)/sizeof(char *), (const char **)&program_str, NULL, &err);
				if(err != CL_SUCCESS){
                                        printf("clCreateProgramWithSource failed with err %d\n", err);
                                        exit(-1);
                                }
				printf("[main] Program %p\n", prog);

				err = clBuildProgram(prog, num_devices, devices, NULL, NULL, NULL);
				if(err != CL_SUCCESS){
                                        printf("clBuildProgram failed with err %d\n", err);
					printf("CL_BUILD_PROGRAM_FAILURE %d\n", err);
					char param_value[16*1024];
					size_t param_value_size_ret = 0;
					for(int j=0; j<num_devices; j++){
						err = clGetProgramBuildInfo(prog, devices[j], CL_PROGRAM_BUILD_LOG, 16*1024, param_value, &param_value_size_ret);
						if(err != CL_SUCCESS){
							printf("clGetProgramBuildInfo failed with err %d\n", err);
							exit(-1);
						}
						printf("param_value_size_ret %ld\n", param_value_size_ret);
						printf("param_value %s\n", param_value);
					}
                                        exit(-1);
                                }

#if 0
				cl_kernel kern;

				kern = clCreateKernel(prog, "helloworld", &err);
				if(err != CL_SUCCESS){
                                        printf("clCreateKernel failed with err %d\n", err);
                                        exit(-1);
                                }
				printf("[main] Kernel %p\n", kern);

				size_t size_l = 1;

				for(int j=0; j<num_devices; j++){
					//char param_value[1024];
					size_t param_value = 0;
					size_t param_value_size_ret;
					err = clGetKernelWorkGroupInfo(kern, devices[j], CL_KERNEL_WORK_GROUP_SIZE, sizeof(param_value), (void *)&param_value, &param_value_size_ret);
					if(err != CL_SUCCESS){
						printf("clGetKernelWorkGroupInfo failed with err %d\n", err);
						exit(-1);
					}
					printf("CL_KERNEL_WORK_GROUP_SIZE %ld\n", param_value);
					err = clGetKernelWorkGroupInfo(kern, devices[j], CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE, sizeof(param_value), (void *)&param_value, &param_value_size_ret);
					if(err != CL_SUCCESS){
						printf("clGetKernelWorkGroupInfo failed with err %d\n", err);
						exit(-1);
					}
					printf("CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE %ld\n", param_value);
				}
			
				err = clSetKernelArg(kern, 0, sizeof(cl_mem), (void *)&mem_in);
				if(err != CL_SUCCESS){
                                        printf("clSetKernelArg failed with err %d\n", err);
                                        exit(-1);
                                }

				err = clSetKernelArg(kern, 1, sizeof(cl_mem), (void *)&mem_out);
				if(err != CL_SUCCESS){
                                        printf("clSetKernelArg failed with err %d\n", err);
                                        exit(-1);
                                }

				cl_uint work_dim = 1;

				for(int j=0; j<num_devices; j++){

					err = clEnqueueWriteBuffer(cmd_q[j], mem_in, CL_TRUE, 0, size_g, host_ptr, 0, NULL, NULL);
					if(err != CL_SUCCESS){
						printf("clEnqueueWriteBuffer failed with err %d\n", err);
						exit(-1);
					}

					size_t global_work_offset[work_dim], global_work_size[work_dim], local_work_size[work_dim];
					for(int k=0; k<work_dim; k++){
						global_work_offset[k] = 0;
						global_work_size[k] = size_g;
						local_work_size[k] = size_l;
					}

					err = clEnqueueNDRangeKernel(cmd_q[j], kern, work_dim, global_work_offset, global_work_size, local_work_size, 0, NULL, NULL);
					if(err != CL_SUCCESS){
						printf("clEnqueueNDRange failed with err %d\n", err);
						printf("CL_INVALID_KERNEL_ARGS %d\n", CL_INVALID_KERNEL_ARGS);
						exit(-1);
					}

					err = clEnqueueReadBuffer(cmd_q[j], mem_out, CL_TRUE, 0, size_g, host_ptr, 0, NULL, NULL);
					if(err != CL_SUCCESS){
						printf("clEnqueueReadBuffer failed with err %d\n", err);
						printf("CL_INVALID_COMMAND_QUEUE %d\n", CL_INVALID_COMMAND_QUEUE);
						printf("CL_INVALID_CONTEXT %d\n", CL_INVALID_CONTEXT);
						printf("CL_INVALID_MEM_OBJECT %d\n", CL_INVALID_MEM_OBJECT);
						printf("CL_MEM_OBJECT_ALLOCATION_FAILURE %d\n", CL_MEM_OBJECT_ALLOCATION_FAILURE);
						printf("CL_INVALID_OPERATION %d\n", CL_INVALID_OPERATION);
						printf("CL_INVALID_VALUE %d\n", CL_INVALID_VALUE);
						printf("CL_OUT_OF_RESOURCES %d\n", CL_OUT_OF_RESOURCES);
						printf("CL_OUT_OF_HOST_MEMORY %d\n", CL_OUT_OF_HOST_MEMORY);
						exit(-1);
					}
				}
#endif	
			}

		}
	}

	return 0;

}
