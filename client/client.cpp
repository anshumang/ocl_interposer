#include <stdio.h>
#include "CL/opencl.h"
#include <rpc/rpc.h>
#include "../client_server_common_includes.h"
#include "client_only_includes.h"
#include <map>
#include <sys/socket.h>
#include <netdb.h>
#include <assert.h>

//This should be populated dynamically
char *nodes[] = {"shiva.cc.gt.atl.ga.us"};

cl_int clGetPlatformIDs (cl_uint num_entries, cl_platform_id *platforms, cl_uint *num_platforms){

//Don't send the RPC if the args are invalid
	if(!num_entries && platforms){
		return CL_INVALID_VALUE;
	}

	if(!num_platforms && !platforms){
		return CL_INVALID_VALUE;
	}

	int num_nodes = sizeof(nodes)/sizeof(char *);

	int num_platforms_found = 0;
 	std::map<int, int> num_platforms_per_node;
 	std::map<int, char*> platforms_per_node;

	cl_int err = CL_SUCCESS;	

	for(int i=0; i<num_nodes; i++){

		register CLIENT *clnt;
		int sock = RPC_ANYSOCK; /* can be also valid socket descriptor */
		struct hostent *hp;
		struct sockaddr_in server_addr;

		/* get the internet address of RPC server */
		if ((hp = gethostbyname(nodes[i])) == NULL){
   			printf("Can't get address for %s\n",nodes[i]);
   			exit (-1);
  		}

		bcopy(hp->h_addr, (caddr_t)&server_addr.sin_addr.s_addr, hp->h_length);
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = 0;

		/* create TCP handle */
		if ((clnt = clnttcp_create(&server_addr, GET_PLATFORM_IDS_PROG, GET_PLATFORM_IDS_VERS,
                            &sock, 0, 0)) == NULL){
    			clnt_pcreateerror("clnttcp_create");
    			exit(-1);
   		}
		printf("[clGetPlatformIDs interposed]clnttcp_create OK\n");

		xdrproc_t xdr_arg, xdr_ret;

		xdr_arg = (xdrproc_t)_xdr_get_platform_ids;
		xdr_ret = (xdrproc_t)_xdr_get_platform_ids;

		get_platform_ids_ arg_pkt, ret_pkt;
		memset((char *)&arg_pkt, 0, sizeof(get_platform_ids_));
		memset((char *)&ret_pkt, 0, sizeof(get_platform_ids_));
		
		//Client receives this from the server - so this is a hack to keep the rpc libray from crashing
		//send one char , that is, pass an initialized pointer, which gets ignored
		arg_pkt.platforms.buff_ptr = "\0";
		arg_pkt.platforms.buff_len = sizeof(char);

		ret_pkt.platforms.buff_ptr = NULL;

		enum clnt_stat cs;
		struct timeval  total_timeout;
		total_timeout.tv_sec = 10;
		total_timeout.tv_usec = 0;
		cs=clnt_call(clnt, GET_PLATFORM_IDS, (xdrproc_t) xdr_arg, (char *) &arg_pkt, (xdrproc_t) xdr_ret,(char *) &ret_pkt, total_timeout);
		if ( cs != RPC_SUCCESS){
    			printf("clnt_call failed \n");
		}

		err |= ret_pkt.err;

		int num_platforms_found_curr_node = ret_pkt.num_platforms_found;
		printf("[clGetPlatformIDs interposed] num_platforms_found %d\n", num_platforms_found_curr_node);

		if(num_platforms_found_curr_node && (ret_pkt.err==CL_SUCCESS)){
			char *platforms_found_curr_node = ret_pkt.platforms.buff_ptr;
			num_platforms_found += num_platforms_found_curr_node;
			num_platforms_per_node.insert(std::pair<int, int>(i, num_platforms_found_curr_node));
			platforms_per_node.insert(std::pair<int, char*>(i, platforms_found_curr_node));

			for(int j=0; j<num_platforms_found_curr_node; j++){
				printf("[clGetPlatformIDs interposed] platforms[%d]=%p\n", j, *((cl_platform_id*)platforms_found_curr_node+j));
			}
		}

	}

	if(num_platforms){
		*num_platforms = num_platforms_found;
	}

	if(!platforms || !num_platforms_found){
		return err;
	}

	int num_entries_found = 0;
	for(int i=0; i<num_nodes; i++){

		std::map<int, int>::iterator it1 = num_platforms_per_node.find(i);
		if(it1 == num_platforms_per_node.end()){
			continue;
		}

		int num_platforms_curr_node = it1->second;
		
		int num_entries_needed = 0;
		if(num_entries_found + num_platforms_curr_node > num_entries){
			num_entries_needed = num_entries - num_entries_found;
		}else{
                        num_entries_needed = num_platforms_curr_node;
		}

		std::map<int, char*>::iterator it2 = platforms_per_node.find(i);
		assert(it2 != platforms_per_node.end());
		cl_platform_id *platforms_curr_node = (cl_platform_id *)(it2->second);

		for(int j=0; j<num_entries_needed; j++){
			cl_platform_id_ *platform_distr = (cl_platform_id_ *)malloc(sizeof(cl_platform_id_));
			platform_distr->node = nodes[i];
			platform_distr->clhandle = platforms_curr_node[j];
			printf("[clGetPlatformIDs interposed] platforms[%d] = %p\n", num_entries_found + j, platform_distr->clhandle);
		 	platforms[num_entries_found + j] = (cl_platform_id)platform_distr;	
		}
		num_entries_found += num_entries_needed;

	}	

	return CL_SUCCESS;

}

