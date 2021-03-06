#include <stdio.h>
#include "CL/opencl.h"
#include <rpc/rpc.h>
#include <rpc/pmap_clnt.h>
#include <sys/socket.h>
#include "../client_server_common_includes.h"
#include <assert.h>

void clGetPlatformIDs_server(get_platform_ids_ *argp, get_platform_ids_ *retp){

	cl_int err = CL_SUCCESS;
	retp->err = err;

        cl_uint num_platforms = 0;

        err = clGetPlatformIDs(0, NULL, &num_platforms);

        if(err != CL_SUCCESS){
                printf("clGetPlatformIDs failed with err %d\n", err);
                exit(-1);
        }

	retp->err |= err;

        printf("[clGetPlatformIDs_server] Num OpenCL platforms found %d\n", num_platforms);
	retp->num_platforms_found = num_platforms;

        if(num_platforms > 0){

		cl_platform_id *platforms = (cl_platform_id *)malloc(sizeof(cl_platform_id)* num_platforms);

		clGetPlatformIDs(num_platforms, platforms, NULL);

                if(err != CL_SUCCESS){
                        printf("clGetPlatformIDs failed with err %d\n", err);
                        exit(-1);
                }

		retp->err |= err;

		for(int i=0; i<num_platforms; i++){
			printf("[clGetPlatformIDs_server] platforms[%d]=%p\n",i, platforms[i]);
		}

		retp->platforms.buff_ptr = (char *)platforms;
		retp->platforms.buff_len = num_platforms * sizeof(cl_platform_id);
	}else{

		retp->platforms.buff_ptr = "\0";
		retp->platforms.buff_len = sizeof(char);	
	}
}

void clGetPlatformIDs_server_wrapper(struct svc_req *rqstp, register SVCXPRT *transp){

	xdrproc_t xdr_arg, xdr_ret;

	xdr_arg = (xdrproc_t)_xdr_get_platform_ids;
	xdr_ret = (xdrproc_t)_xdr_get_platform_ids;

	get_platform_ids_ arg_pkt, ret_pkt;

	memset((char *)&arg_pkt, 0, sizeof(get_platform_ids_));
	memset((char *)&ret_pkt, 0, sizeof(get_platform_ids_));

	arg_pkt.platforms.buff_ptr = NULL;

	if (!svc_getargs (transp, (xdrproc_t) xdr_arg, (char *) &arg_pkt)) {
		svcerr_decode(transp);
		exit(-1);
	}
	printf("[clGetPlatformIDs_server_wrapper] svc_getargs OK\n");

	clGetPlatformIDs_server(&arg_pkt, &ret_pkt);	
	printf("[clGetPlatformIDs_server_wrapper] clCall_server OK\n");

        if (!svc_sendreply(transp, (xdrproc_t) xdr_ret, (char *)&ret_pkt)) {
                svcerr_systemerr (transp);
		exit(-1);
        }
	printf("[clGetPlatformIDs_server_wrapper] svc_sendreply OK\n");

        if (!svc_freeargs (transp, (xdrproc_t) xdr_arg, (caddr_t) &arg_pkt)) {
                printf ("%s", "unable to free arguments");
                exit (-1);
        }
	printf("[clGetPlatformIDs_server_wrapper] svc_freeargs OK\n");

        return;

}

void clGetDeviceIDs_server(get_device_ids_ *argp, get_device_ids_ *retp){

	cl_int err = CL_SUCCESS;
	retp->err = err;

        cl_uint num_devices = 0;

	printf("[clGetDeviceIDs_server] platform %p\n", (cl_platform_id)(argp->platform));
	printf("[clGetDeviceIDs_server] device_type %d\n", (cl_device_type)(argp->device_type));


        err = clGetDeviceIDs((cl_platform_id)(argp->platform), (cl_device_type)(argp->device_type), 0, NULL, &num_devices);

        if(err != CL_SUCCESS){
                printf("clGetDeviceIDs failed with err %d\n", err);
                exit(-1);
        }
	retp->err |= err;

        printf("[clGetDeviceIDs_server] Num OpenCL devices found %d\n", num_devices);
	retp->num_devices_found = num_devices;

        if(num_devices > 0){

		cl_device_id *devices = (cl_device_id *)malloc(sizeof(cl_device_id)* num_devices);

		clGetDeviceIDs((cl_platform_id)(argp->platform), (cl_device_type)(argp->device_type), num_devices, devices, NULL);

                if(err != CL_SUCCESS){
                        printf("clGetDeviceIDs failed with err %d\n", err);
                        exit(-1);
                }
		retp->err |= err;

		for(int i=0; i<num_devices; i++){
			printf("[clGetDeviceIDs_server] devices[%d]=%p\n",i, devices[i]);
		}

		retp->devices.buff_ptr = (char *)devices;
		retp->devices.buff_len = num_devices * sizeof(cl_device_id);
	}else{

		retp->devices.buff_ptr = "\0";
		retp->devices.buff_len = sizeof(char);	
	}
}

