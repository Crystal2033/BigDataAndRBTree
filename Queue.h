#pragma once
#include "Container.h"
#include "Comparator.h"
#include <queue>
template <typename TKey, typename TData>
class Queue : public Container<TKey, TData> 
{

private:
	std::queue<std::pair<TKey, TData>>* queue;
	Comparator<TKey>* comparator;
	void printByBegin(void(*call_back)(const TKey&, const TData&, int)); //const;
	void nullFirstPairField(std::pair<std::string*, unsigned int>& key);
	void nullFirstPairField(std::pair<float, unsigned int>& key);
	void deleteHook(TKey key, std::list<std::pair<TKey, TData>>& list);
public:
	Queue(Comparator<TKey>*);
	void add(const TKey&, const TData&) override;
	void remove(const TKey&) override;
	std::list<TData>* find(const TKey&) override;
	void stepover(void(*call_back)(const TKey&, const TData&, int)) override; //const override;
	~Queue() = default;
};


#pragma region Constructor
template <typename TKey, typename TData>
Queue<TKey, TData>::Queue(Comparator<TKey>* cmp) {
	comparator = cmp;
	queue = new std::queue<std::pair<TKey, TData>>;
}
#pragma endregion


#pragma region ADD
template <typename TKey, typename TData>
void Queue<TKey, TData>::add(const TKey& key_pair, const TData& data)
{
	queue->push(std::make_pair(key_pair, data)); //pair: < <key, hash>, data >
}
#pragma endregion


#pragma region REMOVE
template <typename TKey, typename TData>
void Queue<TKey, TData>::remove(const TKey& key_pair){
	std::queue<std::pair<TKey, TData>>* new_queue = new std::queue<std::pair<TKey, TData>>;
	std::list<std::pair<TKey, TData>> found_data_list;
	std::pair<TKey, TData> check_data_ptr;
	//nullFirstPairField(key_pair);
	int compare_res;
	while (!queue->empty()){
		check_data_ptr = queue->front();
		queue->pop();
		compare_res = comparator->compare(check_data_ptr.first, key_pair);
		if (compare_res == 0){
			found_data_list.push_back(check_data_ptr);
			continue;
		}
		new_queue->push(check_data_ptr);	
	}
	deleteHook(key_pair, found_data_list);
	for (auto iter = found_data_list.begin(); iter != found_data_list.end(); iter++)
	{
		new_queue->push(*iter);
	}
	delete queue;
	queue = new_queue;
}

template<typename TKey, typename TData>
inline void Queue<TKey, TData>::nullFirstPairField(std::pair<std::string*, unsigned int>& key)
{
	key.first = nullptr;
}

template<typename TKey, typename TData>
inline void Queue<TKey, TData>::nullFirstPairField(std::pair<float, unsigned int>& key)
{
	key.first = -1;
}
template<typename TKey, typename TData>
void Queue<TKey, TData>::deleteHook(TKey key, std::list<std::pair<TKey, TData>>& list)
{
	nullFirstPairField(key);
	for (auto iter = list.begin(); iter != list.end(); iter++)
	{
		if (comparator->compare(key, iter->first) == 0)
		{
			list.erase(iter);
			delete iter->second;
		}
	}

}
#pragma endregion


#pragma region FIND
template <typename TKey, typename TData>
std::list<TData>* Queue<TKey, TData>::find(const TKey& key_pair)
{
	std::queue<std::pair<TKey, TData>>* new_queue = new std::queue<std::pair<TKey, TData>>;
	std::list<TData>* found_data_list = new std::list<TData>;
	std::pair<TKey, TData> check_data_ptr;
	//TKey* check_data_ptr;
	int compare_result;
	while (!queue->empty())
	{
		check_data_ptr = queue->front();
		new_queue->push(check_data_ptr);
		compare_result = comparator->compare(new_queue->back().first, key_pair);
		if (compare_result == 0)
		{
			found_data_list->push_back(new_queue->back().second);
		}
		queue->pop();
	}
	delete queue;
	queue = new_queue;

	return found_data_list;
}

#pragma endregion

#pragma region ASSIST METHODS
template <typename TKey, typename TData>
void Queue<TKey, TData>::printByBegin(void(*call_back)(const TKey&, const TData&, int)) //const
{
	/*std::queue<TKey>* new_queue = new std::queue<TKey>;
	TKey* check_data_ptr;
	while (!queue->empty())
	{
		check_data_ptr = &(queue->back());
		call_back(check_data_ptr);
		new_queue->push(*check_data_ptr);
		queue->pop();
	}

	delete queue;
	queue = new_queue;*/
}



template <typename TKey, typename TData>
void Queue<TKey, TData>::stepover(void(*call_back)(const TKey&, const TData&, int)) //const
{
	//printByBegin(call_back);
}
#pragma endregion

