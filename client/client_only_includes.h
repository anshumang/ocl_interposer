#include "CL/opencl.h"

typedef struct cl_platform_id_distr {

	char *node;
	cl_platform_id clhandle;

} cl_platform_id_;

typedef struct cl_device_id_distr {

	char *node;
	cl_device_id clhandle;

} cl_device_id_;

typedef struct cl_context_distr_elem {
	char *node;
	cl_context cl_handle;
} cl_context_elem_;

typedef struct cl_context_distr {

	cl_context_elem_ *context_tuples;
	unsigned int num_context_tuples;

} cl_context_;