void clGetDeviceIDs_server_wrapper(struct svc_req *rqstp, register SVCXPRT *transp){

	xdrproc_t xdr_arg, xdr_ret;

	xdr_arg = (xdrproc_t)_xdr_get_device_ids;
	xdr_ret = (xdrproc_t)_xdr_get_device_ids;

	get_device_ids_ arg_pkt, ret_pkt;

	memset((char *)&arg_pkt, 0, sizeof(get_device_ids_));
	memset((char *)&ret_pkt, 0, sizeof(get_device_ids_));

	arg_pkt.devices.buff_ptr = NULL;

	if (!svc_getargs (transp, (xdrproc_t) xdr_arg, (char *) &arg_pkt)) {
		svcerr_decode(transp);
		exit(-1);
	}
	printf("[clGetDeviceIDs_server_wrapper] svc_getargs OK\n");

	clGetDeviceIDs_server(&arg_pkt, &ret_pkt);	
	printf("[clGetDeviceIDs_server_wrapper] clCall_server OK\n");

        if (!svc_sendreply(transp, (xdrproc_t) xdr_ret, (char *)&ret_pkt)) {
                svcerr_systemerr (transp);
		exit(-1);
        }
	printf("[clGetDeviceIDs_server_wrapper] svc_sendreply OK\n");

        if (!svc_freeargs (transp, (xdrproc_t) xdr_arg, (caddr_t) &arg_pkt)) {
                printf ("%s", "unable to free arguments");
                exit (-1);
        }
	printf("[clGetDeviceIDs_server_wrapper] svc_freeargs OK\n");

        return;

}

void clCreateContext_server(create_context_ *argp, create_context_ *retp){

	cl_int err = CL_SUCCESS;
	retp->err = err;

        cl_context context = 0;

        printf("[clCreateContext_server] Num devices received %d\n", argp->num_devices);

	cl_device_id *devices = (cl_device_id*)(argp->devices.buff_ptr);

	for(int i=0; i<argp->num_devices; i++){
		printf("[clCreateContext_server] devices[%d] = %p\n", i, devices[i]);
	}

        context  = clCreateContext(NULL, (cl_uint)(argp->num_devices), devices, NULL, NULL, &err);

        if(err != CL_SUCCESS){
                printf("clCreateContext failed with err %d\n", err);
                exit(-1);
        }
	retp->err |= err;

	retp->context = (unsigned long)context;
        printf("[clCreateContext_server] context created %p\n", retp->context);

	retp->devices.buff_ptr = "\0";
	retp->devices.buff_len = sizeof(char);	
}

void clCreateContext_server_wrapper(struct svc_req *rqstp, register SVCXPRT *transp){

	xdrproc_t xdr_arg, xdr_ret;

	xdr_arg = (xdrproc_t)_xdr_create_context;
	xdr_ret = (xdrproc_t)_xdr_create_context;

	create_context_ arg_pkt, ret_pkt;

	memset((char *)&arg_pkt, 0, sizeof(create_context_));
	memset((char *)&ret_pkt, 0, sizeof(create_context_));

	arg_pkt.devices.buff_ptr = NULL;

	if (!svc_getargs (transp, (xdrproc_t) xdr_arg, (char *) &arg_pkt)) {
		svcerr_decode(transp);
		exit(-1);
	}
	printf("[clCreateContext_server_wrapper] svc_getargs OK\n");

	clCreateContext_server(&arg_pkt, &ret_pkt);	
	printf("[clCreateContext_server_wrapper] clCall_server OK\n");

        if (!svc_sendreply(transp, (xdrproc_t) xdr_ret, (char *)&ret_pkt)) {
                svcerr_systemerr (transp);
		exit(-1);
        }
	printf("[clCreateContext_server_wrapper] svc_sendreply OK\n");

        if (!svc_freeargs (transp, (xdrproc_t) xdr_arg, (caddr_t) &arg_pkt)) {
                printf ("%s", "unable to free arguments");
                exit (-1);
        }
	printf("[clCreateContext_server_wrapper] svc_freeargs OK\n");

        return;

}

void clCreateCommandQueue_server(create_command_queue_ *argp, create_command_queue_ *retp){

	cl_int err = CL_SUCCESS;

        cl_command_queue command_queue = 0;

        printf("[clCreateCommandQueue_server] context %p\n", argp->context);
        printf("[clCreateCommandQueue_server] device %p\n", argp->device);

        command_queue  = clCreateCommandQueue((cl_context)(argp->context), (cl_device_id)(argp->device), 0, &err);

        if(err != CL_SUCCESS){
                printf("clCreateCommandQueue failed with err %d\n", err);
                exit(-1);
        }
	retp->err = err;

	retp->command_queue = (unsigned long)command_queue;
        printf("[clCreateCommandQueue_server] command_queue created %p\n", retp->command_queue);

}

void clCreateCommandQueue_server_wrapper(struct svc_req *rqstp, register SVCXPRT *transp){

	xdrproc_t xdr_arg, xdr_ret;

	xdr_arg = (xdrproc_t)_xdr_create_command_queue;
	xdr_ret = (xdrproc_t)_xdr_create_command_queue;

	create_command_queue_ arg_pkt, ret_pkt;

	memset((char *)&arg_pkt, 0, sizeof(create_command_queue_));
	memset((char *)&ret_pkt, 0, sizeof(create_command_queue_));

	if (!svc_getargs (transp, (xdrproc_t) xdr_arg, (char *) &arg_pkt)) {
		svcerr_decode(transp);
		exit(-1);
	}
	printf("[clCreateCommandQueue_server_wrapper] svc_getargs OK\n");

	clCreateCommandQueue_server(&arg_pkt, &ret_pkt);	
	printf("[clCreateCommandQueue_server_wrapper] clCall_server OK\n");

        if (!svc_sendreply(transp, (xdrproc_t) xdr_ret, (char *)&ret_pkt)) {
                svcerr_systemerr (transp);
		exit(-1);
        }
	printf("[clCreateCommandQueue_server_wrapper] svc_sendreply OK\n");

        if (!svc_freeargs (transp, (xdrproc_t) xdr_arg, (caddr_t) &arg_pkt)) {
                printf ("%s", "unable to free arguments");
                exit (-1);
        }
	printf("[clCreateCommandQueue_server_wrapper] svc_freeargs OK\n");

        return;

}

