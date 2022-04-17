#pragma once
#include <list>
#include <iostream>
template <typename TKey, typename TData>
class Container
{
public:
	virtual void add(const TKey&, const TData&) = 0;
	virtual void remove(const TKey&) = 0;
	virtual std::list<TData> find(const TKey&) const = 0;
	virtual ~Container() = default;
};

//template <typename TData>
//std::ostream& operator<<(std::ostream& out, std::list<TData&>& data_list) {
//	for (auto data : data_list) {
//		out << data;
//	}
//	return out;
//}