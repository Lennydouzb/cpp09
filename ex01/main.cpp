/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:45:30 by ldesboui          #+#    #+#             */
/*   Updated: 2026/05/12 16:56:52 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "RPN.hpp"

int	main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}
	try
	{
		RPN myRpn;
		myRpn.proceedRPN(av[1]);
		if (myRpn.getStack().size() != 1)
			throw RPN::TheException("Error");
		std::cout << myRpn.getStack().top() << std::endl;
	}catch(std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
}
