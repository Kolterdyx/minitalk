/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 03:21:34 by cigarcia          #+#    #+#             */
/*   Updated: 2022/08/02 05:40:04 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_byte(char b, pid_t pid, int delay)
{
	int	h[2];
	int	i;
	int	j;

	j = 2;
	h[0] = b % 16;
	h[1] = b / 16;
	usleep(delay);
	while (j > 0)
	{
		j--;
		i = 0;
		while (i < h[j])
		{
			send_signal(SIGUSR1, pid, delay);
			i++;
		}
		send_signal(SIGUSR2, pid, delay);
	}
}

void	send_msg(char *msg, pid_t pid, int delay)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		send_byte(msg[i], pid, delay);
		i++;
	}
	send_msg_end(pid, delay);
}

t_msg	*create_msg(int max_size)
{
	t_msg	*msg;

	msg = ft_calloc(1, sizeof(t_msg));
	msg->max_size = max_size;
	msg->buff = 0;
	msg->msg = ft_calloc(max_size + 1, 1);
	msg->msg_len = 0;
	msg->msg_print = 0;
	msg->byte_part = 0;
	return (msg);
}

void	listen(void (handler)(int, siginfo_t *, void *))
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
		usleep(1);
	}
}
