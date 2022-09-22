/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 01:46:35 by cigarcia          #+#    #+#             */
/*   Updated: 2022/09/22 10:19:52 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sig_handler(int signum, __attribute__((unused)) siginfo_t *info,
		__attribute__((unused)) void *context)
{
	static char	c;
	static int	bits;

	if (signum == SIGUSR1)
	{
		bits++;
	}
	else if (signum == SIGUSR2)
	{
		c += 1 << bits;
		bits++;
	}
	if (bits == 8)
	{
		if (c == 0)
		{
			write(1, "\n", 1);
			send_msg("Message recieved", info->si_pid, 30);
		}
		write(1, &c, 1);
		bits = 0;
		c = 0;
	}
}

int	main(void)
{
	usleep(30);
	ft_printf("%d\n", getpid());
	listen(sig_handler);
}
