/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 20:26:36 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/07 12:36:21 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	ft_opencl_init(t_opencl *opencl, char *kernel_file)
{
	opencl->platform_id = ft_cl_platform();
	opencl->device_id = ft_cl_device(opencl->platform_id);
	opencl->context = ft_cl_context(&opencl->device_id);
	opencl->command_queue = ft_cl_command_queue(opencl->context, opencl->device_id);
	opencl->program = ft_cl_program(opencl->context, kernel_file);
}

void	ft_opencl_mem(t_opencl *opencl, t_scene *s)
{
	cl_int		ret;

	opencl->scene_mem_obj = clCreateBuffer(opencl->context, CL_MEM_READ_ONLY, sizeof(t_scene), NULL, &ret);
	opencl->pixels_mem_obj = clCreateBuffer(opencl->context, CL_MEM_WRITE_ONLY, W_W * W_H * sizeof(cl_float3), NULL, &ret);
	ret = clEnqueueWriteBuffer(opencl->command_queue, opencl->scene_mem_obj, CL_TRUE, 0, sizeof(t_scene), s, 0, NULL, NULL);
	if (ret != CL_SUCCESS)
		ft_print_error("debile");
}

void	ft_opencl_kernel(t_opencl *opencl)
{
	cl_int		ret;
	cl_uint		w;
	cl_uint		h;

	w = W_W;
	h = W_H;
	ret = clBuildProgram(opencl->program, 1, &opencl->device_id, NULL, NULL, NULL);
    if (ret == CL_BUILD_PROGRAM_FAILURE)
	{
		size_t	log_size;
		char	*err;

		clGetProgramBuildInfo(opencl->program, opencl->device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
		err = (char *)malloc(log_size);
		clGetProgramBuildInfo(opencl->program, opencl->device_id, CL_PROGRAM_BUILD_LOG, log_size, err, NULL);
		puts(err);
	}
	opencl->kernel = clCreateKernel(opencl->program, "ft_render", &ret);
	ret = clSetKernelArg(opencl->kernel, 0, sizeof(cl_mem), (void *)&opencl->scene_mem_obj);
	ret = clSetKernelArg(opencl->kernel, 1, sizeof(cl_mem), (void *)&opencl->pixels_mem_obj);
	ret = clSetKernelArg(opencl->kernel, 2, sizeof(cl_uint), (void *)&w);
	ret = clSetKernelArg(opencl->kernel, 3, sizeof(cl_uint), (void *)&h);
}

void	ft_opencl_quit(t_opencl *opencl)
{
	cl_int		ret;

	ret = clFlush(opencl->command_queue);
	ret = clFinish(opencl->command_queue);
	ret = clReleaseKernel(opencl->kernel);
	ret = clReleaseProgram(opencl->program);
	ret = clReleaseMemObject(opencl->scene_mem_obj);
	ret = clReleaseMemObject(opencl->pixels_mem_obj);
	ret = clReleaseCommandQueue(opencl->command_queue);
	ret = clReleaseContext(opencl->context);
}
