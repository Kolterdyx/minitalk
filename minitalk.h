/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cigarcia <cigarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 01:46:48 by cigarcia          #+#    #+#             */
/*   Updated: 2022/09/22 10:02:39 by cigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_msg
{
	char	*msg;
	char	buff;
	int		msg_len;
	int		msg_print;
	int		byte_part;
	int		max_size;
}			t_msg;

void		send_msg(char *msg, pid_t pid, int delay);
void		listen(void (handler)(int, siginfo_t *, void *));
void		send_byte(char b, pid_t pid, int delay);
void		send_signal(int signal, pid_t pid, int delay);

#endif