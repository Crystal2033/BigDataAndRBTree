#pragma once
#include "Generator.h"
#include "Container.h"
#include <chrono>
template <typename TKey, typename TData>
class DeliveryManager {
private:
	Container<TKey, TData>* collection;
	InterfaceGenerator* generator;

public:
	void generateData(const int user_choice);
	DeliveryManager(Container<TKey, TData>* col, InterfaceGenerator* gen)
	{
		collection = col;
		generator = gen;
	}
	//DeliveryManager() = default;

};


//template <typename TKey, typename TData>
void DeliveryManager<std::pair<std::string*, unsigned int>, Delivery*>::generateData(const int cmp_choice)
{
	std::list<Delivery*>* deliveries;


	auto begin = std::chrono::steady_clock::now();

	for (int i = 0; i < 50; i++)
	{
		deliveries = &generator->generateData();

		for (auto delivery : *deliveries) {

			switch (cmp_choice)
			{
			case 1: //name
			{
				collection->add(std::make_pair(delivery->name, delivery->hash_code), delivery);
				break;
			}
			case 2: //content
			{
				collection->add(std::make_pair(delivery->content, delivery->hash_code), delivery);
				break;
			}
			case 6: //sender
			{
				collection->add(std::make_pair(delivery->sender, delivery->hash_code), delivery);
				break;
			}
			case 7: //departure point
			{
				collection->add(std::make_pair(delivery->departure_comp, delivery->hash_code), delivery);
				break;
			}
			case 8: //reciever
			{
				collection->add(std::make_pair(delivery->reciever, delivery->hash_code), delivery);
				break;
			}
			case 9: //destination point
			{
				collection->add(std::make_pair(delivery->destination_comp, delivery->hash_code), delivery);
				break;
			}
			case 10: //type of transport
			{
				collection->add(std::make_pair(delivery->type_of_transport, delivery->hash_code), delivery);
				break;
			}
			}

		}
		delete deliveries;
	}

	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	std::cout << blue << "The time of generation: " << cyan << elapsed_ms.count() << blue << " ms" << white << std::endl;

}

void DeliveryManager<std::pair<float, unsigned int>, Delivery*>::generateData(const int cmp_choice)
{
	std::list<Delivery*>* deliveries;


	auto begin = std::chrono::steady_clock::now();

	for (int i = 0; i < 50; i++)
	{
		deliveries = &generator->generateData();

		for (auto delivery : *deliveries) {

			switch (cmp_choice)
			{
			case 3: //weight
			{
				collection->add(std::make_pair(delivery->weight, delivery->hash_code), delivery);
				break;
			}
			case 4: //price
			{
				collection->add(std::make_pair(delivery->price, delivery->hash_code), delivery);
				break;
			}
			case 5: //delivery price
			{
				collection->add(std::make_pair(delivery->deliver_price, delivery->hash_code), delivery);
				break;
			}
			}

		}
		delete deliveries;
	}

	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	std::cout << blue << "The time of generation: " << cyan << elapsed_ms.count() << blue << " ms" << white << std::endl;
}