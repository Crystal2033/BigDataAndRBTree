#pragma once
#include <iostream>
#include <cctype>
#include "Exceptions.h"
typedef enum {INCREASE, DECREASE} COMP_STATUS;

template <typename TKey>
class Comparator
{

public:
	virtual int compare(const TKey& left, const TKey& right) const = 0;
	virtual ~Comparator() = default;
};

std::string to_lower_str(const std::string& str) {
	std::string lower_str;
	for (int i = 0; i < str.size(); i++) {
		lower_str.push_back(tolower(str[i]));
	}
	return lower_str;
}


#pragma region PAIR comparator STR-HASH
class ComparatorPairStr final : public Comparator<std::pair<std::string*, unsigned int>>
{
private:
	COMP_STATUS compare_status;
public:
	ComparatorPairStr(COMP_STATUS);
	int compare(const std::pair<std::string*, unsigned int>& left, const std::pair<std::string*, unsigned int>& right) const override; // по длине строки.
};

ComparatorPairStr::ComparatorPairStr(COMP_STATUS status)
{
	compare_status = status;
}

int ComparatorPairStr::compare(const std::pair<std::string*, unsigned int>& left, const std::pair<std::string*, unsigned int>& right) const
{
	if ((left.first == nullptr || right.first == nullptr) && (left.second == 0 && right.second == 0))
	{
		throw ComparatorNullException("Trying to unpointer nullptr.");
	}

	if ((left.first == nullptr || right.first == nullptr) && left.second != 0 && right.second != 0)
	{// in remove hook case. Where we are set nullptr.
		if (left.second > right.second)
		{
			return (compare_status == INCREASE) ? 1 : -1;
		}
		else if (left.second == right.second)
		{
			return 0;
		}
		else return (compare_status == DECREASE) ? 1 : -1;
	}
	else if ((left.first->size() != 0 && right.first->size() != 0)) //it means comparator by keys.
	{
		if (*left.first > * right.first)
		{
			return (compare_status == INCREASE) ? 1 : -1;
		}
		else if (*left.first == *right.first)
		{
			return 0;
		}
		else return (compare_status == DECREASE) ? 1 : -1;
	}
	else if (left.second != 0 && right.second != 0)  //it means comparator by HASH.
	{
		if (left.second > right.second)
		{
			return (compare_status == INCREASE) ? 1 : -1;
		}
		else if (left.second == right.second)
		{
			return 0;
		}
		else return (compare_status == DECREASE) ? 1 : -1;
	}
	

	std::cout << "Need to check better" << std::endl;
	
}

#pragma endregion

#pragma region PAIR comparator FLOAT-HASH
class ComparatorPairFloat final : public Comparator<std::pair<float, unsigned int>>
{
private:
	COMP_STATUS compare_status;
public:
	ComparatorPairFloat(COMP_STATUS);
	int compare(const std::pair<float, unsigned int>& left, const std::pair<float, unsigned int>& right) const override; // по длине строки.
};

int ComparatorPairFloat::compare(const std::pair<float, unsigned int>& left, const std::pair<float, unsigned int>& right) const
{
	if ((left.first < 0 || right.first < 0 ) && left.second != 0 && right.second != 0)
	{// in remove hook case. Where we are set nullptr.
		if (left.second > right.second)
		{
			return (compare_status == INCREASE) ? 1 : -1;
		}
		else if (left.second == right.second)
		{
			return 0;
		}
		else return (compare_status == DECREASE) ? 1 : -1;
	}
	else if (left.first > 0 && right.second > 0) //it means comparator by keys.
	{
		float epsilone = 0.001;
		if (left.first - right.first > epsilone)
		{
			return (compare_status == INCREASE) ? 1 : -1;
		}
		else if (fabs(left.first - right.first) < epsilone)
		{
			return 0;
		}
		else if (left.first - right.first < 0)
		{
			return (compare_status == DECREASE) ? 1 : -1;
		}
		
	}
	else if (left.second != 0 && right.second != 0)
	{
		if (left.second > right.second)
		{
			return (compare_status == INCREASE) ? 1 : -1;
		}
		else if (left.second == right.second)
		{
			return 0;
		}
		else return (compare_status == DECREASE) ? 1 : -1;
	}
}

ComparatorPairFloat::ComparatorPairFloat(COMP_STATUS status)
{
	compare_status = status;
}
#pragma endregion