#define GET_PLATFORM_IDS_PROG 0xE00000E
#define GET_PLATFORM_IDS_VERS 1
#define GET_PLATFORM_IDS 0x1

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

	if(xdrs->x_op == XDR_ENCODE){
		printf("[_xdr_get_platform_ids] xdr encode\n");
		printf("[_xdr_get_platform_ids] num_platforms_found %d\n", objp->num_platforms_found);
		for(int i=0; i<objp->num_platforms_found; i++){
			printf("[_xdr_get_platform_ids] platforms[%d]=%p\n",i, *((cl_platform_id*)(objp->platforms.buff_ptr)+i));
		}
	}

	if(!xdr_u_int(xdrs, &(objp->num_platforms_found))){
		return FALSE;
	}

	if (!xdr_bytes (xdrs, (char **)&objp->platforms.buff_ptr, (u_int *) &objp->platforms.buff_len, ~0)){
                 return FALSE;
	}

	if(xdrs->x_op == XDR_DECODE){
		printf("[_xdr_get_platform_ids] xdr decode\n");
		printf("[_xdr_get_platform_ids] num_platforms_found %d\n", objp->num_platforms_found);
		for(int i=0; i<objp->num_platforms_found; i++){
			printf("[_xdr_get_platform_ids] platforms[%d]=%p\n",i, *((cl_platform_id*)(objp->platforms.buff_ptr)+i));
		}
	}

	return TRUE;
}
	
