/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 14:33:23 by ldesboui          #+#    #+#             */
/*   Updated: 2026/05/26 14:49:29 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sys/time.h>
#include <algorithm>

PmergeMe::PmergeMe(){}

void	PmergeMe::doAlgorithms(char **av, int size)
{
	int	i =0;
	std::vector<int>	vec;
	std::vector<int>	before;
	std::deque<int>		deq;

	while (i < size)
	{
		int val;
		std::stringstream tmp(av[i]);
		tmp >> val;
		vec.push_back(val);
		deq.push_back(val);
		before.push_back(val);
		++i;
	}
	long long begin = getTime();
	this->fordJohnsonVector(vec);
	long long end = getTime();

	long long beginDeque = getTime();
	this->fordJohnsonDeque(deq);
	long long endDeque = getTime();
	if (deq.size() != vec.size())
		std::cerr << "Error" << std::endl;
	if (deq.size() == vec.size() && !(std::equal(vec.begin(), vec.end(), deq.begin())))
		std::cerr << "Error" << std::endl;
	std::cout << "Before: ";
	for (std::vector<int>::iterator it = before.begin(); it != before.end() - 1; ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << *(before.end() - 1) << std::endl;
	std::cout << "After: ";
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end() - 1; ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << *(vec.end() - 1) << std::endl;
	std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : " << end - begin << " us" << std::endl;
	std::cout << "Time to process a range of " << deq.size() << " elements with std::deque : " << endDeque - beginDeque << " us" << std::endl;	
}

long long getTime()
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    
    return (static_cast<long long>(tv.tv_sec) * 1000000) + tv.tv_usec;
}

bool	checkdigits(char **args, int size)
{

	int	i = 0;

	while (i < size)
	{
		std::stringstream val(args[i]);
		long long test;
		if (!(val >> test))
			return false;
		if (test > INT_MAX)
			return false;
		if (test < 0)
			return false;
		++i;
	}
	return true;
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
	(void)other;
}

PmergeMe::~PmergeMe(){}

PmergeMe & PmergeMe::operator=(const PmergeMe &other)
{
	if (this == &other)
		return (*this);
	return *this;
}

void PmergeMe::fordJohnsonVector(std::vector<int> &arr)
{
	std::vector<std::pair<int, int> > pairs;
	std::vector<int> winners;
	std::vector<int> losers;
	int solo;
	bool hasSolo = 0;

	if (arr.size() == 1)
		return ;
	// keep the solo number
	if (arr.size() % 2 == 1)
	{
			solo = arr.back();
			arr.pop_back();
			hasSolo = 1;
	}
	for(std::vector<int>::iterator it = arr.begin(); it != arr.end();)
	{
		int firstInt = *it;
		++it;
		int secondInt = *it;
		pairs.push_back(std::make_pair(firstInt, secondInt));
		++it;
		if (pairs.back().first < pairs.back().second)
			std::swap(pairs.back().first, pairs.back().second);
		winners.push_back(pairs.back().first);	
		losers.push_back(pairs.back().second);
	}
	//recursivity to make pairs of pairs....
	fordJohnsonVector(winners);
	std::vector<size_t> jacob = getJacobsthalVector(winners.size());
	std::vector<int> main;
	main = winners;
	std::vector<int>::iterator place;
	size_t previous = 0;
	for (size_t i = 0; i < jacob.size(); ++i)
	{
		size_t current = jacob[i];
		if (jacob[i] > winners.size())
			current = winners.size();
		for (size_t j = current; j > previous; --j)
		{
			//a bit tricky here : the jacob vector get us the indexes then between 3 and 5 for example its 5th then 4th
			std::vector<std::pair<int, int> >::iterator aPair = findVector(winners[j - 1], pairs);
			std::vector<int>::iterator winnerPos = std::find(main.begin(), main.end(), aPair->first);
			place = std::lower_bound(main.begin(), winnerPos, aPair->second);
			main.insert(place, aPair->second);
		}
		previous = current;
	}
	if (hasSolo)
	{
		place = std::lower_bound(main.begin(), main.end(), solo);
		main.insert(place, solo);
	}
	arr = main;
}

void PmergeMe::fordJohnsonDeque(std::deque<int> &arr)
{
	std::deque<std::pair<int, int> > pairs;
	std::deque<int> winners;
	std::deque<int> losers;
	int solo;
	bool hasSolo = 0;

	if (arr.size() == 1)
		return ;
	// keep the solo number
	if (arr.size() % 2 == 1)
	{
			solo = arr.back();
			arr.pop_back();
			hasSolo = 1;
	}
	for(std::deque<int>::iterator it = arr.begin(); it != arr.end();)
	{
		int firstInt = *it;
		++it;
		int secondInt = *it;
		pairs.push_back(std::make_pair(firstInt, secondInt));
		++it;
		if (pairs.back().first < pairs.back().second)
			std::swap(pairs.back().first, pairs.back().second);
		winners.push_back(pairs.back().first);	
		losers.push_back(pairs.back().second);
	}
	//recursivity to make pairs of pairs....
	fordJohnsonDeque(winners);
	std::deque<size_t> jacob = getJacobsthalDeque(winners.size());
	std::deque<int> main;
	main = winners;
	std::deque<int>::iterator place;
	size_t previous = 0;
	for (size_t i = 0; i < jacob.size(); ++i)
	{
		size_t current = jacob[i];
		if (jacob[i] > winners.size())
			current = winners.size();
		for (size_t j = current; j > previous; --j)
		{
			//a bit tricky here : the jacob deque get us the indexes then between 3 and 5 for example its 5th then 4th
			std::deque<std::pair<int, int> >::iterator aPair = findDeque(winners[j - 1], pairs);
			std::deque<int>::iterator winnerPos = std::find(main.begin(), main.end(), aPair->first);
			place = std::lower_bound(main.begin(), winnerPos, aPair->second);
			main.insert(place, aPair->second);
		}
		previous = current;
	}
	if (hasSolo)
	{
		place = std::lower_bound(main.begin(), main.end(), solo);
		main.insert(place, solo);
	}
	arr = main;
}

std::vector<std::pair<int, int> >::iterator findVector(int needle, std::vector<std::pair<int, int> > &haystack)
	
{
	for (std::vector<std::pair<int, int> >::iterator it = haystack.begin(); it != haystack.end(); ++it)
	{
		if (needle == it->first)
			return it;
	}
	return haystack.begin();
}

std::deque<std::pair<int, int> >::iterator findDeque(int needle, std::deque<std::pair<int, int> > &haystack)
	
{
	for (std::deque<std::pair<int, int> >::iterator it = haystack.begin(); it != haystack.end(); ++it)
	{
		if (needle == it->first)
			return it;
	}
	return haystack.begin();
}
std::vector<size_t> PmergeMe::getJacobsthalVector(size_t max) const
{
	std::vector<size_t> jacob;
    jacob.push_back(1);
    jacob.push_back(3);
    
    while (jacob.back() < max)
	{
        size_t next = jacob.back() + 2 * *(jacob.end() - 2);
        jacob.push_back(next);
    }
    return jacob;
}

std::deque<size_t>	PmergeMe::getJacobsthalDeque(size_t	max) const
{
	std::deque<size_t> jacob;
    jacob.push_back(1);
    jacob.push_back(3);
    
    while (jacob.back() < max)
	{
        size_t next = jacob.back() + 2 * *(jacob.end() - 2);
        jacob.push_back(next);
    }
    return jacob;
}

