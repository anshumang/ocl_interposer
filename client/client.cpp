#include <stdio.h>
#include "CL/opencl.h"
#include <rpc/rpc.h>
#include "../client_server_common_includes.h"
#include "client_only_includes.h"

cl_int clGetPlatformIDs (cl_uint num_entries, cl_platform_id *platforms, cl_uint *num_platforms){

	return CL_SUCCESS;

}

cl_int clGetDeviceIDs (cl_platform_id platform,cl_device_type device_type, cl_uint num_entries,cl_device_id *devices, cl_uint *num_devices){

	return CL_SUCCESS;

}

cl_context clCreateContext (const cl_context_properties *properties,cl_uint num_devices, const cl_device_id *devices,void (CL_CALLBACK*pfn_notify)(const char *errinfo, const void *private_info,size_t cb, void *user_data),void *user_data, cl_int *errcode_ret){

	cl_context context = 0;

	*errcode_ret = CL_SUCCESS;
	return context;
}

cl_command_queue clCreateCommandQueue (cl_context context, cl_device_id device,cl_command_queue_properties properties,cl_int *errcode_ret){

	cl_command_queue command_queue = 0;

	*errcode_ret = CL_SUCCESS;
	return command_queue;
}

cl_mem clCreateBuffer (cl_context context, cl_mem_flags flags, size_t size, void *host_ptr, cl_int *errcode_ret){

	cl_mem buffer = 0;

	*errcode_ret = CL_SUCCESS;
	return buffer;
}

cl_program clCreateProgramWithSource (cl_context context, cl_uint count, const char **strings,const size_t *lengths, cl_int *errcode_ret){

	cl_program program = 0;
	
	*errcode_ret = CL_SUCCESS;
	return program;
}

cl_int clBuildProgram (cl_program program, cl_uint num_devices, const cl_device_id *device_list, const char *options, void (CL_CALLBACK*pfn_notify)(cl_program program, void *user_data), void *user_data){

	return CL_SUCCESS;

}

cl_kernel clCreateKernel (cl_program program,const char *kernel_name, cl_int *errcode_ret){

	cl_kernel kernel = 0;

	*errcode_ret = CL_SUCCESS;
	return kernel;
}

cl_int clSetKernelArg (cl_kernel kernel, cl_uint arg_index,size_t arg_size, const void *arg_value){

	return CL_SUCCESS;
}

cl_int clEnqueueWriteBuffer (cl_command_queue command_queue, cl_mem buffer,cl_bool blocking_write, size_t offset, size_t size,const void *ptr, cl_uint num_events_in_wait_list,const cl_event *event_wait_list, cl_event *event){

	return CL_SUCCESS;

}

cl_int clEnqueueReadBuffer (cl_command_queue command_queue, cl_mem buffer,cl_bool blocking_read, size_t offset, size_t size,const void *ptr, cl_uint num_events_in_wait_list,const cl_event *event_wait_list, cl_event *event){

	return CL_SUCCESS;

}
