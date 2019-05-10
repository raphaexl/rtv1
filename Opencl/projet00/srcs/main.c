/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 14:05:24 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/10 13:59:03 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/prototypes.h"

static Uint32	ft_clamp_rgb(float red, float green, float blue)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = (unsigned char)fmin(red * 255.0 + .5, 255.0);
	g = (unsigned char)fmin(green * 255.0 + .5, 255.0);
	b = (unsigned char)fmin(blue * 255.0 + .5, 255.0);
	return (b + (g << 8) + (r << 16));
}

void	ft_opencl_run(t_opencl *opencl, cl_float4 *cpu)
{
	size_t		global_iterm_size;
	size_t		local_iterm_size;
	cl_int		ret;

	global_iterm_size = SCR_WIDTH * SCR_HEIGHT;
	local_iterm_size = 64;
	ret = clEnqueueNDRangeKernel(opencl->command_queue, opencl->kernel, 1, NULL, &global_iterm_size, &local_iterm_size, 0, NULL, NULL);
	ret = clEnqueueReadBuffer(opencl->command_queue, opencl->cpu_mem_obj, CL_TRUE, 0, SCR_WIDTH * SCR_HEIGHT * sizeof(cl_float3), cpu, 0, NULL, NULL);
}


int		main(void)
{
	t_opencl	opencl;
	t_ptr		ptr;
	t_input		in;
	cl_float4		*cpu;
	Uint32			*pixels;

	memset(&in, SDL_FALSE, sizeof(t_input));
	ft_sdl_init(&ptr, "1337");
	ft_opencl_init(&opencl, "kernels/pixels.cl");
	cpu = (cl_float4 *)malloc(sizeof(cl_float4) * SCR_WIDTH * SCR_HEIGHT);
	pixels = (Uint32 *)malloc(sizeof(Uint32 ) * SCR_WIDTH * SCR_HEIGHT);
	ft_opencl_mem(&opencl);
	ft_opencl_kernel(&opencl);
	ft_opencl_run(&opencl, cpu);
	for (int i = 0; i < SCR_WIDTH * SCR_HEIGHT; i++)
		pixels[i] = ft_clamp_rgb(cpu[i].s[0], cpu[i].s[1], cpu[i].s[2]);
	while (!in.quit)
	{
		ft_update_event(&in);
		ft_update_renderer(&ptr, pixels);
		SDL_RenderPresent(ptr.renderer);
		SDL_Delay(10);
	}
	ft_opencl_quit(&opencl);
	ft_sdl_quit(&ptr);
	free(cpu), cpu = NULL;
	free(pixels), pixels = NULL;
	return (0);
}
