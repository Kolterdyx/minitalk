/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comms_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 03:55:13 by cigarcia          #+#    #+#             */
/*   Updated: 2022/08/02 04:45:26 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signal(int signal, pid_t pid, int delay)
{
	kill(pid, signal);
	usleep(delay);
}

void	send_msg_end(pid_t pid, int delay)
{
	send_signal(SIGUSR2, pid, delay);
	send_signal(SIGUSR2, pid, delay);
	send_signal(SIGUSR2, pid, delay);
	send_signal(SIGUSR2, pid, delay);
	send_signal(SIGUSR2, pid, delay);
}
