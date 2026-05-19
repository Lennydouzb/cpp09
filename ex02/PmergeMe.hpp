/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 12:45:49 by ldesboui          #+#    #+#             */
/*   Updated: 2026/05/13 16:28:19 by ldesboui         ###   ########.fr       */
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
		PmergeMe(const PmergeMe &other);
		~PmergeMe();
		PmergeMe &operator=(const PmergeMe &other);
		std::vector<size_t> getJacobsthalVector(size_t	max) const;	
		void	fordJohnsonVector(std::vector<std::pair<char,char>> &arr);
		void	fordJohnsonDeque(std::deque<char> &arr);
};

bool	checkdigits(char **args, int size);
std::vector<char> createVector(char **av, int size);
std::deque<char> createDeque(char **av, int size);