void clCreateBuffer_server(create_buffer_ *argp, create_buffer_ *retp){

	cl_int err = CL_SUCCESS;

        cl_mem mem = 0;

        printf("[clCreateBuffer_server] context %p\n", argp->context);

	cl_mem_flags flags = (cl_mem_flags)(argp->flags);
	size_t size = (size_t)(argp->size);
	void *host_ptr = NULL;

	bool use_host_ptr = flags & CL_MEM_USE_HOST_PTR;

	bool copy_host_ptr = flags & CL_MEM_COPY_HOST_PTR;

	if(use_host_ptr){
		host_ptr = malloc(size);
	} else if (copy_host_ptr) {
		host_ptr = (void *)(argp->data.buff_ptr);
	}
        mem  = clCreateBuffer((cl_context)(argp->context), flags, size, host_ptr, &err);

        if(err != CL_SUCCESS){
                printf("clCreateBuffer failed with err %d\n", err);
                exit(-1);
        }
	retp->err = err;

	retp->data.buff_ptr = "\0";
	retp->data.buff_len = sizeof(char);	

	retp->mem = (unsigned long)mem;

        printf("[clCreateBuffer_server] mem created %p\n", retp->mem);

}

void clCreateBuffer_server_wrapper(struct svc_req *rqstp, register SVCXPRT *transp){

	xdrproc_t xdr_arg, xdr_ret;

	xdr_arg = (xdrproc_t)_xdr_create_buffer;
	xdr_ret = (xdrproc_t)_xdr_create_buffer;

	create_buffer_ arg_pkt, ret_pkt;

	memset((char *)&arg_pkt, 0, sizeof(create_buffer_));
	memset((char *)&ret_pkt, 0, sizeof(create_buffer_));

	arg_pkt.data.buff_ptr = NULL;

	if (!svc_getargs (transp, (xdrproc_t) xdr_arg, (char *) &arg_pkt)) {
		svcerr_decode(transp);
		exit(-1);
	}
	printf("[clCreateBuffer_server_wrapper] svc_getargs OK\n");

	clCreateBuffer_server(&arg_pkt, &ret_pkt);	
	printf("[clCreateBuffer_server_wrapper] clCall_server OK\n");

        if (!svc_sendreply(transp, (xdrproc_t) xdr_ret, (char *)&ret_pkt)) {
                svcerr_systemerr (transp);
		exit(-1);
        }
	printf("[clCreateBuffer_server_wrapper] svc_sendreply OK\n");

        if (!svc_freeargs (transp, (xdrproc_t) xdr_arg, (caddr_t) &arg_pkt)) {
                printf ("%s", "unable to free arguments");
                exit (-1);
        }
	printf("[clCreateBuffer_server_wrapper] svc_freeargs OK\n");

        return;

}

void clCreateProgramWithSource_server(create_program_with_source_ *argp, create_program_with_source_ *retp){

	cl_int err = CL_SUCCESS;

        cl_program program = 0;

        printf("[clCreateProgramWithSource_server] context %p\n", argp->context);

        program  = clCreateProgramWithSource((cl_context)(argp->context), 1, (const char **)&(argp->program_str.buff_ptr), NULL, &err);

        if(err != CL_SUCCESS){
                printf("clCreateProgramWithSource failed with err %d\n", err);
                exit(-1);
        }
	retp->err = err;

	retp->program_str.buff_ptr = "\0";
	retp->program_str.buff_len = sizeof(char);	

	retp->program = (unsigned long)program;

        printf("[clCreateProgramWithSource_server] program created %p\n", retp->program);

}

void clCreateProgramWithSource_server_wrapper(struct svc_req *rqstp, register SVCXPRT *transp){

	xdrproc_t xdr_arg, xdr_ret;

	xdr_arg = (xdrproc_t)_xdr_create_program_with_source;
	xdr_ret = (xdrproc_t)_xdr_create_program_with_source;

	create_program_with_source_ arg_pkt, ret_pkt;

	memset((char *)&arg_pkt, 0, sizeof(create_program_with_source_));
	memset((char *)&ret_pkt, 0, sizeof(create_program_with_source_));

	arg_pkt.program_str.buff_ptr = NULL;

	if (!svc_getargs (transp, (xdrproc_t) xdr_arg, (char *) &arg_pkt)) {
		svcerr_decode(transp);
		exit(-1);
	}
	printf("[clCreateProgramWithSource_server_wrapper] svc_getargs OK\n");

	clCreateProgramWithSource_server(&arg_pkt, &ret_pkt);
	printf("[clCreateProgramWithSource_server_wrapper] clCall_server OK\n");

        if (!svc_sendreply(transp, (xdrproc_t) xdr_ret, (char *)&ret_pkt)) {
                svcerr_systemerr (transp);
		exit(-1);
        }
	printf("[clCreateProgramWithSource_server_wrapper] svc_sendreply OK\n");

        if (!svc_freeargs (transp, (xdrproc_t) xdr_arg, (caddr_t) &arg_pkt)) {
                printf ("%s", "unable to free arguments");
                exit (-1);
        }
	printf("[clCreateProgramWithSource_server_wrapper] svc_freeargs OK\n");

        return;
}

