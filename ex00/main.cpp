/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:45:30 by ldesboui          #+#    #+#             */
/*   Updated: 2026/05/12 03:47:12 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "BitcoinExchange.hpp"
#include <string>
#include <utility>
#include <vector>

static void checkFirstLine (std::stringstream &str)
{

	std::string firstval;
	std::string secondval;
	std::getline(str, firstval,',');
	if (firstval != "data" && firstval != "exchange_rate")
		throw BitcoinExchange::TheException("Bad csv field");
	std::getline(str, secondval);
	if (secondval != "data" && secondval != "exchange_rate")
		throw BitcoinExchange::TheException("Bad csv field");
	if (firstval == secondval)
		throw BitcoinExchange::TheException("Duplicated csv field");
}

static void	parseLine(std::string tmp, std::vector<std::pair<std::string, float>> values)
{

	std::stringstream full(tmp);
	std::string dateS;
	std::string valueS;

	std::getline(full, dateS, '|');
	std::getline(full, valueS, '|');
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
		
		int		floatValue;

		if (!(streamYear >> intYear) || !(streamDay >> intDay)
				|| !(streamMonth >> intMonth))
			throw BitcoinExchange::TheException("Input file date is not a date");
		if (intYear < 2009 || (intMonth < 1 || intMonth > 12) || intDay < 1 || intDay > 31)
			throw BitcoinExchange::TheException("Bad input =>" + dateS);
		if (!(value >> floatValue))
			throw BitcoinExchange::TheException("Not a correct digit");
		if (floatValue < 0)
			throw BitcoinExchange::TheException("not a positive number");
		if (floatValue > 1000)
			throw BitcoinExchange::TheException("too large");
		values.push_back(std::make_pair(dateS, floatValue));
	}
	else
		throw BitcoinExchange::TheException("Input file is badly typed");

}

int	main(int ac, char **av)

{

	std::vector<std::pair<std::string, float>> fileValues;
	std::string str;
	if (ac < 2)
		return 1;
	std::ifstream file(av[1]);
	try
	{
		BitcoinExchange BtcClienCsv("data.csv");
		BtcClienCsv.readFile();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	if (!file.is_open())
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
		}
		while (std::getline(file, str))
		{
			try
			{
				parseLine(str, fileValues);	
			}
			catch (std::exception &e)
			{
				std::cout << e.what() << std::endl;
			}

		}
	}


}
