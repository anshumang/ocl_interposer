#include "CL/opencl.h"

typedef struct cl_platform_id_distr {

	char *node;
	cl_platform_id clhandle;

} cl_platform_id_;

typedef struct cl_device_id_distr {

	char *node;
	cl_device_id clhandle;

} cl_device_id_;
