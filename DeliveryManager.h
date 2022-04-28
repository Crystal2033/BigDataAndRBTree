#pragma once
#include "Generator.h"
#include "Container.h"
#include <chrono>
template <typename TKey, typename TData>
class DeliveryManager {
private:
	Container<TKey, TData>* collection;
	InterfaceGenerator* generator;
	std::string choice_str;
	void set_choice_str(const int choice_num);

public:
	void generateData(const int user_choice);
	const std::string& getStringChoice() const { return choice_str; };

	void addData();
	std::list<TData*> findData();
	void removeData();
	Delivery* createUserDelivery() const;
	
	DeliveryManager(Container<TKey, TData>* col, InterfaceGenerator* gen)
	{
		collection = col;
		generator = gen;
	}

	void PrintData(void (*callback)(const TKey&,const TData&, int));
	//DeliveryManager() = default;

};

#pragma region PrintData
template <typename TKey, typename TData>
void DeliveryManager<TKey, TData>::PrintData(void (*callback)(const TKey&, const TData&, int))
{
	collection->stepover(callback);
}
#pragma endregion


#pragma region Generation
template <typename TKey, typename TData>
void DeliveryManager<TKey, TData>::set_choice_str(const int choice_num)
{
	switch (choice_num)
	{
		case 1:
		{
			choice_str = "Name";
			break;
		}
		case 2:
		{
			choice_str = "Content";
			break;
		}
		case 3:
		{
			choice_str = "Weight";
			break;
		}
		case 4:
		{
			choice_str = "Price";
			break;
		}
		case 5:
		{
			choice_str = "Delivery price";
			break;
		}
		case 6:
		{
			choice_str = "Sender (from country)";
			break;
		}
		case 7:
		{
			choice_str = "Departure point (by company)";
			break;
		}
		case 8:
		{
			choice_str = "Reciever (to country)";
			break;
		}
		case 9:
		{
			choice_str = "Destination point (for company)";
			break;
		}
		case 10:
		{
			choice_str = "Type of transport";
			break;
		}
		//TODO: TIME 11( SEND ), 12 ( RECIEVE )
		
	}
}

//Specialization
void DeliveryManager<std::pair<std::string*, unsigned int>, Delivery*>::generateData(const int cmp_choice)
{
	std::list<Delivery*>* deliveries;

	set_choice_str(cmp_choice);
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
	std::cout << azure << "Generated value: " << cyan << generator->get_generated_value() << white << std::endl;
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	std::cout << blue << "The time of generation: " << cyan << elapsed_ms.count() << blue << " ms" << white << std::endl;

}


//Specialization
void DeliveryManager<std::pair<float, unsigned int>, Delivery*>::generateData(const int cmp_choice)
{
	std::list<Delivery*>* deliveries;

	set_choice_str(cmp_choice);
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
	std::cout << azure << "Generated value: " << cyan << generator->get_generated_value() << white << std::endl;
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	std::cout << blue << "The time of generation: " << cyan << elapsed_ms.count() << blue << " ms" << white << std::endl;
}
#pragma endregion


#pragma region AddRequest
template <typename TKey, typename TData>
void DeliveryManager<TKey, TData>::addData()
{

}
#pragma endregion

#pragma region FindRequest
template <typename TKey, typename TData>
std::list<TData*> DeliveryManager<TKey, TData>::findData() {
	std::list<TData*> foundData;

	return foundData;
}
#pragma endregion

#pragma region RemoveRequest
template <typename TKey, typename TData>
void DeliveryManager<TKey, TData>::removeData()
{

}
#pragma endregion

