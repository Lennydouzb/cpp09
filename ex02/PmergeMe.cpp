/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 14:33:23 by ldesboui          #+#    #+#             */
/*   Updated: 2026/05/13 15:45:34 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}

bool	checkdigits(char **args, int size)
{

	int	i = 0;

	while (i < size)
	{
		if (!std::isdigit(args[i][0]))
			return false;
		++i;
	}
	return true;
}

PmergeMe::PmergeMe(char **args, int size)
{
	int	i = 0;

	while (i < size)
	{
		this->deque.push_back(args[i][0]);
		this->vector.push_back(args[i][0]);
		++i;
	}
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
	this->deque = other.deque;
	this->vector = other.vector;
}

PmergeMe::~PmergeMe(){}

PmergeMe & PmergeMe::operator=(const PmergeMe &other)
{
	if (this == &other)
		return (*this);
	this->deque = other.deque;
	this->vector = other.vector;
	return *this;
}

void PmergeMe::fordJohnsonVector(std::vector<char> arr)
{
	std::vector<std::pair<char, char>> pairs;
	char solo;
	if (arr.size() == 1)
		return ;
	for(std::vector<char>::iterator it = arr.begin(); it != arr.end(); ++it)
	{
		if (arr.size() % 2 == 1)
			solo = *(arr.end() - 1);
		pairs.push_back(std::make_pair(*it, *(++it)));
	}
}

void PmergeMe::fordJohnsonDeque(std::deque<char> arr)
{

}

