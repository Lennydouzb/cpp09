/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:22:41 by ldesboui          #+#    #+#             */
/*   Updated: 2026/05/07 02:39:39 by ldesboui         ###   ########.fr       */
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
	public:
		BitcoinExchange(std::string file);
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
	

		class FileDoesntExistException : public std::exception
		{
			public:
				const char *what() const throw(); 
		};
		class BadCsvException : public std::exception
		{
			public:
				const char *what() const throw(); 
		};
		class	NothingReadException : public std::exception
		{
			public:
				const char *what() const throw(); 
		};
		class	BadNumberException : public std::exception
		{
			public:
				const char *what() const throw(); 
		};

		void	readFile();
		void	parse(std::stringstream &str);
		std::map<std::string, float> &getLines();
};
void	trim(std::string &str);
void	calculus(BitcoinExchange &csv, BitcoinExchange &file);
