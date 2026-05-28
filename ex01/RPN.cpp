/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesboui <ldesboui@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 16:10:06 by ldesboui          #+#    #+#             */
/*   Updated: 2026/05/28 18:48:48 by ldesboui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(){}

RPN::~RPN(){}

RPN::RPN(const RPN&  aRPN)
{
	this->theStack = aRPN.theStack;
}

RPN& RPN::operator=(const RPN&  aRPN)
{
	if (this == &aRPN)
		return *this;
	this->theStack = aRPN.theStack;
	return *this;
}

std::stack<unsigned int> RPN::getStack()
{
	return (this->theStack);
}

void RPN::proceedRPN(std::string str)
{
	int	i = 0;
	for (std::string::iterator it = str.begin(); it != str.end(); ++it)
	{
		if (i % 2 == 1)
		{
			if (*it != ' ')
				throw RPN::TheException("Error");
		}
		else
		{
			if (std::isdigit(*it))
				this->theStack.push(*it - '0');
			else if (theStack.size() >= 2)
			{
				unsigned int	rightValue = theStack.top();
				theStack.pop();
				unsigned int	leftValue = theStack.top();
				theStack.pop();
				if (*it == '+')
				{
					if (rightValue + leftValue > INT_MAX)
						throw RPN::TheException("Error");
					theStack.push(rightValue + leftValue);
				}
				else if (*it == '-')
				{
					if (static_cast<long long>(leftValue) -  static_cast<long long>(rightValue)< 0)
						theStack.push(0);
					else
						theStack.push(leftValue - rightValue);
				}
				else if (*it == '*')
				{
					if (rightValue * leftValue > INT_MAX)
						throw RPN::TheException("Error");
					theStack.push(rightValue * leftValue);
				}
				else if (*it == '/')
				{
					if (rightValue == 0)
						throw RPN::TheException("Error");
					theStack.push(leftValue / rightValue);
				}
				else
					throw RPN::TheException("Error");
			}
			else
				throw RPN::TheException("Error");
		}
		++i;
	}
}

RPN::TheException::~TheException()throw(){}

RPN::TheException::TheException(std::string message) : message(message){}

const char * RPN::TheException::what()const throw() {return this->message.c_str();}