void clBuildProgram_server(build_program_ *argp, build_program_ *retp){

	cl_int err = CL_SUCCESS;

        printf("[clBuildProgram_server] program %p\n", argp->program);
	printf("[clBuildProgram_server] options %s\n", argp->options.buff_ptr);
	
	if(argp->all_devices){
		err  = clBuildProgram((cl_program)(argp->program), 0, NULL, (const char *)(argp->options.buff_ptr), NULL, NULL);
	} else {
		err  = clBuildProgram((cl_program)(argp->program), (argp->num_devices), (cl_device_id *)(argp->devices.buff_ptr), (const char *)(argp->options.buff_ptr), NULL, NULL);
	}
        if(err != CL_SUCCESS){
                printf("clBuildProgram failed with err %d\n", err);
                exit(-1);
        }
	retp->err = err;

	retp->devices.buff_ptr = "\0";
	retp->devices.buff_len = sizeof(char);	

	retp->options.buff_ptr = "\0";
	retp->options.buff_len = sizeof(char);	

}

void clBuildProgram_server_wrapper(struct svc_req *rqstp, register SVCXPRT *transp){

	xdrproc_t xdr_arg, xdr_ret;

	xdr_arg = (xdrproc_t)_xdr_build_program;
	xdr_ret = (xdrproc_t)_xdr_build_program;

	build_program_ arg_pkt, ret_pkt;

	memset((char *)&arg_pkt, 0, sizeof(build_program_));
	memset((char *)&ret_pkt, 0, sizeof(build_program_));

	arg_pkt.devices.buff_ptr = NULL;
	arg_pkt.options.buff_ptr = NULL;

	if (!svc_getargs (transp, (xdrproc_t) xdr_arg, (char *) &arg_pkt)) {
		svcerr_decode(transp);
		exit(-1);
	}
	printf("[clBuildProgram_server_wrapper] svc_getargs OK\n");

	clBuildProgram_server(&arg_pkt, &ret_pkt);
	printf("[clBuildProgram_server_wrapper] clCall_server OK\n");

        if (!svc_sendreply(transp, (xdrproc_t) xdr_ret, (char *)&ret_pkt)) {
                svcerr_systemerr (transp);
		exit(-1);
        }
	printf("[clBuildProgram_server_wrapper] svc_sendreply OK\n");

        if (!svc_freeargs (transp, (xdrproc_t) xdr_arg, (caddr_t) &arg_pkt)) {
                printf ("%s", "unable to free arguments");
                exit (-1);
        }
	printf("[clBuildProgram_server_wrapper] svc_freeargs OK\n");

        return;
}

void clCreateKernel_server(create_kernel_ *argp, create_kernel_ *retp){

	cl_int err = CL_SUCCESS;

        cl_kernel kernel = 0;

        printf("[clCreateKernel_server] program %p\n", argp->program);
        printf("[clCreateKernel_server] kernel_name %s\n", argp->kernel_name.buff_ptr);
        printf("[clCreateKernel_server] kernel_name length %d\n", argp->kernel_name.buff_len);

	char *kernel_name = (char *)calloc(argp->kernel_name.buff_len + 1, sizeof(char));
	for(int i=0; i<argp->kernel_name.buff_len; i++){
		kernel_name[i] = *((argp->kernel_name.buff_ptr) + i);
	}
	kernel_name[argp->kernel_name.buff_len] = '\0'; 

        //kernel  = clCreateKernel((cl_program)(argp->program), (const char *)(argp->kernel_name.buff_ptr), &err);
        //if(err != CL_SUCCESS){
        //        printf("clCreateKernel failed with err %d\n", err);
        //        exit(-1);
        //}

	err = CL_SUCCESS;
        kernel  = clCreateKernel((cl_program)(argp->program), kernel_name, &err);
        if(err != CL_SUCCESS){
                printf("clCreateKernel failed with err %d\n", err);
                exit(-1);
        }

	retp->err = err;

	retp->kernel_name.buff_ptr = "\0";
	retp->kernel_name.buff_len = sizeof(char);	

	retp->kernel = (unsigned long)kernel;

        printf("[clCreateKernel_server] kernel created %p\n", retp->kernel);

}

void clCreateKernel_server_wrapper(struct svc_req *rqstp, register SVCXPRT *transp){

	xdrproc_t xdr_arg, xdr_ret;

	xdr_arg = (xdrproc_t)_xdr_create_kernel;
	xdr_ret = (xdrproc_t)_xdr_create_kernel;

	create_kernel_ arg_pkt, ret_pkt;

	memset((char *)&arg_pkt, 0, sizeof(create_kernel_));
	memset((char *)&ret_pkt, 0, sizeof(create_kernel_));

	arg_pkt.kernel_name.buff_ptr = NULL;

	if (!svc_getargs (transp, (xdrproc_t) xdr_arg, (char *) &arg_pkt)) {
		svcerr_decode(transp);
		exit(-1);
	}
	printf("[clCreateKernel_server_wrapper] svc_getargs OK\n");

	clCreateKernel_server(&arg_pkt, &ret_pkt);
	printf("[clCreateKernel_server_wrapper] clCall_server OK\n");

        if (!svc_sendreply(transp, (xdrproc_t) xdr_ret, (char *)&ret_pkt)) {
                svcerr_systemerr (transp);
		exit(-1);
        }
	printf("[clCreateKernel_server_wrapper] svc_sendreply OK\n");

        if (!svc_freeargs (transp, (xdrproc_t) xdr_arg, (caddr_t) &arg_pkt)) {
                printf ("%s", "unable to free arguments");
                exit (-1);
        }
	printf("[clCreateKernel_server_wrapper] svc_freeargs OK\n");

        return;
}

