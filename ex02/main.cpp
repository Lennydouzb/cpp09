/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 14:35:56 by ldesboui          #+#    #+#             */
/*   Updated: 2026/05/13 16:04:48 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "PmergeMe.hpp"

int	main(int ac, char **av)
{
	if (ac < 2)
		return 1;
	if (checkdigits(&av[1], ac - 1))
	{
		PmergeMe myPmergeMe(&av[1], ac - 1);
		myPmergeMe.fordJohnsonDeque();
		myPmergeMe.fordJohnsonVector();
	}
}
