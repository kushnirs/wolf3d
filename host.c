/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   host.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 10:14:49 by sergee            #+#    #+#             */
/*   Updated: 2018/03/20 13:55:59 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

#define MAX_SOURCE_SIZE 12000
#define CL_BUILD_PROGRAM_FAILURE -11

void		kernel_param(t_sdl *data)
{
	cl_int ret;

	(ret = clSetKernelArg(data->host.kernel, 0, sizeof(cl_mem),
	(void *)&data->host.memobj)) ? exit(ft_printf("Can't set parameter\n")) : 0;
	(ret = clSetKernelArg(data->host.kernel, 1, sizeof(cl_mem),
	(void *)&data->host.map)) ? exit(ft_printf("Can't set parameter\n")) : 0;
	(ret = clSetKernelArg(data->host.kernel, 2, sizeof(cl_mem),
	(void *)&data->host.wall)) ? exit(ft_printf("Can't set parameter\n")) : 0;
	(ret = clSetKernelArg(data->host.kernel, 3, sizeof(t_point),
	(void *)&data->player.pos)) ? exit(ft_printf("Can't set parameter\n")) : 0;
	(ret = clSetKernelArg(data->host.kernel, 4, sizeof(t_point),
	(void *)&data->player.dir)) ? exit(ft_printf("Can't set parameter\n")) : 0;
	(ret = clSetKernelArg(data->host.kernel, 5, sizeof(t_point),
	(void *)&data->plane)) ? exit(ft_printf("Can't set parameter\n")) : 0;
	(ret = clSetKernelArg(data->host.kernel, 6, sizeof(t_point),
	(void *)&((t_point){data->map.col, data->map.row}))) ?
		exit(ft_printf("Can't set parameter\n")) : 0;
	ret = clEnqueueNDRangeKernel(data->host.com_queue, data->host.kernel,
		1, NULL, (size_t[3]){data->surface->w, 0, 0}, NULL, 0, NULL, NULL);
	ret ? exit(ft_printf("clEnqueueNDRangeKernel Failed\n")) : 0;
	ret = clEnqueueReadBuffer(data->host.com_queue, data->host.memobj, CL_TRUE,
		0, data->surface->w * data->surface->h * sizeof(int),
		(t_ui*)data->surface->pixels, 0, NULL, NULL);
	ret ? exit(ft_printf("clEnqueueReadBuffer Failed\n")) : 0;
}

static void	host_program(char *str, int size, t_sdl *data)
{
	cl_int	ret;

	data->host.com_queue = clCreateCommandQueue(data->host.context,
		data->host.dev_id, 0, &ret);
	ret ? exit(ft_printf("clCreateCommandQueue Failed\n")) : 0;
	data->host.memobj = clCreateBuffer(data->host.context, CL_MEM_READ_WRITE,
		data->surface->w * data->surface->h * sizeof(int), NULL, &ret);
	ret ? exit(ft_printf("clCreateBuffer Failed\n")) : 0;
	data->host.map = clCreateBuffer(data->host.context, CL_MEM_USE_HOST_PTR,
		data->map.row * data->map.col * sizeof(int), data->map.map, &ret);
	data->host.wall = clCreateBuffer(data->host.context, CL_MEM_USE_HOST_PTR,
		7 * sizeof(t_wall), data->wall, &ret);
	ret ? exit(ft_printf("clCreateMap Failed\n")) : 0;
	data->host.program = clCreateProgramWithSource(data->host.context, 1,
		(const char **)&str, (const size_t *)&size, &ret);
	ret ? exit(ft_printf("clCreateProgramWithSource Failed %d\n", ret)) : 0;
	(ret = clBuildProgram(data->host.program, 1, &data->host.dev_id,
	"-I ./kernel", NULL, NULL)) ? ft_printf("%dBuildProgram Failed\n", ret) : 0;
	data->host.kernel = clCreateKernel(data->host.program, "raycast", &ret);
	ret ? exit(ft_printf("clCreateKernel Failed\n")) : 0;
}

int			host_fract(t_sdl *data)
{
	int		fp;
	int		size;
	char	*str;
	cl_int	ret;

	(fp = open("./kernel/wolf.cl", O_RDONLY)) <= 0 ?
		exit(ft_printf("Failed to load kernel.\n")) : 0;
	!(str = (char*)malloc(MAX_SOURCE_SIZE)) ?
		exit(ft_printf("Can't allocate memory\n")) : 0;
	(size = read(fp, str, MAX_SOURCE_SIZE)) <= 0 ?
		exit(ft_printf("Can't read file\n")) : 0;
	close(fp);
	(ret = clGetPlatformIDs(1, &data->host.p_id, &data->host.ret_num_p)) ?
		exit(ft_printf("clGetPlatformIDs Failed\n")) : 0;
	ret = clGetDeviceIDs(data->host.p_id, DEVICE_TYPE, 1,
		&data->host.dev_id, &data->host.ret_num_dev);
	ret ? exit(ft_printf("clGetPlatformIDs Failed\n")) : 0;
	data->host.context = clCreateContext(NULL, 1,
		&data->host.dev_id, NULL, NULL, &ret);
	ret ? exit(ft_printf("clCreateContext Failed\n")) : 0;
	host_program(str, size, data);
	ft_memdel((void**)&str);
	return (0);
}

/*
**static char* clUtilGetErrorCode(cl_int err)
**{
**	switch(err)
**	{
**	case CL_SUCCESS: return "No Error.";
**	case CL_INVALID_MEM_OBJECT: return "Invalid memory object.";
**	case CL_INVALID_ARG_INDEX: return "Invalid argument index for this kernel.";
**	case CL_INVALID_ARG_VALUE: return "Invalid argument value.";
**	case CL_INVALID_SAMPLER: return "Invalid sampler.";
**	case CL_INVALID_ARG_SIZE: return "Invalid argument size.";
**	case CL_INVALID_BUFFER_SIZE: return "Invalid buffer size.";
**	case CL_INVALID_HOST_PTR: return "Invalid host pointer.";
**	case CL_INVALID_DEVICE: return "Invalid device.";
**	case CL_INVALID_VALUE: return "Invalid value.";
**	case CL_INVALID_CONTEXT: return "Invalid Context.";
**	case CL_INVALID_KERNEL: return "Invalid kernel.";
**	case CL_INVALID_PROGRAM: return "Invalid program object.";
**	case CL_INVALID_BINARY: return "Invalid program binary.";
**	case CL_INVALID_OPERATION: return "Invalid operation.";
**	case CL_INVALID_BUILD_OPTIONS: return "Invalid build options.";
**	case CL_INVALID_PROGRAM_EXECUTABLE: return "Invalid executable.";
**	case CL_INVALID_COMMAND_QUEUE: return "Invalid command queue.";
**	case CL_INVALID_KERNEL_ARGS: return "Invalid kernel arguments.";
**	case CL_INVALID_WORK_DIMENSION: return "Invalid work dimension.";
**	case CL_INVALID_WORK_GROUP_SIZE: return "Invalid work group size.";
**	case CL_INVALID_WORK_ITEM_SIZE: return "Invalid work item size.";
**	case CL_INVALID_GLOBAL_OFFSET:
**  return "Invalid global offset (should be NULL).";
**	case CL_OUT_OF_RESOURCES: return "Insufficient resources.";
**	case CL_MEM_OBJECT_ALLOCATION_FAILURE:
**	return "Could not allocate mem object.";
**	case CL_INVALID_EVENT_WAIT_LIST: return "Invalid event wait list.";
**	case CL_OUT_OF_HOST_MEMORY: return "Out of memory on host.";
**	case CL_INVALID_KERNEL_NAME: return "Invalid kernel name.";
**	case CL_INVALID_KERNEL_DEFINITION: return "Invalid kernel definition.";
**	case CL_BUILD_PROGRAM_FAILURE: return "Failed to build program.";
**	}
**	return (NULL);
**}
*/
/*
** if (ret == CL_BUILD_PROGRAM_FAILURE)
** {
**    	size_t log_size;
**    	clGetProgramBuildInfo(data->host.program, data->host.dev_id,
**		CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
**    	char *log = (char *) malloc(log_size);
**    	clGetProgramBuildInfo(data->host.program, data->host.dev_id,
**		CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
**    	printf("%s\n", log);
** }
*/
