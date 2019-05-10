/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 18:54:55 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/10 13:07:38 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	ft_opencl_run(t_opencl *opencl, Uint32	*pixels)
{
	size_t		global_iterm_size;
	size_t		local_iterm_size;
	cl_int		ret;

	global_iterm_size = W_W * W_H;
	local_iterm_size = 64;
	ret = clEnqueueNDRangeKernel(opencl->command_queue, opencl->kernel, 1, NULL,
		   	&global_iterm_size, &local_iterm_size, 0, NULL, NULL);
	ret = clEnqueueReadBuffer(opencl->command_queue, opencl->pixels_mem_obj, 
			CL_TRUE, 0, W_W * W_H * sizeof(Uint32), pixels, 0, NULL, NULL);
}


int		main(int argc, char *argv[])
{
	t_input	in;
	t_env	e;
	t_opencl opencl;


	if (argc <= 3)
		ft_env_init(&e, argc, argv);
	else
		ft_error();
	ft_opencl_init(&opencl, "kernels/rtv1.cl");
	ft_memset(&in, SDL_FALSE, sizeof(t_input));
	ft_opencl_mem(&opencl, &e.s);
	ft_opencl_kernel(&opencl);
	ft_opencl_run(&opencl, e.pixels);
	while (!in.quit)
	{
		ft_update_event(&in);
		/*if (ft_process_event(&e, &in))
		  ft_env_draw(&e);*/
		SDL_RenderClear(e.ptr.renderer);
		ft_update_renderer(&e.ptr, e.pixels);
		SDL_RenderPresent(e.ptr.renderer);
		SDL_Delay(16);
	}
	ft_opencl_quit(&opencl);
	ft_env_quit(&e);
	return (0);
}
