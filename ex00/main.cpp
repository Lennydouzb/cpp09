/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:45:30 by ldesboui          #+#    #+#             */
/*   Updated: 2026/05/12 15:58:15 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "BitcoinExchange.hpp"
#include <string>
#include <utility>

static void checkFirstLine (std::stringstream &str)
{

	std::string firstval;
	std::string secondval;
	size_t pos = str.str().find(" | ");

    if (pos == std::string::npos)
		throw BitcoinExchange::TheException("Bad input file");

	firstval = str.str().substr(0, pos);
    secondval = str.str().substr(pos + 3);
	if (firstval != "date" && firstval != "value")
		throw BitcoinExchange::TheException("Bad input file field");
	if (secondval != "date" && secondval != "value")
		throw BitcoinExchange::TheException("Bad input file field");
	if (firstval == secondval)
		throw BitcoinExchange::TheException("Duplicated input file field");
}

static void	calculus(std::string date, float value, BitcoinExchange& BtcExchange)
{
	std::map<std::string, float>::iterator it = BtcExchange.getLines().lower_bound(date);
	if (it == BtcExchange.getLines().begin() && it->first != date)
		throw BitcoinExchange::TheException("No values prior to " + date);
	if (it == BtcExchange.getLines().end() || it->first != date)
		--it;
	std::cout << date << " => " << value << " = " << it->second * value << std::endl;
}

static void	parseLine(std::string tmp, BitcoinExchange &BtcExchange)
{

	size_t pos = tmp.find(" | ");

    if (pos == std::string::npos)
		throw BitcoinExchange::TheException("Bad input file format");

    std::string dateS = tmp.substr(0, pos);

    std::string valueS = tmp.substr(pos + 3);
	std::stringstream date(dateS);
	std::stringstream value(valueS);

	std::string year;
	std::string month;
	std::string day;
	std::getline(date, year, '-');	
	std::getline(date, month, '-');
	std::getline(date, day);
	if (!year.empty() && !month.empty() && !day.empty())
	{
		std::stringstream streamYear(year);
		std::stringstream streamMonth(month);
		std::stringstream streamDay(day);

		int		intYear;
		int		intMonth;
		int		intDay;
		
		float		floatValue;

		if (!(streamYear >> intYear) || !(streamDay >> intDay)
				|| !(streamMonth >> intMonth))
			throw BitcoinExchange::TheException("Input file date is not even a number");
		if (intYear < 2009 || (intMonth < 1 || intMonth > 12) || intDay < 1 || intDay > 31)
			throw BitcoinExchange::TheException("Bad input =>" + dateS);
		if (intMonth == 4 || intMonth == 6 || intMonth == 9 || intMonth == 11)
		{
			if (intDay > 30)
				throw BitcoinExchange::TheException("input date is out of bound");
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
					throw BitcoinExchange::TheException("input date is out of bound");
			}
			else
			{
				if (intDay > 28)
					throw BitcoinExchange::TheException("input date is out of bound");
			}
		}

		if (!(value >> floatValue))
			throw BitcoinExchange::TheException("Not a correct digit");
		if (floatValue < 0)
			throw BitcoinExchange::TheException("not a positive number");
		if (floatValue > 1000)
			throw BitcoinExchange::TheException("too large");
		calculus(dateS, floatValue, BtcExchange);
	}
	else
		throw BitcoinExchange::TheException("Input file is badly typed");

}

int	main(int ac, char **av)

{
	std::string str;
	if (ac < 2)
		return 1;
	std::ifstream file(av[1]);
	BitcoinExchange BtcClienCsv("data.csv");
	try
	{
		BtcClienCsv.readFile();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return (1);
	}
	if (file.is_open())
	{
		try
		{
			std::getline(file, str);
			std::stringstream sstr(str);
			checkFirstLine(sstr);
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
			return 1;
		}
		while (std::getline(file, str))
		{
			try
			{
				parseLine(str, BtcClienCsv);
			}
			catch(std::exception &e)
			{
				std::cout << e.what() << std::endl;
			}
		}
	}


}
