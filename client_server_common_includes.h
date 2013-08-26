#define GET_PLATFORM_IDS_PROG 0x6000006
#define GET_PLATFORM_IDS_VERS 1
#define GET_PLATFORM_IDS 0x1

#define GET_DEVICE_IDS_PROG 0xB11111B
#define GET_DEVICE_IDS_VERS 1
#define GET_DEVICE_IDS 0x1

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
	