void clSetKernelArg_server(set_kernel_arg_ *argp, set_kernel_arg_ *retp){

	cl_int err = CL_SUCCESS;

        cl_kernel kernel = 0;

        printf("[clSetKernelArg_server] kernel %p\n", argp->kernel);

	if(argp->is_null_arg){
		err  = clSetKernelArg((cl_kernel)(argp->kernel), argp->arg_index, argp->arg_size, NULL);
	} else if (argp->is_clobj) {
		if(argp->is_mem){
			cl_mem mem = (cl_mem)(argp->mem);
			printf("[clSetKernelArg_server] mem %p\n", mem);
			assert(argp->arg_size == sizeof(cl_mem));
			err = clSetKernelArg((cl_kernel)(argp->kernel), argp->arg_index, sizeof(cl_mem), (void *)&mem);
		} else if (argp->is_image){
			//cl_image not supported in the runtime version installed on shiva
			//cl_image image = (cl_image)(argp->image);
			//assert(argp->arg_size == sizeof(cl_image));
			//err = clSetKernelArg((cl_kernel)(argp->kernel), argp->arg_index, sizeof(cl_image), (void *)&image);
		} else if (argp->is_sampler) {
			cl_sampler sampler = (cl_sampler)(argp->sampler);
			assert(argp->arg_size == sizeof(cl_sampler));
			err = clSetKernelArg((cl_kernel)(argp->kernel), argp->arg_index, sizeof(cl_sampler), (void *)&sampler);
		} else {
			assert(0); //should not be here
		}

	} else {
		err  = clSetKernelArg((cl_kernel)(argp->kernel), argp->arg_index, argp->arg_size, (void *)(argp->plain_old_data.buff_ptr));
	}

        if(err != CL_SUCCESS){
                printf("clCreateKernel failed with err %d\n", err);
                exit(-1);
        }
	retp->err = err;

	retp->plain_old_data.buff_ptr = "\0";
	retp->plain_old_data.buff_len = sizeof(char);	

}

void clSetKernelArg_server_wrapper(struct svc_req *rqstp, register SVCXPRT *transp){

	xdrproc_t xdr_arg, xdr_ret;

	xdr_arg = (xdrproc_t)_xdr_set_kernel_arg;
	xdr_ret = (xdrproc_t)_xdr_set_kernel_arg;

	set_kernel_arg_ arg_pkt, ret_pkt;

	memset((char *)&arg_pkt, 0, sizeof(set_kernel_arg_));
	memset((char *)&ret_pkt, 0, sizeof(set_kernel_arg_));

	arg_pkt.plain_old_data.buff_ptr = NULL;

	printf("[clSetKernelArg_server_wrapper] svc_getargs starting\n");
	if (!svc_getargs (transp, (xdrproc_t) xdr_arg, (char *) &arg_pkt)) {
		svcerr_decode(transp);
		exit(-1);
	}
	printf("[clSetKernelArg_server_wrapper] svc_getargs OK\n");

	clSetKernelArg_server(&arg_pkt, &ret_pkt);
	printf("[clSetKernelArg_server_wrapper] clCall_server OK\n");

        if (!svc_sendreply(transp, (xdrproc_t) xdr_ret, (char *)&ret_pkt)) {
                svcerr_systemerr (transp);
		exit(-1);
        }
	printf("[clSetKernelArg_server_wrapper] svc_sendreply OK\n");

        if (!svc_freeargs (transp, (xdrproc_t) xdr_arg, (caddr_t) &arg_pkt)) {
                printf ("%s", "unable to free arguments");
                exit (-1);
        }
	printf("[clSetKernelArg_server_wrapper] svc_freeargs OK\n");

        return;
}

void clEnqueueWriteBuffer_server(enqueue_write_buffer_ *argp, enqueue_write_buffer_ *retp){

	cl_int err = CL_SUCCESS;

        printf("[clEnqueueWriteBuffer_server] mem %p\n", argp->mem);
        printf("[clEnqueueWriteBuffer_server] command queue %p\n", argp->command_queue);

        err  = clEnqueueWriteBuffer((cl_command_queue)(argp->command_queue), (cl_mem)(argp->mem), argp->blocking, argp->offset, argp->size, (void *)(argp->data.buff_ptr), 0, NULL, NULL);

        if(err != CL_SUCCESS){
                printf("clEnqueueWriteBuffer failed with err %d\n", err);
                exit(-1);
        }
	retp->err = err;

	retp->data.buff_ptr = "\0";
	retp->data.buff_len = sizeof(char);

        printf("[clEnqueueWriteBuffer_server]err returned %d\n", retp->err);

}

void clEnqueueWriteBuffer_server_wrapper(struct svc_req *rqstp, register SVCXPRT *transp){

	xdrproc_t xdr_arg, xdr_ret;

	xdr_arg = (xdrproc_t)_xdr_enqueue_write_buffer;
	xdr_ret = (xdrproc_t)_xdr_enqueue_write_buffer;

	enqueue_write_buffer_ arg_pkt, ret_pkt;

	memset((char *)&arg_pkt, 0, sizeof(enqueue_write_buffer_));
	memset((char *)&ret_pkt, 0, sizeof(enqueue_write_buffer_));

	arg_pkt.data.buff_ptr = NULL;

	if (!svc_getargs (transp, (xdrproc_t) xdr_arg, (char *) &arg_pkt)) {
		svcerr_decode(transp);
		exit(-1);
	}
	printf("[clEnqueueWriteBuffer_server_wrapper] svc_getargs OK\n");

	clEnqueueWriteBuffer_server(&arg_pkt, &ret_pkt);	
	printf("[clEnqueueWriteBuffer_server_wrapper] clCall_server OK\n");

        if (!svc_sendreply(transp, (xdrproc_t) xdr_ret, (char *)&ret_pkt)) {
                svcerr_systemerr (transp);
		exit(-1);
        }
	printf("[clEnqueueWriteBuffer_server_wrapper] svc_sendreply OK\n");

        if (!svc_freeargs (transp, (xdrproc_t) xdr_arg, (caddr_t) &arg_pkt)) {
                printf ("%s", "unable to free arguments");
                exit (-1);
        }
	printf("[clEnqueueWriteBuffer_server_wrapper] svc_freeargs OK\n");

        return;

}

