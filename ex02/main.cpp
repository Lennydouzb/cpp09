/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 14:35:56 by ldesboui          #+#    #+#             */
/*   Updated: 2026/05/13 16:29:38 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "PmergeMe.hpp"

int	main(int ac, char **av)
{
	if (ac < 2)
		return 1;
	if (checkdigits(&av[1], ac - 1))
	{
		PmergeMe myPmergeMe;
		std::deque<char> deque = createDeque(&av[1], ac - 1);
		std::vector<char> vector = createVector(&av[1], ac - 1);
		myPmergeMe.fordJohnsonDeque(deque);
		myPmergeMe.fordJohnsonVector(vector);
	}
}
