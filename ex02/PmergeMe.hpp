/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 12:45:49 by ldesboui          #+#    #+#             */
/*   Updated: 2026/05/26 15:52:04 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once
#include <vector>
#include <deque>
#include <iostream>
#include <sstream>
#include <climits>

class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(const PmergeMe &other);
		~PmergeMe();
		PmergeMe &operator=(const PmergeMe &other);
		std::vector<size_t> getJacobsthalVector(size_t	max) const;	
		std::deque<size_t>	getJacobsthalDeque(size_t	max) const;	
		void	fordJohnsonVector(std::vector<int> &arr);
		void	fordJohnsonDeque(std::deque<int> &arr);
		void	doAlgorithms(char **av, int size);
};

bool		checkGood(std::vector<int> &vec, std::deque<int> &deq, std::vector<int> before);
long long	getTime();
std::vector<std::pair<int, int> >::iterator findVector(int neelde, std::vector<std::pair<int, int> > &haystack);
std::deque<std::pair<int, int> >::iterator findDeque(int neelde, std::deque<std::pair<int, int> > &haystack);
bool	checkdigits(char **args, int size);