void clEnqueueNDRangeKernel_server(enqueue_ndrange_kernel_ *argp, enqueue_ndrange_kernel_ *retp){

	cl_int err = CL_SUCCESS;

        printf("[clEnqueueNDRangeKernel_server] kernel %p\n", argp->kernel);
        printf("[clEnqueueNDRangeKernel_server] command queue %p\n", argp->command_queue);

	size_t *global_work_offset=NULL, *local_work_size=NULL;

	if(strcmp(argp->global_offset.buff_ptr, "\0")){
		global_work_offset = (size_t *)argp->global_offset.buff_ptr;
	}

	if(strcmp(argp->local_size.buff_ptr, "\0")){
		local_work_size = (size_t *)argp->local_size.buff_ptr;
	}

        //err  = clEnqueueNDRangeKernel((cl_command_queue)(argp->command_queue), (cl_kernel)(argp->kernel), argp->work_dim, (const size_t *)(argp->global_offset.buff_ptr), (const size_t *)(argp->global_size.buff_ptr), (const size_t *)(argp->local_size.buff_ptr), 0, NULL, NULL);
        err  = clEnqueueNDRangeKernel((cl_command_queue)(argp->command_queue), (cl_kernel)(argp->kernel), argp->work_dim, (const size_t *)global_work_offset, (const size_t *)(argp->global_size.buff_ptr), (const size_t *)local_work_size, 0, NULL, NULL);

        if(err != CL_SUCCESS){
                printf("clEnqueueNDRangeKernel failed with err %d\n", err);
                exit(-1);
        }
	retp->err = err;

	retp->global_offset.buff_ptr = "\0";
	retp->global_offset.buff_len = sizeof(char);

	retp->global_size.buff_ptr = "\0";
	retp->global_size.buff_len = sizeof(char);

	retp->local_size.buff_ptr = "\0";
	retp->local_size.buff_len = sizeof(char);

        printf("[clEnqueueNDRangeKernel_server]err returned %d\n", retp->err);

}

void clEnqueueNDRangeKernel_server_wrapper(struct svc_req *rqstp, register SVCXPRT *transp){

	xdrproc_t xdr_arg, xdr_ret;

	xdr_arg = (xdrproc_t)_xdr_enqueue_ndrange_kernel;
	xdr_ret = (xdrproc_t)_xdr_enqueue_ndrange_kernel;

	enqueue_ndrange_kernel_ arg_pkt, ret_pkt;

	memset((char *)&arg_pkt, 0, sizeof(enqueue_ndrange_kernel_));
	memset((char *)&ret_pkt, 0, sizeof(enqueue_ndrange_kernel_));

	arg_pkt.global_offset.buff_ptr = NULL;
	arg_pkt.global_size.buff_ptr = NULL;
	arg_pkt.local_size.buff_ptr = NULL;

	if (!svc_getargs (transp, (xdrproc_t) xdr_arg, (char *) &arg_pkt)) {
		svcerr_decode(transp);
		exit(-1);
	}
	printf("[clEnqueueNDRangeKernel_server_wrapper] svc_getargs OK\n");

	clEnqueueNDRangeKernel_server(&arg_pkt, &ret_pkt);	
	printf("[clEnqueueNDRangeKernel_server_wrapper] clCall_server OK\n");

        if (!svc_sendreply(transp, (xdrproc_t) xdr_ret, (char *)&ret_pkt)) {
                svcerr_systemerr (transp);
		exit(-1);
        }
	printf("[clEnqueueNDRangeKernel_server_wrapper] svc_sendreply OK\n");

        if (!svc_freeargs (transp, (xdrproc_t) xdr_arg, (caddr_t) &arg_pkt)) {
                printf ("%s", "unable to free arguments");
                exit (-1);
        }
	printf("[clEnqueueNDRangeKernel_server_wrapper] svc_freeargs OK\n");

        return;

}

void clEnqueueReadBuffer_server(enqueue_read_buffer_ *argp, enqueue_read_buffer_ *retp){

	cl_int err = CL_SUCCESS;

        printf("[clEnqueueReadBuffer_server] mem %p\n", argp->mem);
        printf("[clEnqueueReadBuffer_server] command queue %p\n", argp->command_queue);

	void *ptr = malloc(argp->size);
        err  = clEnqueueReadBuffer((cl_command_queue)(argp->command_queue), (cl_mem)(argp->mem), argp->blocking, argp->offset, argp->size, ptr, 0, NULL, NULL);

        if(err != CL_SUCCESS){
                printf("clEnqueueReadBuffer failed with err %d\n", err);
                exit(-1);
        }
	retp->err = err;

	retp->data.buff_ptr = (char *)ptr;
	retp->data.buff_len = argp->size;

        printf("[clEnqueueReadBuffer_server]err returned %d\n", retp->err);

}

