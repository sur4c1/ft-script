/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyy <yyyyyy@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 06:14:48 by yyyyyy            #+#    #+#             */
/*   Updated: 2024/11/25 05:05:44 by yyyyyy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/******************************** SIGNED **************************************/

typedef	signed char		s8;
typedef	short			s16;
typedef	int				s32;
typedef	long			s64;

/******************************** UNSIGNED ************************************/

typedef	unsigned char	u8;
typedef	unsigned short	u16;
typedef	unsigned int	u32;
typedef	unsigned long	u64;

/******************************* FLOATING *************************************/

typedef	float			f32;
typedef	double			f64;

/********************************** PTR ***************************************/

typedef void			*ptr;
typedef char			*str;

/********************************** SIZE **************************************/

typedef unsigned long	usz;
typedef long			ssz;

/********************************** BOOL **************************************/

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

/****************************** UTILITIES **************************************/

typedef enum e_ret
{
	SUCCESS,
	FAILURE
}	t_ret;

typedef enum e_error
{
	OK,
	ERROR,
	UKNOWN_OPTION,
	UKNOWN_HOST
}	t_error;

typedef int t_fd;
