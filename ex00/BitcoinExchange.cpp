/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:46:10 by ldesboui          #+#    #+#             */
/*   Updated: 2026/05/12 15:56:39 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <cctype>
#include <sstream>

BitcoinExchange::TheException::~TheException() throw() {};
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
		throw BitcoinExchange::TheException("File doesn't exist");
	std::getline(csv, str);
	std::stringstream	ss(str);
	this->parsefirst(ss);
	while (std::getline(csv, str))
	{	
		std::stringstream	ss(str);
		this->parse(ss);
	}
}

void BitcoinExchange::parse(std::stringstream &str)
{
	if (order == 1)
	{
		std::string date;
		std::getline(str, date, ',');
		std::stringstream dateStream(date);
		this->parseDate(dateStream);
		
		std::string value;
		std::getline(str, value);
		std::stringstream valueStream(value);
		this->parseValue(valueStream, dateStream);
	}
}

BitcoinExchange::TheException::TheException(std::string message)
{
	this->message = message;
}

const char * BitcoinExchange::TheException::what()const throw()
{
	return (message.c_str());
}

std::map<std::string, float> &BitcoinExchange::getLines()
{
	return (this->lines);
}

void BitcoinExchange::parsefirst(std::stringstream &str)
{
	std::string firstval;
	std::string secondval;
	std::getline(str, firstval,',');
	if (firstval != "date" && firstval != "exchange_rate")
		throw BitcoinExchange::TheException("Bad csv field");
	std::getline(str, secondval);
	if (secondval != "date" && secondval != "exchange_rate")
		throw BitcoinExchange::TheException("Bad csv field");
	if (firstval == secondval)
		throw BitcoinExchange::TheException("Duplicated csv field");
	if (firstval == "date")
		this->order = 1;
	else
		this ->order = 0;
}

void BitcoinExchange::parseDate(std::stringstream &str)
{
	std::string year;
	std::string month;
	std::string day;
	std::getline(str, year, '-');	
	std::getline(str, month, '-');
	std::getline(str, day);
	if (!year.empty() && !month.empty() && !day.empty())
	{
		std::stringstream streamYear(year);
		std::stringstream streamMonth(month);
		std::stringstream streamDay(day);

		int		intYear;
		int		intMonth;
		int		intDay;

		if (!(streamYear >> intYear) || !(streamDay >> intDay)
				|| !(streamMonth >> intMonth))
			throw BitcoinExchange::TheException("Csv date might not be an int");
		if (intYear < 2009 || (intMonth < 1 || intMonth > 12) || intDay < 1 || intDay > 31)
			throw BitcoinExchange::TheException("CSV date is out of bound");
		if (intMonth == 4 || intMonth == 6 || intMonth == 9 || intMonth == 11)
		{
			if (intDay > 30)
				throw BitcoinExchange::TheException("CSV date is out of bound");
		}
		if (intMonth == 2)
		{
			int	flag;
			if (intYear % 400 == 0)
				flag = 1;
			if (intYear % 100 == 0)
				flag = 0;
			if (intYear % 4 == 0)
				flag = 1;
			if (flag == 1)
			{
				if (intDay > 29)
					throw BitcoinExchange::TheException("CSV date is out of bound");
			}
			else
			{
				if (intDay > 28)
					throw BitcoinExchange::TheException("CSV date is out of bound");
			}
		}
		if (this->lines.find(str.str()) == this->lines.end())
			this->lines.insert(std::make_pair(str.str(), 0));
		else
			throw BitcoinExchange::TheException("Duplicated row");
	}
	else
		throw BitcoinExchange::TheException("Bad csv date");

}

void BitcoinExchange::parseValue(std::stringstream &str, std::stringstream &date)
{
	float floatValue;

	if (!(str >> floatValue))
		throw BitcoinExchange::TheException("Bad value");
	if (floatValue < 0)
		throw BitcoinExchange::TheException("Negative csv value");
	this->lines[date.str()] = floatValue;
}
