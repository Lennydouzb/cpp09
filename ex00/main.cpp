/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 15:45:30 by ldesboui          #+#    #+#             */
/*   Updated: 2026/05/07 02:38:54 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "BitcoinExchange.hpp"

int	main(int ac, char **av)
{
	if (ac < 2)
		return 1;
	try
	{
		BitcoinExchange BtcClienCsv("data.csv", ',');
		BtcClienCsv.readFile();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	
}
