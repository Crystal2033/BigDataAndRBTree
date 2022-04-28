#pragma once
#include "Generator.h"
#include "Container.h"
#include <chrono>
#include <string>

template <typename TKey, typename TData>
class DeliveryManager {
private:
	Container<TKey, TData>* collection;
	InterfaceGenerator<Delivery>* generator;
	std::string choice_str;
	void set_choice_str(const int choice_num);
	std::string* getStringInput(DELITYPES type, const std::string& request_str);
	std::string* addToDataPool(DELITYPES type, const std::string& str);

	float getFloatInput(DELITYPES type, const std::string& request_str);


	public:
	void generateData(const int user_choice);
	const std::string& getStringChoice() const { return choice_str; };

	void addData();
	std::list<Delivery*> findData();
	void removeData();
	Delivery* createUserDelivery() ;
	
	DeliveryManager(Container<TKey, TData>* col, InterfaceGenerator<Delivery>* gen)
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

template<typename TKey, typename TData>
std::string* DeliveryManager<TKey, TData>::getStringInput(DELITYPES type, const std::string& request_str) 
{
	std::string input_data;
	std::string* dataField;

	input_data.clear();
	std::cout << blue << "Please, input data in " << yellow << request_str << blue << " field:" << white << std::endl << "> ";
	std::cin >> input_data;
	dataField = addToDataPool(type, input_data);
	if (dataField == nullptr)
	{
		throw NullException("There is an error with nullptr, which shouldn`t be.");
	}
	return dataField;
}

template<typename TKey, typename TData>
std::string* DeliveryManager<TKey, TData>::addToDataPool(DELITYPES type, const std::string& str)
{
	std::vector<std::string>* data_vector;
	data_vector = &generator->getDataVector(type);
	for (auto iter = data_vector->begin(); iter != data_vector->end(); iter++)
	{
		if (*iter == str)
		{
			return &(*iter);
		}
	}

	data_vector->push_back(str);
	return &data_vector->back();
}

template<typename TKey, typename TData>
float DeliveryManager<TKey, TData>::getFloatInput(DELITYPES type, const std::string& request_str)
{
	std::string number_str = "";
	float number = 0.0;
	char curr_char;
	int dot_counter = 0;
	bool number_err = false;
	while (true)
	{
		dot_counter = 0;
		number_err = false;
		number_str.clear();
		std::cout << blue << "Please, input data in " << yellow << request_str << blue << " field: (example: 123.45)" << white << std::endl << "> ";
		std::cin >> number_str;
		for (int i = 0; i < number_str.size(); i++)
		{

			curr_char = number_str[i];
			if (isdigit(curr_char) || curr_char == '.')
			{
				if (curr_char == '.')
				{
					dot_counter++;
				}
			}
			else
			{
				number_err = true;
				break;
			}
		}
		if (dot_counter > 1 || number_err)
		{
			std::cout << red << "You have to input float number (example 123.45). Please try again." << white << std::endl;
			continue;
		}
		try
		{
			number = std::stof(number_str.c_str());
		}
		catch (std::invalid_argument)
		{
			std::cout << red << "You have to input float number (example 123.45). Please try again." << white << std::endl;
			continue;
		}
		catch (std::out_of_range)
		{
			std::cout << red << "You have to input not big float number (example 123.45). Please try again." << white << std::endl;
			continue;
		}
		break;

	}
	return number;
}

template <typename TKey, typename TData>
Delivery* DeliveryManager<TKey, TData>::createUserDelivery()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	DeliGenerator* delivery_gen = reinterpret_cast<DeliGenerator*>(generator);
	Delivery* delivery = new Delivery;
	delivery->name = getStringInput(NAME, "name");
	delivery->content = getStringInput(CONTENT, "content");
	delivery->weight = getFloatInput(WEIGHT, "weight");
	delivery->price = getFloatInput(PRICE, "price");
	delivery->sender = getStringInput(SENDER, "sender (from country)");
	delivery->departure_comp = getStringInput(DEPART, "departure point (by company)");
	delivery->reciever = getStringInput(RECIEVER, "reciever (to country)");
	delivery->destination_comp = getStringInput(DESTINATION, "destination (for company)");
	delivery->type_of_transport = getStringInput(TRANSPORT, "type of transport");

	delivery->deliver_price = delivery_gen->get_delivery_price(*delivery);
	generator->generateHash(*delivery, gen);
	return delivery;
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
	std::cout << azure << "Generated value: " << cyan << generator->getGeneratedCount() << white << std::endl;
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
	std::cout << azure << "Generated value: " << cyan << generator->getGeneratedCount() << white << std::endl;
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	std::cout << blue << "The time of generation: " << cyan << elapsed_ms.count() << blue << " ms" << white << std::endl;
}
#pragma endregion


#pragma region AddRequest
template <typename TKey, typename TData>
void DeliveryManager<TKey, TData>::addData()
{
	Delivery* createdDeliv = createUserDelivery();
	std::cout << std::endl << green << "Added new delivery:" << std::endl;
	std::cout << *createdDeliv << std::endl;
}
#pragma endregion

#pragma region FindRequest

std::list<Delivery*> DeliveryManager<std::pair<float, unsigned int>, Delivery*>::findData() {
	std::list<Delivery*> foundData;
	std::cout << "FLOAT" << std::endl;
	return foundData;
}

std::list<Delivery*> DeliveryManager<std::pair<std::string*, unsigned int>, Delivery*>::findData() {
	std::list<Delivery*> foundData;
	std::cout << "STRING" << std::endl;
	return foundData;
}
#pragma endregion

#pragma region RemoveRequest

void DeliveryManager<std::pair<float, unsigned int>, Delivery*>::removeData()
{

}


void DeliveryManager<std::pair<std::string*, unsigned int>, Delivery*>::removeData()
{

}
#pragma endregion

