/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 18:54:55 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/07 12:35:59 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

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

void	ft_opencl_run(t_opencl *opencl, cl_float4 *pixels)
{
	size_t		global_iterm_size;
	size_t		local_iterm_size;
	cl_int		ret;

	global_iterm_size = W_W * W_H;
	local_iterm_size = 64;
	ret = clEnqueueNDRangeKernel(opencl->command_queue, opencl->kernel, 1, NULL,
			&global_iterm_size, &local_iterm_size, 0, NULL, NULL);
	/*ret = clEnqueueReadBuffer(opencl->command_queue, opencl->pixels_mem_obj, 
	  CL_TRUE, 0, W_W * W_H * sizeof(Uint32), pixels, 0, NULL, NULL);*/
	ret = clEnqueueReadBuffer(opencl->command_queue, opencl->pixels_mem_obj, 
			CL_TRUE, 0, W_W * W_H * sizeof(cl_float4), pixels, 0, NULL, NULL);
}




int		main(int argc, char *argv[])
{
	t_input	in;
	t_env	e;
	cl_float4	*cpu;
	t_opencl opencl;


	if (argc <= 3)
		ft_env_init(&e, argc, argv);
	else
		ft_error();
	cpu = (cl_float4 *)malloc(W_W * W_H * sizeof(cl_float4));
	ft_opencl_init(&opencl, "kernels/rtv1.cl");
	ft_memset(&in, SDL_FALSE, sizeof(t_input));
	ft_opencl_mem(&opencl, &e.s);
	ft_opencl_kernel(&opencl);
	ft_opencl_run(&opencl, cpu);
	for (int i = 0; i < W_H * W_H; i++)
		e.pixels[i] = ft_clamp_rgb(cpu[i].s[0], cpu[i].s[1], cpu[i].s[2]);
	ft_env_draw(&e);
	while (!in.quit)
	{
		ft_update_event(&in);
		//	if (ft_process_event(&e, &in))
		//  ft_env_draw(&e);
		SDL_Delay(16);
	}
	ft_opencl_quit(&opencl);
	ft_env_quit(&e);
	free(cpu), cpu = NULL;
	return (0);
}
