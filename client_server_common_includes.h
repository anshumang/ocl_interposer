#define GET_PLATFORM_IDS_PROG 0xFF000000
#define GET_PLATFORM_IDS_VERS 1
#define GET_PLATFORM_IDS 0x1

#define GET_DEVICE_IDS_PROG 0x0FF00000
#define GET_DEVICE_IDS_VERS 1
#define GET_DEVICE_IDS 0x2

#define CREATE_CONTEXT_PROG 0x00FF0000
#define CREATE_CONTEXT_VERS 1
#define CREATE_CONTEXT 0x3

#define CREATE_COMMAND_QUEUE_PROG 0x000FF000
#define CREATE_COMMAND_QUEUE_VERS 1
#define CREATE_COMMAND_QUEUE 0x4

#define CREATE_BUFFER_PROG 0x0000FF00
#define CREATE_BUFFER_VERS 1
#define CREATE_BUFFER 0x5

#define CREATE_PROGRAM_WITH_SOURCE_PROG 0x000000FF0
#define CREATE_PROGRAM_WITH_SOURCE_VERS 1
#define CREATE_PROGRAM_WITH_SOURCE 0x6

#define BUILD_PROGRAM_PROG 0x000000FF
#define BUILD_PROGRAM_VERS 1
#define BUILD_PROGRAM 0x7

#define CREATE_KERNEL_PROG 0xAA000000
#define CREATE_KERNEL_VERS 1
#define CREATE_KERNEL 0x8

#define SET_KERNEL_ARG_PROG 0x0AA00000
#define SET_KERNEL_ARG_VERS 1
#define SET_KERNEL_ARG 0x9

#define ENQUEUE_WRITE_BUFFER_PROG 0x00AA0000
#define ENQUEUE_WRITE_BUFFER_VERS 1
#define ENQUEUE_WRITE_BUFFER 0xA

#define ENQUEUE_READ_BUFFER_PROG 0x000AA000
#define ENQUEUE_READ_BUFFER_VERS 1
#define ENQUEUE_READ_BUFFER 0xB

#define ENQUEUE_NDRANGE_KERNEL_PROG 0x0000AA00
#define ENQUEUE_NDRANGE_KERNEL_VERS 1
#define ENQUEUE_NDRANGE_KERNEL 0xC

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

#ifdef XDR_DEBUG
	if(xdrs->x_op == XDR_ENCODE){
		printf("[_xdr_create_command_queue] xdr encode\n");
		printf("[_xdr_create_command_queue] context %p\n", objp->context);
	}
#endif

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

#ifdef XDR_DEBUG
	if(xdrs->x_op == XDR_DECODE){
		printf("[_xdr_create_command_queue] xdr decode\n");
		printf("[_xdr_create_command_queue] context %p\n", objp->context);
	}
#endif

	return TRUE;
}

typedef struct create_buffer_xdr {
	unsigned long context; //Client to Server
	int flags; //C2S
	buff_xdr_ data; //C2S
	unsigned long size; //C2S
	int err; //Server to Client
	unsigned long mem; //S2C
} create_buffer_;

bool_t _xdr_create_buffer(XDR *xdrs, create_buffer_ *objp){

#ifdef XDR_DEBUG
	if(xdrs->x_op == XDR_ENCODE){
		printf("[_xdr_create_buffer] xdr encode\n");
		printf("[_xdr_create_buffer] context %p\n", objp->context);
	}
#endif

	if(!xdr_u_long(xdrs, &(objp->context))){
		return FALSE;
	}

	if(!xdr_int(xdrs, &(objp->flags))){
		return FALSE;
	}

        if(!xdr_u_long(xdrs, &(objp->size))){
                return FALSE;
        }

	if (!xdr_bytes (xdrs, (char **)&objp->data.buff_ptr, (u_int *) &objp->data.buff_len, ~0)){
		return FALSE;
	}

	if(!xdr_u_long(xdrs, &(objp->mem))){
		return FALSE;
	}

	if(!xdr_int(xdrs, &(objp->err))){
		return FALSE;
	}

#ifdef XDR_DEBUG
	if(xdrs->x_op == XDR_DECODE){
		printf("[_xdr_create_buffer] xdr decode\n");
		printf("[_xdr_create_buffer] context %p\n", objp->context);
	}
#endif

	return TRUE;
}

typedef struct create_program_with_source_xdr {
	unsigned long context; //Client to Server
	buff_xdr_ program_str; //C2S
	int err; //Server to Client
	unsigned long program; //S2C
} create_program_with_source_;

