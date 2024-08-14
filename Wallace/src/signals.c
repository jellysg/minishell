/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wchow <wchow@42mail.sutd.edu.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 04:46:52 by wchow             #+#    #+#             */
/*   Updated: 2024/08/13 04:51:41 by wchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test.h"

void	resetPrompt(int signum)
{
	(void)signum;
	write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ignore_sigquit()
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	handleSignals()
{
	struct sigaction	sa;
	
	//Signal handling and removing CTL+C (need to add CTRL+/)
	ignore_sigquit();
	sa.sa_handler = &resetPrompt; //Gives prompt to usr and waits for input
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}