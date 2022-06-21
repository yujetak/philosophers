/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:57:32 by yotak             #+#    #+#             */
/*   Updated: 2022/06/21 16:41:04 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    free_info(t_info *info)
{
    free(info->forks);
    free(info->m_forks);
    free(info->philo);
    free(info->thread);
    free(info);
}