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
	cl_context clhandle;
} cl_context_elem_;

typedef struct cl_context_distr {

	cl_context_elem_ *context_tuples;
	unsigned int num_context_tuples;

} cl_context_;

typedef struct cl_command_queue_distr {

	char *node;
	cl_command_queue clhandle;

} cl_command_queue_;

typedef struct cl_mem_distr_elem {
	char *node;
	cl_mem clhandle;
} cl_mem_elem_;

typedef struct cl_mem_distr {

	cl_mem_elem_ *mem_tuples;
	unsigned int num_mem_tuples;

} cl_mem_;

typedef struct cl_program_distr_elem {
	char *node;
	cl_program clhandle;
} cl_program_elem_;

typedef struct cl_program_distr {

	cl_program_elem_ *program_tuples;
	unsigned int num_program_tuples;

} cl_program_;
