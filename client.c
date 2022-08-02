/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 01:46:37 by cigarcia          #+#    #+#             */
/*   Updated: 2022/08/02 05:46:25 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_msg	*g_msg;

void	handle_msg(char *msg, __attribute__((unused)) int sender)
{
	ft_printf("%s\n", msg);
	exit(0);
}

void	register_end(int hex_size)
{
	if (g_msg->buff == 0 && g_msg->byte_part == 0)
	{
		g_msg->msg_print++;
		return ;
	}
	if (g_msg->byte_part < hex_size - 1)
	{
		g_msg->msg[g_msg->msg_len] = g_msg->buff + g_msg->msg[g_msg->msg_len]
			* 16;
		g_msg->buff = 0;
		g_msg->byte_part++;
	}
	else if (g_msg->byte_part == hex_size - 1)
	{
		g_msg->msg[g_msg->msg_len] = g_msg->buff + g_msg->msg[g_msg->msg_len]
			* 16;
		g_msg->buff = 0;
		g_msg->byte_part = 0;
		g_msg->msg_len++;
	}
}

void	sig_handler(int signum, siginfo_t *info,
		__attribute__((unused)) void *context)
{
	if (signum == SIGUSR1)
	{
		g_msg->buff++;
		g_msg->msg_print = 0;
	}
	if (g_msg->msg_print == 3)
	{
		handle_msg(g_msg->msg, info->si_pid);
		free(g_msg->msg);
		g_msg->msg_len = 0;
		g_msg->msg = ft_calloc(g_msg->max_size, 1);
		g_msg->msg_print = 0;
		g_msg->byte_part = 0;
	}
	else if (signum == SIGUSR2)
		register_end(2);
}

int	main(int argc, char **argv)
{
	int		pid;
	char	b;
	int		delay;

	delay = 10;
	b = '?';
	if (argc != 3)
		return (0);
	g_msg = create_msg(1024 * 1024);
	pid = ft_atoi(argv[1]);
	send_msg(argv[2], pid, delay);
	listen(sig_handler);
}
