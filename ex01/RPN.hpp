/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 16:03:20 by ldesboui          #+#    #+#             */
/*   Updated: 2026/05/12 16:50:03 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#pragma once
#include <stack>
#include <iostream>
#include <string>

class RPN
{
	private:
		std::stack<int> theStack;
	public:
		RPN();
		~RPN();
		RPN(const RPN&  aRPN);
		RPN& operator=(const RPN&  aRPN);
		
		std::stack<int> getStack();
		void			proceedRPN(std::string str);
		class TheException : public std::exception
		{
			private:
				std::string message;
			public:
				~TheException() throw();
				TheException(std::string message);
				const char *what() const throw(); 
		};
};
