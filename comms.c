/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 03:21:34 by cigarcia          #+#    #+#             */
/*   Updated: 2022/09/22 10:16:21 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_byte(char b, pid_t pid, int delay)
{
	int		i;
	char	j;

	i = 0;
	j = 1;
	usleep(delay);
	while (i < 8)
	{
		if (j & b)
			send_signal(SIGUSR2, pid, delay);
		else
			send_signal(SIGUSR1, pid, delay);
		j <<= 1;
		i++;
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
	send_byte((char)0, pid, delay);
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

void	send_signal(int signal, pid_t pid, int delay)
{
	kill(pid, signal);
	usleep(delay);
}
