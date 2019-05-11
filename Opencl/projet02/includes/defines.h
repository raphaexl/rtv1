/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 17:33:12 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/11 20:15:25 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H
# ifdef __APPLE__
# include <OpenCL/opencl.h>
# else
# include <CL/cl.h>
#endif
# include <math.h>
# define MAX_SOURCE_SIZE 0x1000000
# define RAY_T_MIN 0.0001
# define RAY_T_MAX 1.0e30
# define M_I_PI 1.0 / M_PI
# define SCR_WIDTH 1024
# define SCR_HEIGHT 1024
# define N_MAX 10
# define W_W 1024
# define W_H 1024

#endif
