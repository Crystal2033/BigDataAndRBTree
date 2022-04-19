#pragma once
#include "Container.h"
#include "Queue.h"
#include <queue>
template <typename TKey, typename TData>
class Queue : public Container<TKey, TData> 
{
	//“ут нужно учитывать, что TData и TKey в очереди ќЅя«јЌџ совпадать.
	// ѕотому что ключом и €вл€ютс€ сами данные.
private:
	std::queue<TKey>* queue;

public:
	Queue();
	void add(const TKey&, const TData&) override;
	void remove(const TKey&) override;
	std::list<TData*> find(const TKey&) override;
	~Queue() = default;
};

template <typename TKey, typename TData>
Queue<TKey, TData>::Queue() {
	queue = new std::queue<TKey>;
}

template <typename TKey, typename TData>
void Queue<TKey, TData>::add(const TKey& data_key, const TData& not_used)
{
	queue->push(data_key);
}

template <typename TKey, typename TData>
void Queue<TKey, TData>::remove(const TKey& data_key){
	std::queue<TKey>* new_queue = new std::queue<TKey>;
	std::list<TData*> found_data_list;
	TKey check_data_ptr;

	while (!queue->empty()){
		check_data_ptr = queue->front();
		queue->pop();

		if (check_data_ptr == data_key){
			continue;
		}
		new_queue->push(check_data_ptr);	
	}

	delete queue;
	queue = new_queue;
}

template <typename TKey, typename TData>
std::list<TData*> Queue<TKey, TData>::find(const TKey& data_key) //TData == TKey
{
	std::queue<TKey> *new_queue = new std::queue<TKey>;
	std::list<TData*> found_data_list;
	TKey* check_data_ptr;
	while (!queue->empty())
	{
		check_data_ptr = &(queue->front());
		new_queue->push(*check_data_ptr);
		if (new_queue->back() == data_key)
		{
			found_data_list.push_back(&(new_queue->back()));
		}
		queue->pop();
	}
	delete queue;
	queue = new_queue;

	return found_data_list;
}