#include <iostream>
#include <string>
#include <vector>

double string_to_number(std::string str)
{
	double num{};
	bool past_decimal = false;
	double decimal_place = 0.1;
	for (char c : str)
	{
		if (isdigit(c))
			if (!past_decimal)
				num = num * 10 + (c - '0');
			else
			{
				num += (c - '0') * decimal_place;
				decimal_place *= 0.1;
			}
		else if (c == '.')
			past_decimal = true;
		else
			break;
	}
	return num;
}

std::vector<char> get_opVector(std::string user_equation)
{
	std::vector<char> operands;
	for (char c : user_equation)
	{
		if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')')
			operands.push_back(c);
		else
			continue;
	}
	return operands;
}

std::vector<double> get_numVector(std::string user_equation)
{
	std::vector<double> numbers;
	std::string takeout_num{};
	for (char c : user_equation)
	{
		if (isdigit(c) || c == '.')
			takeout_num.push_back(c);
		else
		{
			if (!takeout_num.empty())
			{
				numbers.push_back(string_to_number(takeout_num));
				takeout_num.clear();
			}
			else
				continue;
		}
	}
	// handle trailing numbers in 'user_equation'
	if (!takeout_num.empty())
	{
		numbers.push_back(string_to_number(takeout_num));
	}

	return numbers;
}

double getResult(std::string user_equation)
{
	std::vector<double> numVector = get_numVector(user_equation);
	std::vector<char> opVector = get_opVector(user_equation);
	double num{numVector[0]};
	double next_num{};
	bool parentheses = false;
	int next_op{};

	for (int i = 1; i < size(numVector); ++i)
	{
		next_num = numVector[i];
		switch (opVector[next_op])
		{
			case '+': num += next_num; break;
			case '-': num -= next_num; break;
			case '*': num *= next_num; break;
			case '/': num /= next_num; break;
			case '(':
			{
				parentheses = true;
			}
			; break;
			case ')':
			{
				parentheses = false;
			}
			default:;
		}
		next_op = i;
	}
	
	return num;
}

int main()
{
	/*std::cout << "Enter equation for assessment: ";
	std::string user_equation;
	std::getline(std::cin, user_equation,'\n');*/
	
	std::string user_equation = "1 + 2 + 2 / 5 * 12.5";
	std::cout << "Result: " << getResult(user_equation);

	return 0;
}