bool_t _xdr_create_program_with_source(XDR *xdrs, create_program_with_source_ *objp){

#ifdef XDR_DEBUG
	if(xdrs->x_op == XDR_ENCODE){
		printf("[_xdr_create_program_with_source] xdr encode\n");
		printf("[_xdr_create_program_with_source] context %p\n", objp->context);
	}
#endif

	if(!xdr_u_long(xdrs, &(objp->context))){
		return FALSE;
	}

	if (!xdr_bytes (xdrs, (char **)&objp->program_str.buff_ptr, (u_int *) &objp->program_str.buff_len, ~0)){
		return FALSE;
	}

	if(!xdr_u_long(xdrs, &(objp->program))){
		return FALSE;
	}

	if(!xdr_int(xdrs, &(objp->err))){
		return FALSE;
	}

#ifdef XDR_DEBUG
	if(xdrs->x_op == XDR_DECODE){
		printf("[_xdr_create_program_with_source] xdr decode\n");
		printf("[_xdr_create_program_with_source] context %p\n", objp->context);
	}
#endif

	return TRUE;
}


typedef struct build_program_xdr {
	unsigned long program; //Client to Server
	bool_t all_devices; //C2S
	unsigned int num_devices; //C2S
	buff_xdr_ devices; //C2S
	buff_xdr_ options; //C2S
	int err; //Server to Client
} build_program_;

bool_t _xdr_build_program(XDR *xdrs, build_program_ *objp){

#ifdef XDR_DEBUG
	if(xdrs->x_op == XDR_ENCODE){
		printf("[_xdr_build_program] xdr encode\n");
		printf("[_xdr_build_program] program %p\n", objp->program);
	}
#endif

	if(!xdr_u_long(xdrs, &(objp->program))){
		return FALSE;
	}

	if(!xdr_bool(xdrs, &(objp->all_devices))){
		return FALSE;
	}

	if(!xdr_u_int(xdrs, &(objp->num_devices))){
		return FALSE;
	}

	if (!xdr_bytes (xdrs, (char **)&objp->devices.buff_ptr, (u_int *) &objp->devices.buff_len, ~0)){
		return FALSE;
	}

	if (!xdr_bytes (xdrs, (char **)&objp->options.buff_ptr, (u_int *) &objp->options.buff_len, ~0)){
		return FALSE;
	}

	if(!xdr_int(xdrs, &(objp->err))){
		return FALSE;
	}

#ifdef XDR_DEBUG
	if(xdrs->x_op == XDR_DECODE){
		printf("[_xdr_build_program] xdr decode\n");
		printf("[_xdr_build_program] program %p\n", objp->program);
	}
#endif

	return TRUE;
}

typedef struct create_kernel {
	unsigned long program; //Client to Server
	buff_xdr_ kernel_name; //C2S
	int err; //Server to Client
	unsigned long kernel; //S2C
} create_kernel_;

bool_t _xdr_create_kernel(XDR *xdrs, create_kernel_ *objp){

#ifdef XDR_DEBUG
	if(xdrs->x_op == XDR_ENCODE){
		printf("[_xdr_create_kernel] xdr encode\n");
		printf("[_xdr_create_kernel] program %p\n", objp->program);
	}
#endif

	if(!xdr_u_long(xdrs, &(objp->program))){
		return FALSE;
	}

	if (!xdr_bytes (xdrs, (char **)&objp->kernel_name.buff_ptr, (u_int *) &objp->kernel_name.buff_len, ~0)){
		return FALSE;
	}

	if(!xdr_u_long(xdrs, &(objp->kernel))){
		return FALSE;
	}

	if(!xdr_int(xdrs, &(objp->err))){
		return FALSE;
	}

#ifdef XDR_DEBUG
	if(xdrs->x_op == XDR_DECODE){
		printf("[_xdr_create_kernel] xdr decode\n");
		printf("[_xdr_create_kernel] program %p\n", objp->program);
	}
#endif

	return TRUE;
}

typedef struct set_kernel_arg {
	unsigned long kernel; //Client to Server
	unsigned long mem; //C2S
	unsigned long image; //C2S
	unsigned long sampler; //C2S
	bool_t is_clobj; //C2S
	bool_t is_mem; //C2S
	bool_t is_image; //C2S
	bool_t is_sampler; //C2S
	bool_t is_null_arg; //C2S
	int arg_index; //C2S
	int arg_size; //C2S
	buff_xdr_ plain_old_data; //C2S
	int err; //Server to Client
} set_kernel_arg_;

