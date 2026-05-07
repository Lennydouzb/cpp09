/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:46:10 by ldesboui          #+#    #+#             */
/*   Updated: 2026/05/07 02:39:28 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <cctype>

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(std::string file)
{
	this->file= file;
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	this->file = other.file;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this == &other)
		return (*this);
	this->file = other.file;
	return (*this);
}

void BitcoinExchange::readFile()
{
	std::ifstream		csv((this->file).c_str());
	std::string			str;
	if (!(csv.is_open()))
		throw BitcoinExchange::FileDoesntExistException();
	while (std::getline(csv, str))
	{	
		std::stringstream	ss(str);
		this->parse(ss);
	}
}

void BitcoinExchange::parse(std::stringstream &str)
{
	std::string		date, value;
	std::getline(str, date, this->sep);	
	std::getline(str, value);
	trim(date);
	trim(value);
	if (date == "date")
		return ;
	std::stringstream streamDate(date);
	std::string year;
	std::string month;
	std::string day;
	std::getline(streamDate, year, '-');	
	std::getline(streamDate, month, '-');
	std::getline(streamDate, day);
	if (!year.empty() && !month.empty() && !day.empty())
	{
		std::stringstream streamYear(year);
		std::stringstream streamMonth(month);
		std::stringstream streamDay(day);
		std::stringstream streamValue(value);

		int		intYear;
		int		intMonth;
		int		intDay;
		float	floatValue;

		if (!(streamYear >> intYear) || !(streamDay >> intDay)
				|| !(streamMonth >> intMonth) || !(streamValue >> floatValue))
			throw BitcoinExchange::BadCsvException();
		if (intYear < 2009 || (intMonth < 1 || intMonth > 12) || intDay < 1 || intDay > 31)
			throw BitcoinExchange::BadCsvException();
		if (floatValue > INT_MAX || floatValue < 0)
			throw BitcoinExchange::BadNumberException();
		this->lines.insert(std::make_pair(date, floatValue));
	}
	else
		throw BitcoinExchange::BadCsvException();
}
	
const char * BitcoinExchange::FileDoesntExistException::what()const throw()
{
	return ("Error : File doesn't exist");
}

const char * BitcoinExchange::BadCsvException::what()const throw()
{
	return ("Error : this csv file is garbage");
}

const char * BitcoinExchange::NothingReadException::what()const throw()
{

	return ("Error : nothing has been read");
}

void	trim(std::string &str)
{
	std::string::iterator it = str.begin();
	std::string::iterator itend = str.end();
	std::string::iterator start = str.begin();
	std::string::iterator end = str.end();
	while (it != itend && (*it == ' ' || *it == '\t'))
		start++;
	while (it != itend && (*itend == ' ' || *itend == '\t'))
		end--;
	std::string	tmp(start, end);
	str = tmp;
}

const char * BitcoinExchange::BadNumberException::what()const throw()
{
	return ("Error : bad number");
}

std::map<std::string, float> &BitcoinExchange::getLines()
{
	return (this->lines);
}

