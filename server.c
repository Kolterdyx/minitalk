/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 01:46:35 by cigarcia          #+#    #+#             */
/*   Updated: 2022/08/20 08:36:20 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_msg	*g_msg;

void	handle_msg(char *msg, __attribute__((unused)) int sender)
{
	usleep(100);
	if (msg[0] == 0)
	{
		send_msg("Message recieved (empty)", sender, 20);
		return ;
	}
	ft_printf("%s\n", msg);
	send_msg("Message received", sender, 20);
	if (!ft_strncmp(msg, "exit", 4))
	{
		free(g_msg->msg);
		free(g_msg);
		exit(0);
	}
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

int	main(void)
{
	usleep(30);
	g_msg = create_msg(1024 * 1024);
	ft_printf("%d\n", getpid());
	listen(sig_handler);
}
