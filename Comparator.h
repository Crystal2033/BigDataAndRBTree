#pragma once
#include <iostream>
typedef enum {INCREASE, DECREASE} COMP_STATUS;
template <typename TKey>
class Comparator
{

public:
	virtual int compare(const TKey& left, const TKey& right) const = 0;
	virtual ~Comparator() = default;
};


#pragma region Int Compare
class ComparatorInt final : public Comparator<int>
{
private:
	COMP_STATUS compare_status;
public:
	ComparatorInt(COMP_STATUS);
	int compare(const int& left, const int& right) const override;
};


int ComparatorInt::compare(const int& left, const int& right) const
{
		if (left > right)
		{
			return (compare_status== INCREASE)? 1: -1;
		}
		else if (left == right)
		{
			return 0;
		}
		else return (compare_status == DECREASE) ? 1 : -1;

}

ComparatorInt::ComparatorInt(COMP_STATUS status)
{
	compare_status = status;
}

#pragma endregion


#pragma region Str Compare
class ComparatorStr final : public Comparator<std::string>
{
private:
	COMP_STATUS compare_status;
public:
	ComparatorStr(COMP_STATUS);
	int compare(const std::string& left, const std::string& right) const override; // по длине строки.
};

ComparatorStr::ComparatorStr(COMP_STATUS status)
{
	compare_status = status;
}

int ComparatorStr::compare(const std::string& left, const std::string& right) const
{

		if (left.length() > right.length())
		{
			return (compare_status == INCREASE) ? 1 : -1;
		}
		else if (left.length() == right.length())
		{
			return 0;
		}
		else return (compare_status == DECREASE) ? 1 : -1;

}
#pragma endregion