#include <stdio.h>
#include "CL/opencl.h"
#include <rpc/rpc.h>
#include <sys/socket.h>
#include "../client_server_common_includes.h"

void clGetPlatformIDs_server(get_platform_ids_ *argp, get_platform_ids_ *retp){

	cl_int err = CL_SUCCESS;

        cl_uint num_platforms = 0;

        err = clGetPlatformIDs(0, NULL, &num_platforms);

        if(err != CL_SUCCESS){
                printf("clGetPlatformIDs failed with err %d\n", err);
                exit(-1);
        }

        printf("[clGetPlatformIDs_server] Num OpenCL platforms found %d\n", num_platforms);
	retp->num_platforms_found = num_platforms;

        if(num_platforms > 0){

		cl_platform_id *platforms = (cl_platform_id *)malloc(sizeof(cl_platform_id)* num_platforms);

		clGetPlatformIDs(num_platforms, platforms, NULL);

                if(err != CL_SUCCESS){
                        printf("clGetPlatformIDs failed with err %d\n", err);
                        exit(-1);
                }

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

        cl_uint num_devices = 0;

	printf("[clGetDeviceIDs_server] platform %p\n", (cl_platform_id)(argp->platform));
	printf("[clGetDeviceIDs_server] device_type %d\n", (cl_device_type)(argp->device_type));


        err = clGetDeviceIDs((cl_platform_id)(argp->platform), (cl_device_type)(argp->device_type), 0, NULL, &num_devices);

        if(err != CL_SUCCESS){
                printf("clGetDeviceIDs failed with err %d\n", err);
                exit(-1);
        }

        printf("[clGetDeviceIDs_server] Num OpenCL devices found %d\n", num_devices);
	retp->num_devices_found = num_devices;

        if(num_devices > 0){

		cl_device_id *devices = (cl_device_id *)malloc(sizeof(cl_device_id)* num_devices);

		clGetDeviceIDs((cl_platform_id)(argp->platform), (cl_device_type)(argp->device_type), num_devices, devices, NULL);

                if(err != CL_SUCCESS){
                        printf("clGetDeviceIDs failed with err %d\n", err);
                        exit(-1);
                }

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

        if (!svc_register(transp, GET_PLATFORM_IDS_PROG, GET_PLATFORM_IDS_VERS,clGetPlatformIDs_server_wrapper, IPPROTO_TCP)) {
                printf ("%s", "unable to register (GET_PLATFORM_IDS_PROG, GET_PLATFORM_IDS_VERS, tcp).");
                exit(-1);
        }

	printf("[main] svctcp_register GET_PLATFORM_IDS_PROG OK\n");

	svc_unregister(GET_DEVICE_IDS_PROG, GET_DEVICE_IDS_VERS);

        if (!svc_register(transp, GET_DEVICE_IDS_PROG, GET_DEVICE_IDS_VERS,clGetDeviceIDs_server_wrapper, IPPROTO_TCP)) {
                printf ("%s", "unable to register (GET_DEVICE_IDS_PROG, GET_DEVICE_IDS_VERS, tcp).");
                exit(-1);
        }

	printf("[main] svctcp_register GET_DEVICE_IDS_PROG OK\n");

	svc_run();

	printf("[main] this message should be unreachable");

	exit(-1);

}
