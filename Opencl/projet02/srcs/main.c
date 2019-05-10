/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 18:54:55 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/10 19:22:52 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	ft_opencl_run(t_opencl *opencl, Uint32	*pixels)
{
	size_t		global_iterm_size;
	size_t		local_iterm_size;
	cl_int		ret;

	global_iterm_size = opencl->w * opencl->h;
	local_iterm_size = 64;
	ret = clEnqueueNDRangeKernel(opencl->command_queue, opencl->kernel, 1, NULL,
			&global_iterm_size, &local_iterm_size, 0, NULL, NULL);
	ret = clEnqueueReadBuffer(opencl->command_queue, opencl->pixels_mem_obj,
			CL_TRUE, 0, opencl->w * opencl->h * sizeof(Uint32), pixels, 0, NULL, NULL);
}

int		main(int argc, char *argv[])
{
	t_input	in;
	cl_int	status;
	t_ptr	ptr;
	t_opencl opencl;
	Uint32	*pixels;

	status = EXIT_FAILURE;
	ft_opencl_init(&opencl, "kernels/rtv1.cl");
	if (argc == 2)
		ft_scene_init(&opencl.scene, argv[1]);
	else
		ft_scene_init_default(&opencl.scene);
	ft_opencl_mem(&opencl);
	opencl.scene.cam = ft_camera_perspective(ft_vector(0.0f, 1.0f, -5.0f),
			ft_vector(0.0f, 1.0f, 0.0f), ft_vector(0.0f, 0.0f, 0.0f), 25.0f * M_PI / 180,
			(cl_float)opencl.scene.scr_width / (cl_float)opencl.scene.scr_height);
	if (ft_sdl_init(&ptr, opencl.scene.scr_width, opencl.scene.scr_height, "42"))
		goto Quit;
	if (!(pixels = (Uint32 *)malloc(sizeof(Uint32) * opencl.scene.scr_width * opencl.scene.scr_height)))
		perror("Error Malloc pixels");
	memset(pixels, 0xFFFF00, sizeof(Uint32) * opencl.scene.scr_width * opencl.scene.scr_height);
	ft_memset(&in, SDL_FALSE, sizeof(t_input));
	ft_scene_print(&opencl.scene);
	ft_opencl_kernel(&opencl);
	ft_opencl_run(&opencl, pixels);
	printf("n = %d\n", opencl.scene.nb_objects);
	while (!in.quit)
	{
		ft_update_event(&in);
		ft_update_renderer(ptr, pixels, opencl.scene.scr_width);
	//	ft_draw(&s, pixels);
		SDL_RenderPresent(ptr.renderer);
	}
	status = EXIT_SUCCESS;
Quit:
	ft_opencl_quit(&opencl);
	ft_scene_clear(&opencl.scene, &pixels);
	ft_sdl_quit(&ptr);
	return (status);
}