void clEnqueueReadBuffer_server_wrapper(struct svc_req *rqstp, register SVCXPRT *transp){

	xdrproc_t xdr_arg, xdr_ret;

	xdr_arg = (xdrproc_t)_xdr_enqueue_read_buffer;
	xdr_ret = (xdrproc_t)_xdr_enqueue_read_buffer;

	enqueue_read_buffer_ arg_pkt, ret_pkt;

	memset((char *)&arg_pkt, 0, sizeof(enqueue_read_buffer_));
	memset((char *)&ret_pkt, 0, sizeof(enqueue_read_buffer_));

	arg_pkt.data.buff_ptr = NULL;

	if (!svc_getargs (transp, (xdrproc_t) xdr_arg, (char *) &arg_pkt)) {
		svcerr_decode(transp);
		exit(-1);
	}
	printf("[clEnqueueReadBuffer_server_wrapper] svc_getargs OK\n");

	clEnqueueReadBuffer_server(&arg_pkt, &ret_pkt);	
	printf("[clEnqueueReadBuffer_server_wrapper] clCall_server OK\n");

        if (!svc_sendreply(transp, (xdrproc_t) xdr_ret, (char *)&ret_pkt)) {
                svcerr_systemerr (transp);
		exit(-1);
        }
	printf("[clEnqueueReadBuffer_server_wrapper] svc_sendreply OK\n");

        if (!svc_freeargs (transp, (xdrproc_t) xdr_arg, (caddr_t) &arg_pkt)) {
                printf ("%s", "unable to free arguments");
                exit (-1);
        }
	printf("[clEnqueueReadBuffer_server_wrapper] svc_freeargs OK\n");

        return;

}

