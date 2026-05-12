/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:22:41 by ldesboui          #+#    #+#             */
/*   Updated: 2026/05/12 15:28:46 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <cctype>
#include <map>
#include <iostream>
#include <climits>

class BitcoinExchange
{
	private:
		std::string						file;
		std::map<std::string, float>	lines;
		BitcoinExchange();
		bool							order;
	public:
		BitcoinExchange(std::string file);
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
	

		class TheException : public std::exception
		{
			private:
				std::string message;
			public:
				~TheException() throw();
				TheException(std::string message);
				const char *what() const throw(); 
		};

		void	readFile();
		void	parse(std::stringstream &str);
		void	parsefirst(std::stringstream &str);
		void	parseDate(std::stringstream &str);
		void	parseValue(std::stringstream &str, std::stringstream &date);
		std::map<std::string, float> &getLines();
};

void	checkDate(std::string y, std::string m, std::string d);
