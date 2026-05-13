/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 12:45:49 by ldesboui          #+#    #+#             */
/*   Updated: 2026/05/13 15:35:24 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once
#include <vector>
#include <deque>
#include <iostream>

class PmergeMe
{
	private:
		std::vector<char>	vector;
		std::deque<char>		deque;
	public:
		PmergeMe();
		PmergeMe(char **args, int size);
		PmergeMe(const PmergeMe &other);
		~PmergeMe();
		PmergeMe &operator=(const PmergeMe &other);
		void	fordJohnsonVector(std::vector<char> arr);
		void	fordJohnsonDeque(std::deque<char> arr);
};

bool	checkdigits(char **args, int size);
