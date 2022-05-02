#pragma once
#include <list>
#include <iostream>
template <typename TKey, typename TData>
class Container
{
public:
	virtual void add(const TKey&, const TData&) = 0;
	virtual void remove(const TKey&) = 0;
	virtual std::list<TData>* find(const TKey&) = 0;
	virtual void stepover(void(*call_back)(const TKey&, const TData&, int)) = 0;//const = 0;
	virtual ~Container() = default;
};
