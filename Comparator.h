#pragma once
#include <iostream>
#include <cctype>
#include "Exceptions.h"
typedef enum {INCREASE, DECREASE} COMP_STATUS;
//typedef enum { KEY, HASH } TYPE;
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

#pragma region Int Compare
//class ComparatorInt final : public Comparator<int>
//{
//private:
//	COMP_STATUS compare_status;
//public:
//	ComparatorInt(COMP_STATUS);
//	int compare(const int& left, const int& right) const override;
//};
//
//
//int ComparatorInt::compare(const int& left, const int& right) const
//{
//		if (left > right)
//		{
//			return (compare_status == INCREASE)? 1: -1;
//		}
//		else if (left == right)
//		{
//			return 0;
//		}
//		else return (compare_status == DECREASE) ? 1 : -1;
//
//}
//
//ComparatorInt::ComparatorInt(COMP_STATUS status)
//{
//	compare_status = status;
//}

#pragma endregion


#pragma region Str Compare
//class ComparatorStr final : public Comparator<std::string>
//{
//private:
//	COMP_STATUS compare_status;
//public:
//	ComparatorStr(COMP_STATUS);
//	int compare(const std::string& left, const std::string& right) const override; // по длине строки.
//};
//
//ComparatorStr::ComparatorStr(COMP_STATUS status)
//{
//	compare_status = status;
//}
//
//int ComparatorStr::compare(const std::string& left, const std::string& right) const
//{
//		/*if (to_lower_str(left) > to_lower_str(right))
//		{
//			return (compare_status == INCREASE) ? 1 : -1;
//		}
//		else if (to_lower_str(left) == to_lower_str(right))
//		{
//			return 0;
//		}
//		else return (compare_status == DECREASE) ? 1 : -1;*/
//
//		if (left > right)
//		{
//			return (compare_status == INCREASE) ? 1 : -1;
//		}
//		else if (left == right)
//		{
//			return 0;
//		}
//		else return (compare_status == DECREASE) ? 1 : -1;
//
//}
#pragma endregion

#pragma region StrPointer comparator
//class ComparatorStrPtr final : public Comparator<std::string*>
//{
//private:
//	COMP_STATUS compare_status;
//public:
//	ComparatorStrPtr(COMP_STATUS);
//	int compare(std::string* const& left, std::string* const& right) const override; // по длине строки.
//};
//
//ComparatorStrPtr::ComparatorStrPtr(COMP_STATUS status)
//{
//	compare_status = status;
//}
//
//int ComparatorStrPtr::compare(std::string* const& left, std::string* const& right) const
//{
//	/*if (to_lower_str(left) > to_lower_str(right))
//	{
//		return (compare_status == INCREASE) ? 1 : -1;
//	}
//	else if (to_lower_str(left) == to_lower_str(right))
//	{
//		return 0;
//	}
//	else return (compare_status == DECREASE) ? 1 : -1;*/
//	if (left == nullptr || right == nullptr)
//	{
//		throw ComparatorNullException("Trying to unpointer nullptr.");
//	}
//
//	if (*left > *right)
//	{
//		return (compare_status == INCREASE) ? 1 : -1;
//	}
//	else if (*left == *right)
//	{
//		return 0;
//	}
//	else return (compare_status == DECREASE) ? 1 : -1;
//
//}
#pragma endregion

#pragma region float compare
//class ComparatorFloat final : public Comparator<float>
//{
//private:
//	COMP_STATUS compare_status;
//public:
//	ComparatorFloat(COMP_STATUS);
//	int compare(const float& left, const float& right) const override;
//};
//
//ComparatorFloat::ComparatorFloat(COMP_STATUS status)
//{
//	compare_status = status;
//}
//
//int ComparatorFloat::compare(const float& left, const float& right) const
//{
//	float epsilone = 0.001;
//	if (left - right > epsilone)
//	{
//		return (compare_status == INCREASE) ? 1 : -1;
//	}
//	else if (fabs(left - right) < epsilone)
//	{
//		return 0;
//	}
//	else if (left - right < 0)
//	{
//		return (compare_status == DECREASE) ? 1 : -1;
//	}
//}
#pragma endregion

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
	/*if (to_lower_str(left) > to_lower_str(right))
	{
		return (compare_status == INCREASE) ? 1 : -1;
	}
	else if (to_lower_str(left) == to_lower_str(right))
	{
		return 0;
	}
	else return (compare_status == DECREASE) ? 1 : -1;*/
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