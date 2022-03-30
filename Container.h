#pragma once
template <typename TKey, typename TData>
class Container
{
public:
	virtual void add(const TKey&, const TData&) = 0;
	virtual void remove(const TKey&) = 0;
	virtual TData& find(const TKey&) const = 0; 
	virtual ~Container() = default;
};