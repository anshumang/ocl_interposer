#define GET_PLATFORM_IDS_PROG 0x30000000
#define GET_PLATFORM_IDS_VERS 1
#define GET_PLATFORM_IDS 0x1

#define GET_DEVICE_IDS_PROG 0x03000000
#define GET_DEVICE_IDS_VERS 1
#define GET_DEVICE_IDS 0x2

#define CREATE_CONTEXT_PROG 0x00300000
#define CREATE_CONTEXT_VERS 1
#define CREATE_CONTEXT 0x3

#define CREATE_COMMAND_QUEUE_PROG 0x00030000
#define CREATE_COMMAND_QUEUE_VERS 1
#define CREATE_COMMAND_QUEUE 0x4

typedef struct buff_xdr {
	unsigned int buff_len;
	char *buff_ptr;
} buff_xdr_;

typedef struct get_platform_ids_xdr {
	int err;
	unsigned int num_platforms_found;
	buff_xdr_ platforms;
} get_platform_ids_;


bool_t _xdr_get_platform_ids(XDR *xdrs, get_platform_ids_ *objp){
#ifdef XDR_DEBUG
	if(xdrs->x_op == XDR_ENCODE){
		printf("[_xdr_get_platform_ids] xdr encode\n");
		printf("[_xdr_get_platform_ids] num_platforms_found %d\n", objp->num_platforms_found);
		for(int i=0; i<objp->num_platforms_found; i++){
			printf("[_xdr_get_platform_ids] platforms[%d]=%p\n",i, *((cl_platform_id*)(objp->platforms.buff_ptr)+i));
		}
	}
#endif

	if(!xdr_u_int(xdrs, &(objp->num_platforms_found))){
		return FALSE;
	}

	if (!xdr_bytes (xdrs, (char **)&objp->platforms.buff_ptr, (u_int *) &objp->platforms.buff_len, ~0)){
                 return FALSE;
	}

	if(!xdr_int(xdrs, &(objp->err))){
		return FALSE;
	}

#ifdef XDR_DEBUG
	if(xdrs->x_op == XDR_DECODE){
		printf("[_xdr_get_platform_ids] xdr decode\n");
		printf("[_xdr_get_platform_ids] num_platforms_found %d\n", objp->num_platforms_found);
		for(int i=0; i<objp->num_platforms_found; i++){
			printf("[_xdr_get_platform_ids] platforms[%d]=%p\n",i, *((cl_platform_id*)(objp->platforms.buff_ptr)+i));
		}
	}
#endif
	return TRUE;
}
	
typedef struct get_device_ids_xdr {
	unsigned long platform;
	int device_type;
	int err;
	unsigned int num_devices_found;
	buff_xdr_ devices;
} get_device_ids_;

bool_t _xdr_get_device_ids(XDR *xdrs, get_device_ids_ *objp){
#ifdef XDR_DEBUG
	if(xdrs->x_op == XDR_ENCODE){
		printf("[_xdr_get_device_ids] xdr encode\n");
		printf("[_xdr_get_device_ids] num_devices_found %d\n", objp->num_devices_found);
		for(int i=0; i<objp->num_devices_found; i++){
			printf("[_xdr_get_device_ids] devices[%d]=%p\n",i, *((cl_device_id*)(objp->devices.buff_ptr)+i));
		}
	}
#endif
	if(!xdr_u_long(xdrs, &(objp->platform))){
		return FALSE;
	}

	if(!xdr_int(xdrs, &(objp->device_type))){
		return FALSE;
	}

	if(!xdr_u_int(xdrs, &(objp->num_devices_found))){
		return FALSE;
	}

	if (!xdr_bytes (xdrs, (char **)&objp->devices.buff_ptr, (u_int *) &objp->devices.buff_len, ~0)){
                 return FALSE;
	}

	if(!xdr_int(xdrs, &(objp->err))){
		return FALSE;
	}

#ifdef XDR_DEBUG
	if(xdrs->x_op == XDR_DECODE){
		printf("[_xdr_get_device_ids] xdr decode\n");
		printf("[_xdr_get_device_ids] num_devices_found %d\n", objp->num_devices_found);
		for(int i=0; i<objp->num_devices_found; i++){
			printf("[_xdr_get_device_ids] devices[%d]=%p\n",i, *((cl_device_id*)(objp->devices.buff_ptr)+i));
		}
	}
#endif
	return TRUE;
}

typedef struct create_context_xdr {
	unsigned long context;
	int err;
	unsigned int num_devices;
	buff_xdr_ devices;
} create_context_;
	
bool_t _xdr_create_context(XDR *xdrs, create_context_ *objp){
#ifdef XDR_DEBUG
	if(xdrs->x_op == XDR_ENCODE){
		printf("[_xdr_create_context] xdr encode\n");
		printf("[_xdr_create_context] num_devices_found %d\n", objp->num_devices);
		for(int i=0; i<objp->num_devices; i++){
			printf("[_xdr_create_context] devices[%d]=%p\n",i, *((cl_device_id*)(objp->devices.buff_ptr)+i));
		}
	}
#endif
	if(!xdr_u_long(xdrs, &(objp->context))){
		return FALSE;
	}

	if(!xdr_u_int(xdrs, &(objp->num_devices))){
		return FALSE;
	}

	if (!xdr_bytes (xdrs, (char **)&objp->devices.buff_ptr, (u_int *) &objp->devices.buff_len, ~0)){
                 return FALSE;
	}

	if(!xdr_int(xdrs, &(objp->err))){
		return FALSE;
	}

#ifdef XDR_DEBUG
	if(xdrs->x_op == XDR_DECODE){
		printf("[_xdr_create_context] xdr decode\n");
		printf("[_xdr_create_context] num_devices %d\n", objp->num_devices);
		for(int i=0; i<objp->num_devices; i++){
			printf("[_xdr_create_context] devices[%d]=%p\n",i, *((cl_device_id*)(objp->devices.buff_ptr)+i));
		}
	}
#endif
	return TRUE;
}

typedef struct create_command_queue_xdr {
	unsigned long context; //Client to Server
	unsigned long device; //C2S
	int err; //Server to Client
	unsigned long command_queue; //S2C
} create_command_queue_;

bool_t _xdr_create_command_queue(XDR *xdrs, create_command_queue_ *objp){

	if(!xdr_u_long(xdrs, &(objp->context))){
		return FALSE;
	}

	if(!xdr_u_long(xdrs, &(objp->device))){
		return FALSE;
	}

	if(!xdr_u_long(xdrs, &(objp->command_queue))){
		return FALSE;
	}

	if(!xdr_int(xdrs, &(objp->err))){
		return FALSE;
	}

	return TRUE;
}