bool_t _xdr_set_kernel_arg(XDR *xdrs, set_kernel_arg_ *objp){

#ifndef XDR_DEBUG
	if(xdrs->x_op == XDR_ENCODE){
		printf("[_xdr_set_kernel_arg] xdr encode\n");
	}
	if(xdrs->x_op == XDR_DECODE){
		printf("[_xdr_set_kernel_arg] xdr decode\n");
	}
#endif

	if(!xdr_u_long(xdrs, &(objp->kernel))){
		return FALSE;
	}

	if(!xdr_u_long(xdrs, &(objp->mem))){
		return FALSE;
	}

	if(!xdr_u_long(xdrs, &(objp->image))){
		return FALSE;
	}

	if(!xdr_u_long(xdrs, &(objp->sampler))){
		return FALSE;
	}

	printf("[_xdr_set_kernel_arg] buff_ptr %p buff_len %d\n", objp->plain_old_data.buff_ptr, objp->plain_old_data.buff_len);

	if (!xdr_bytes (xdrs, (char **)&objp->plain_old_data.buff_ptr, (u_int *) &objp->plain_old_data.buff_len, ~0)){
		return FALSE;
	}

	printf("[_xdr_set_kernel_arg] buff_ptr %p buff_len %d\n", objp->plain_old_data.buff_ptr, objp->plain_old_data.buff_len);

	if(!xdr_bool(xdrs, &(objp->is_clobj))){
		return FALSE;
	}

	if(!xdr_bool(xdrs, &(objp->is_mem))){
		return FALSE;
	}

	if(!xdr_bool(xdrs, &(objp->is_image))){
		return FALSE;
	}

	if(!xdr_bool(xdrs, &(objp->is_sampler))){
		return FALSE;
	}

	if(!xdr_bool(xdrs, &(objp->is_null_arg))){
		return FALSE;
	}

	if(!xdr_int(xdrs, &(objp->arg_index))){
		return FALSE;
	}

	if(!xdr_int(xdrs, &(objp->arg_size))){
		return FALSE;
	}

	if(!xdr_int(xdrs, &(objp->err))){
		return FALSE;
	}


	return TRUE;
}

typedef struct enqueue_write_buffer_xdr {
	unsigned long mem; //Client to Server
	unsigned long command_queue; //C2S
	int blocking; //C2S
	unsigned long size; //C2S
	unsigned long offset; //C2S
	buff_xdr_ data; //C2S
	int err; //Server to Client
} enqueue_write_buffer_;

bool_t _xdr_enqueue_write_buffer(XDR *xdrs, enqueue_write_buffer_ *objp){

	if(!xdr_u_long(xdrs, &(objp->mem))){
		return FALSE;
	}

	if(!xdr_u_long(xdrs, &(objp->command_queue))){
		return FALSE;
	}

	if(!xdr_int(xdrs, &(objp->blocking))){
		return FALSE;
	}

	if(!xdr_u_long(xdrs, &(objp->size))){
		return FALSE;
	}

	if(!xdr_u_long(xdrs, &(objp->offset))){
		return FALSE;
	}

	if (!xdr_bytes (xdrs, (char **)&objp->data.buff_ptr, (u_int *) &objp->data.buff_len, ~0)){
		return FALSE;
	}

	if(!xdr_int(xdrs, &(objp->err))){
		return FALSE;
	}

	return TRUE;
}

typedef struct enqueue_read_buffer_xdr {
	unsigned long mem; //Client to Server
	unsigned long command_queue; //C2S
	int blocking; //C2S
	unsigned long size; //C2S
	unsigned long offset; //C2S
	buff_xdr_ data; //Server to Client
	int err; //S2C
} enqueue_read_buffer_;

bool_t _xdr_enqueue_read_buffer(XDR *xdrs, enqueue_read_buffer_ *objp){

	if(!xdr_u_long(xdrs, &(objp->mem))){
		return FALSE;
	}

	if(!xdr_u_long(xdrs, &(objp->command_queue))){
		return FALSE;
	}

	if(!xdr_int(xdrs, &(objp->blocking))){
		return FALSE;
	}

	if(!xdr_u_long(xdrs, &(objp->size))){
		return FALSE;
	}

	if(!xdr_u_long(xdrs, &(objp->offset))){
		return FALSE;
	}

	if (!xdr_bytes (xdrs, (char **)&objp->data.buff_ptr, (u_int *) &objp->data.buff_len, ~0)){
		return FALSE;
	}

	if(!xdr_int(xdrs, &(objp->err))){
		return FALSE;
	}

	return TRUE;
}

typedef struct enqueue_ndrange_kernel_xdr {
	unsigned long kernel; //Client to Server
	unsigned long command_queue; //C2S
	int work_dim; //C2S
	buff_xdr_ global_offset; //C2S
	buff_xdr_ global_size; //C2S
	buff_xdr_ local_size; //C2S
	int err; //Server to Client
} enqueue_ndrange_kernel_;

bool_t _xdr_enqueue_ndrange_kernel(XDR *xdrs, enqueue_ndrange_kernel_ *objp){

	if(!xdr_u_long(xdrs, &(objp->kernel))){
		return FALSE;
	}

	if(!xdr_u_long(xdrs, &(objp->command_queue))){
		return FALSE;
	}

	if(!xdr_int(xdrs, &(objp->work_dim))){
		return FALSE;
	}

	if (!xdr_bytes (xdrs, (char **)&objp->global_offset.buff_ptr, (u_int *) &objp->global_offset.buff_len, ~0)){
		return FALSE;
	}

	if (!xdr_bytes (xdrs, (char **)&objp->global_size.buff_ptr, (u_int *) &objp->global_size.buff_len, ~0)){
		return FALSE;
	}

	if (!xdr_bytes (xdrs, (char **)&objp->local_size.buff_ptr, (u_int *) &objp->local_size.buff_len, ~0)){
		return FALSE;
	}

	if(!xdr_int(xdrs, &(objp->err))){
		return FALSE;
	}

	return TRUE;
}
