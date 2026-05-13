/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 14:33:23 by ldesboui          #+#    #+#             */
/*   Updated: 2026/05/13 16:49:57 by ldesboui         ###   ########.fr       */
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

std::vector<char> createVector(char **av, int size)
{
	int	i = 0;
	std::vector<char> vector;
	while (i < size)
	{
		vector.push_back(av[i][0]);
		++i;
	}
	return vector;
}

std::deque<char> createDeque(char **av, int size)
{
	int	i = 0;
	std::deque<char> deque;
	while (i < size)
	{
		deque.push_back(av[i][0]);
		++i;
	}
	return deque;
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