cl_int clGetDeviceIDs (cl_platform_id platform,cl_device_type device_type, cl_uint num_entries,cl_device_id *devices, cl_uint *num_devices){


//Don't send the RPC if the args are invalid
	if(!num_entries && devices){
		return CL_INVALID_VALUE;
	}

	if(!num_devices && !devices){
		return CL_INVALID_VALUE;
	}

	int num_devices_found = 0;

	cl_int err = CL_SUCCESS;	

	cl_platform_id_ *platform_distr = (cl_platform_id_ *)platform;

	char *node = platform_distr->node;
	cl_platform_id clhandle = platform_distr->clhandle;
	
	register CLIENT *clnt;
	int sock = RPC_ANYSOCK; /* can be also valid socket descriptor */
	struct hostent *hp;
	struct sockaddr_in server_addr;

	/* get the internet address of RPC server */
	if ((hp = gethostbyname(node)) == NULL){
		printf("Can't get address for %s\n",node);
		exit (-1);
	}

	bcopy(hp->h_addr, (caddr_t)&server_addr.sin_addr.s_addr, hp->h_length);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = 0;

	/* create TCP handle */
	if ((clnt = clnttcp_create(&server_addr, GET_DEVICE_IDS_PROG, GET_DEVICE_IDS_VERS,
					&sock, 0, 0)) == NULL){
		clnt_pcreateerror("clnttcp_create");
		exit(-1);
	}

	printf("[clGetDeviceIDs interposed]clnttcp_create OK\n");

	xdrproc_t xdr_arg, xdr_ret;

	xdr_arg = (xdrproc_t)_xdr_get_device_ids;
	xdr_ret = (xdrproc_t)_xdr_get_device_ids;

	get_device_ids_ arg_pkt, ret_pkt;
	memset((char *)&arg_pkt, 0, sizeof(get_device_ids_));
	memset((char *)&ret_pkt, 0, sizeof(get_device_ids_));
		
	//Client receives this from the server - so this is a hack to keep the rpc libray from crashing
	//send one char , that is, pass an initialized pointer, which gets ignored
	arg_pkt.devices.buff_ptr = "\0";
	arg_pkt.devices.buff_len = sizeof(char);

	ret_pkt.devices.buff_ptr = NULL;

	arg_pkt.platform = (unsigned long)clhandle;
	arg_pkt.device_type = (int)device_type;

        printf("[clGetDeviceIDs interposed] platform %p\n", (cl_platform_id)(arg_pkt.platform));
        printf("[clGetDeviceIDs interposed] device_type %d\n", (cl_device_type)(arg_pkt.device_type));

	enum clnt_stat cs;
	struct timeval  total_timeout;
	total_timeout.tv_sec = 10;
	total_timeout.tv_usec = 0;

	cs=clnt_call(clnt, GET_DEVICE_IDS, (xdrproc_t) xdr_arg, (char *) &arg_pkt, (xdrproc_t) xdr_ret,(char *) &ret_pkt, total_timeout);
	if ( cs != RPC_SUCCESS){
		printf("clnt_call failed \n");
	}

	err |= ret_pkt.err;

	printf("[clGetPlatformIDs interposed] num_devices_found %d\n", ret_pkt.num_devices_found);

	cl_device_id *device_list = (cl_device_id *)malloc(ret_pkt.num_devices_found * sizeof(cl_device_id));
	char *device_list_returned = ret_pkt.devices.buff_ptr;

	if(ret_pkt.num_devices_found && (ret_pkt.err==CL_SUCCESS)){

		num_devices_found += ret_pkt.num_devices_found;

		for(int i=0; i<num_devices_found; i++){
			device_list[i] = *((cl_device_id*)device_list_returned+i);
			printf("[clGetDeviceIDs interposed] devices[%d]=%p\n", i, device_list[i]);
		}
	}


	if(num_devices){
		*num_devices = num_devices_found;
	}

	if(!devices || !num_devices_found){
		return err;
	}

	for(int i=0; i<num_entries; i++){

		/*If the application asks for more devices than there is on the given platform, then just return the ones that are available and set the rest of the devices array to zero*/
		if(i >= num_devices_found){
			devices[i] = 0;
			continue;
		}

		cl_device_id_ *device_distr = (cl_device_id_ *)malloc(sizeof(cl_device_id_));
		device_distr->node = node;
		device_distr->clhandle = device_list[i];
		printf("[clGetDeviceIDs interposed] devices[%d] = %p\n", i, device_distr->clhandle);
		devices[i] = (cl_device_id)device_distr;	

	}	

	//strictly speaking, this should not return a CL_SUCCESS if devices asked for > devices available
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

cl_int clEnqueueNDRangeKernel (cl_command_queue command_queue, cl_kernel kernel, cl_uint work_dim, const size_t *global_work_offset, const size_t *global_work_size, const size_t *local_work_size, cl_uint num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event){

	return CL_SUCCESS;

}