int main(){

        SVCXPRT *transp;

	int sock;

       /* Create the socket. */
       /*sock = socket (PF_INET, SOCK_STREAM, 0);
       if (sock < 0)
       {
       	perror ("socket");
       	exit (EXIT_FAILURE);
       }*/


        transp = svctcp_create(RPC_ANYSOCK, 0, 0);
        if (transp == NULL) {
                printf ("%s", "cannot create tcp service.");
                exit(-1);
        }
	printf("[main] svctcp_create OK\n");

	//can't find in rpc.h, so commenting for now
        //pmap_unset (GET_PLATFORM_IDS_PROG, GET_PLATFORM_IDS_VERS);
	//printf("pmap_unset OK\n");

	svc_unregister(GET_PLATFORM_IDS_PROG, GET_PLATFORM_IDS_VERS);
	pmap_unset(GET_PLATFORM_IDS_PROG, GET_PLATFORM_IDS_VERS);

        if (!svc_register(transp, GET_PLATFORM_IDS_PROG, GET_PLATFORM_IDS_VERS,clGetPlatformIDs_server_wrapper, IPPROTO_TCP)) {
                printf ("%s", "unable to register (GET_PLATFORM_IDS_PROG, GET_PLATFORM_IDS_VERS, tcp).");
                exit(-1);
        }

	printf("[main] svctcp_register GET_PLATFORM_IDS_PROG OK\n");

	svc_unregister(GET_DEVICE_IDS_PROG, GET_DEVICE_IDS_VERS);
	pmap_unset(GET_DEVICE_IDS_PROG, GET_DEVICE_IDS_VERS);

        if (!svc_register(transp, GET_DEVICE_IDS_PROG, GET_DEVICE_IDS_VERS,clGetDeviceIDs_server_wrapper, IPPROTO_TCP)) {
                printf ("%s", "unable to register (GET_DEVICE_IDS_PROG, GET_DEVICE_IDS_VERS, tcp).");
                exit(-1);
        }

	printf("[main] svctcp_register GET_DEVICE_IDS_PROG OK\n");

	svc_unregister(CREATE_CONTEXT_PROG, CREATE_CONTEXT_VERS);
	pmap_unset(CREATE_CONTEXT_PROG, CREATE_CONTEXT_VERS);

        if (!svc_register(transp, CREATE_CONTEXT_PROG, CREATE_CONTEXT_VERS,clCreateContext_server_wrapper, IPPROTO_TCP)) {
                printf ("%s", "unable to register (CREATE_CONTEXT_PROG, CREATE_CONTEXT_VERS, tcp).");
                exit(-1);
        }

	printf("[main] svctcp_register CREATE_CONTEXT_PROG OK\n");

	svc_unregister(CREATE_COMMAND_QUEUE_PROG, CREATE_COMMAND_QUEUE_VERS);
	pmap_unset(CREATE_COMMAND_QUEUE_PROG, CREATE_COMMAND_QUEUE_VERS);

        if (!svc_register(transp, CREATE_COMMAND_QUEUE_PROG, CREATE_COMMAND_QUEUE_VERS,clCreateCommandQueue_server_wrapper, IPPROTO_TCP)) {
                printf ("%s", "unable to register (CREATE_COMMAND_QUEUE_PROG, CREATE_COMMAND_QUEUE_VERS, tcp).");
                exit(-1);
        }

	printf("[main] svctcp_register CREATE_COMMAND_QUEUE_PROG OK\n");

	svc_unregister(CREATE_BUFFER_PROG, CREATE_BUFFER_VERS);
	pmap_unset(CREATE_BUFFER_PROG, CREATE_BUFFER_VERS);

        if (!svc_register(transp, CREATE_BUFFER_PROG, CREATE_BUFFER_VERS,clCreateBuffer_server_wrapper, IPPROTO_TCP)) {
                printf ("%s", "unable to register (CREATE_BUFFER_PROG, CREATE_BUFFER_VERS, tcp).");
                exit(-1);
        }

	printf("[main] svctcp_register CREATE_BUFFER_PROG OK\n");

	svc_unregister(CREATE_PROGRAM_WITH_SOURCE_PROG, CREATE_PROGRAM_WITH_SOURCE_VERS);
	pmap_unset(CREATE_PROGRAM_WITH_SOURCE_PROG, CREATE_PROGRAM_WITH_SOURCE_VERS);

        if (!svc_register(transp, CREATE_PROGRAM_WITH_SOURCE_PROG, CREATE_PROGRAM_WITH_SOURCE_VERS,clCreateProgramWithSource_server_wrapper, IPPROTO_TCP)) {
                printf ("%s", "unable to register (CREATE_PROGRAM_WITH_SOURCE_PROG, CREATE_PROGRAM_WITH_SOURCE_VERS, tcp).");
                exit(-1);
        }

	printf("[main] svctcp_register CREATE_PROGRAM_WITH_SOURCE_PROG OK\n");

	svc_unregister(BUILD_PROGRAM_PROG, BUILD_PROGRAM_VERS);
	pmap_unset(BUILD_PROGRAM_PROG, BUILD_PROGRAM_VERS);

        if (!svc_register(transp, BUILD_PROGRAM_PROG, BUILD_PROGRAM_VERS,clBuildProgram_server_wrapper, IPPROTO_TCP)) {
                printf ("%s", "unable to register (BUILD_PROGRAM_PROG, BUILD_PROGRAM_VERS, tcp).");
                exit(-1);
        }

	printf("[main] svctcp_register BUILD_PROGRAM_PROG OK\n");

	svc_unregister(CREATE_KERNEL_PROG, CREATE_KERNEL_VERS);
	pmap_unset(CREATE_KERNEL_PROG, CREATE_KERNEL_VERS);

        if (!svc_register(transp, CREATE_KERNEL_PROG, CREATE_KERNEL_VERS,clCreateKernel_server_wrapper, IPPROTO_TCP)) {
                printf ("%s", "unable to register (CREATE_KERNEL_PROG, CREATE_KERNEL_VERS, tcp).");
                exit(-1);
        }

	printf("[main] svctcp_register CREATE_KERNEL_PROG OK\n");

	svc_unregister(SET_KERNEL_ARG_PROG, SET_KERNEL_ARG_VERS);
	pmap_unset(SET_KERNEL_ARG_PROG, SET_KERNEL_ARG_VERS);

        if (!svc_register(transp, SET_KERNEL_ARG_PROG, SET_KERNEL_ARG_VERS,clSetKernelArg_server_wrapper, IPPROTO_TCP)) {
                printf ("%s", "unable to register (SET_KERNEL_ARG_PROG, SET_KERNEL_ARG_VERS, tcp).");
                exit(-1);
        }

	printf("[main] svctcp_register SET_KERNEL_ARG_PROG OK\n");

        svc_unregister(ENQUEUE_WRITE_BUFFER_PROG, ENQUEUE_WRITE_BUFFER_VERS);
        pmap_unset(ENQUEUE_WRITE_BUFFER_PROG, ENQUEUE_WRITE_BUFFER_VERS);

        if (!svc_register(transp, ENQUEUE_WRITE_BUFFER_PROG, ENQUEUE_WRITE_BUFFER_VERS,clEnqueueWriteBuffer_server_wrapper, IPPROTO_TCP)) {
                printf ("%s", "unable to register (ENQUEUE_WRITE_BUFFER_PROG, ENQUEUE_WRITE_BUFFER_VERS, tcp).");
                exit(-1);
        }

        printf("[main] svctcp_register ENQUEUE_WRITE_BUFFER_PROG OK\n");

        svc_unregister(ENQUEUE_READ_BUFFER_PROG, ENQUEUE_READ_BUFFER_VERS);
        pmap_unset(ENQUEUE_READ_BUFFER_PROG, ENQUEUE_READ_BUFFER_VERS);

        if (!svc_register(transp, ENQUEUE_READ_BUFFER_PROG, ENQUEUE_READ_BUFFER_VERS,clEnqueueReadBuffer_server_wrapper, IPPROTO_TCP)) {
                printf ("%s", "unable to register (ENQUEUE_READ_BUFFER_PROG, ENQUEUE_READ_BUFFER_VERS, tcp).");
                exit(-1);
        }

        printf("[main] svctcp_register ENQUEUE_READ_BUFFER_PROG OK\n");

        svc_unregister(ENQUEUE_NDRANGE_KERNEL_PROG, ENQUEUE_NDRANGE_KERNEL_VERS);
	pmap_unset(ENQUEUE_NDRANGE_KERNEL_PROG, ENQUEUE_NDRANGE_KERNEL_VERS);

        if (!svc_register(transp, ENQUEUE_NDRANGE_KERNEL_PROG, ENQUEUE_NDRANGE_KERNEL_VERS,clEnqueueNDRangeKernel_server_wrapper, IPPROTO_TCP)) {
                printf ("%s", "unable to register (ENQUEUE_NDRANGE_KERNEL_PROG, ENQUEUE_NDRANGE_KERNEL_VERS, tcp).");
                exit(-1);
        }

        printf("[main] svctcp_register ENQUEUE_NDRANGE_KERNEL_PROG OK\n");

	svc_run();

	printf("[main] this message should be unreachable");

	exit(-1);

}
