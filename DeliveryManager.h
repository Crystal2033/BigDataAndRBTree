#pragma once
#include "Generator.h"
#include "Container.h"
#include <chrono>
#include <string>
#include "UserFuncsAndCallbacks.h"
typedef enum RequestType {POST, GET} REQ_TYPE;
template <typename TKey, typename TData>
class DeliveryManager {
private:
	Container<TKey, TData>* collection;
	InterfaceGenerator<Delivery>* generator;
	std::string comp_str;
	DELITYPES comp_type;
	void setChoice(const int choice_num);
	std::string* getStringInput(DELITYPES type, const std::string& request_str);
	std::string* addToDataPool(DELITYPES type, const std::string& str);

	float getFloatInput(REQ_TYPE type, const std::string& request_str);
	void addDeliveryInCollection(Delivery*& delivery);

	public:
	void generateData(const int user_choice);
	const std::string& getStringChoice() const { return comp_str; };
	int workWithUser(int choice_user);
	void addData();
	std::list<Delivery*>* findData();
	void removeData();
	Delivery* createUserDelivery(std::string* const& sender_chain=nullptr) ;
	
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
void DeliveryManager<TKey, TData>::setChoice(const int choice_num)
{
	switch (choice_num)
	{
		case 1:
		{
			comp_str = "Name";
			comp_type = NAME;
			break;
		}
		case 2:
		{
			comp_str = "Content";
			comp_type = CONTENT;
			break;
		}
		case 3:
		{
			comp_str = "Weight";
			comp_type = WEIGHT;
			break;
		}
		case 4:
		{
			comp_str = "Price";
			comp_type = PRICE;
			break;
		}
		case 5:
		{
			comp_type = DELI_PRICE;
			comp_str = "Delivery price";
			break;
		}
		case 6:
		{
			comp_type = SENDER;
			comp_str = "Sender (from country)";
			break;
		}
		case 7:
		{
			comp_type = DEPART;
			comp_str = "Departure point (by company)";
			break;
		}
		case 8:
		{
			comp_type = RECIEVER;
			comp_str = "Reciever (to country)";
			break;
		}
		case 9:
		{
			comp_type = DESTINATION;
			comp_str = "Destination point (for company)";
			break;
		}
		case 10:
		{
			comp_type = TRANSPORT;
			comp_str = "Type of transport";
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
	std::cin.clear();
	std::getline(std::cin, input_data);
	std::cin.clear();
	dataField = addToDataPool(type, input_data);
	if (dataField == nullptr)
	{
		throw NullException("There is an error with nullptr, which shouldn`t be.");
	}
	return dataField;
}

template<typename TKey, typename TData>
float DeliveryManager<TKey, TData>::getFloatInput(REQ_TYPE req_type, const std::string& request_str)
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
		if (req_type == POST)
		{
			std::cout << blue << "Please, input data in " << yellow << request_str << blue << " field: (example: 123.45)" << white << std::endl << "> ";
		}
		else if (req_type == GET)
		{
			std::cout << blue << "Please, input data which you want to find, comparator is a " << yellow << request_str << blue << " field: (example: 123.45)" << white << std::endl << "> ";
		}
		std::cin.clear();
		std::getline(std::cin, number_str);
		std::cin.clear();
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

template<typename TKey, typename TData>
std::string* DeliveryManager<TKey, TData>::addToDataPool(DELITYPES type, const std::string& str)
{
	std::list<std::string>* data_list;
	data_list = generator->getPoolCollection(type);
	for (auto iter = data_list->begin(); iter != data_list->end(); iter++)
	{
		if (*iter == str)
		{
			return &(*iter);
		}
	}

	data_list->push_back(str);
	return &data_list->back();
}




void DeliveryManager<std::pair<std::string*, unsigned int>, Delivery*>::addDeliveryInCollection(Delivery*& delivery)
{
	switch (comp_type)
	{
		case NAME: //name
		{
			collection->add(std::make_pair(delivery->name, delivery->hash_code), delivery);
			break;
		}
		case CONTENT: //content
		{
			collection->add(std::make_pair(delivery->content, delivery->hash_code), delivery);
			break;
		}
		case SENDER: //sender
		{
			collection->add(std::make_pair(delivery->sender, delivery->hash_code), delivery);
			break;
		}
		case DEPART: //departure point
		{
			collection->add(std::make_pair(delivery->departure_comp, delivery->hash_code), delivery);
			break;
		}
		case RECIEVER: //reciever
		{
			collection->add(std::make_pair(delivery->reciever, delivery->hash_code), delivery);
			break;
		}
		case DESTINATION: //destination point
		{
			collection->add(std::make_pair(delivery->destination_comp, delivery->hash_code), delivery);
			break;
		}
		case TRANSPORT: //type of transport
		{
			collection->add(std::make_pair(delivery->type_of_transport, delivery->hash_code), delivery);
			break;
		}
	}
}

void DeliveryManager<std::pair<float, unsigned int>, Delivery*>::addDeliveryInCollection(Delivery*& delivery)
{
	switch (comp_type)
	{
		case WEIGHT: //weight
		{
			collection->add(std::make_pair(delivery->weight, delivery->hash_code), delivery);
			break;
		}
		case PRICE: //price
		{
			collection->add(std::make_pair(delivery->price, delivery->hash_code), delivery);
			break;
		}
		case DELI_PRICE: //delivery price
		{
			collection->add(std::make_pair(delivery->deliver_price, delivery->hash_code), delivery);
			break;
		}
	}
}

template <typename TKey, typename TData>
Delivery* DeliveryManager<TKey, TData>::createUserDelivery(std::string* const& last_reciever)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	
	Delivery* delivery = new Delivery;
	delivery->name = getStringInput(NAME, "name");
	delivery->content = getStringInput(CONTENT, "content");
	delivery->weight = getFloatInput(POST, "weight");
	delivery->price = getFloatInput(POST, "price");
	if (last_reciever == nullptr)
	{
		delivery->sender = getStringInput(SENDER, "sender (from country)");
	}
	else
	{
		delivery->sender = last_reciever;
	}
	delivery->departure_comp = getStringInput(DEPART, "departure point (by company)");
	delivery->reciever = getStringInput(RECIEVER, "reciever (to country)");
	delivery->destination_comp = getStringInput(DESTINATION, "destination (for company)");
	delivery->type_of_transport = getStringInput(TRANSPORT, "type of transport");

	DeliGenerator* delivery_gen = reinterpret_cast<DeliGenerator*>(generator);
	delivery->deliver_price = delivery_gen->get_delivery_price(*delivery);
	generator->generateHash(*delivery, gen);
	return delivery;
}
//Specialization
//void DeliveryManager<std::pair<std::string*, unsigned int>, Delivery*>::generateData(const int cmp_choice)
//{
//	std::list<Delivery*>* deliveries;
//
//	setChoice(cmp_choice);
//	auto begin = std::chrono::steady_clock::now();
//
//	for (int i = 0; i < 100; i++)
//	{
//		deliveries = &generator->generateData();
//
//		for (auto delivery : *deliveries) {
//
//			addDeliveryInCollection(delivery);
//		}
//		delete deliveries;
//	}
//
//	auto end = std::chrono::steady_clock::now();
//	std::cout << azure << "Generated value: " << cyan << generator->getGeneratedCount() << white << std::endl;
//	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
//	std::cout << blue << "The time of generation: " << cyan << elapsed_ms.count() << blue << " ms" << white << std::endl;
//
//}


//Specialization
template <typename TKey, typename TData>
void DeliveryManager<TKey, TData>::generateData(const int cmp_choice)
{
	std::list<Delivery*>* deliveries;

	setChoice(cmp_choice);
	auto begin = std::chrono::steady_clock::now();

	for (int i = 0; i < 100; i++)
	{
		deliveries = &generator->generateData();

		for (auto delivery : *deliveries)
		{
			addDeliveryInCollection(delivery);
		}
		delete deliveries;
	}
	
	auto end = std::chrono::steady_clock::now();
	std::cout << azure << "Generated value: " << cyan << generator->getGeneratedCount() << white << std::endl;
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	std::cout << blue << "The time of generation: " << cyan << elapsed_ms.count() << blue << " ms" << white << std::endl;
}
#pragma endregion

#pragma region Work with user
template<typename TKey, typename TData>
int DeliveryManager<TKey, TData>::workWithUser(int choice_number)
{
	std::cout << cyan << "To start " << blue << "generating " << cyan << "data press any keyboard button." << white << std::endl;
	getchar();
	//getchar();
	generateData(choice_number);
	//manager.PrintData(print_tree_for_deliv_pair_float);
	while (true)
	{
		chooseOperationPrint();
		choice_number = userChoice(1, 4);
		if (choice_number == 1) //ADD
		{
			addData();
		}
		else if (choice_number == 2) //FIND
		{
			std::cout << "find" << std::endl;

			std::list<Delivery*>* found_data = findData();
			if (found_data->size() == 0)
			{
				std::cout << red << "Not found information by your search request." << white << std::endl;
			}
			else
			{
				std::cout << cyan << "Was found: " << green << found_data->size() << cyan << " deliveries." << white << std::endl;
				for (auto it = found_data->begin(); it != found_data->end(); it++)
				{
					std::cout << **it << std::endl;
				}
				while (true)
				{
					int choice_number;
					std::cout << cyan << "Choose field to change data:" << white << std::endl;
					chooseFieldPrint();
					choice_number = userChoice(1, 10);
					if (found_data->size() == 1)
					{

					}
					else //find by HASH
					{

					}


				}

			}
			delete found_data;

		}
		else if (choice_number == 3) //DELETE
		{
			std::cout << "delete" << std::endl;
			removeData();
		}
		else if (choice_number == 4) //exit
		{
			return 0;
		}

	}
}
#pragma endregion

#pragma region AddRequest

template<typename TKey, typename TData>
void DeliveryManager<TKey, TData>::addData()
{
	std::cout << cyan << "Choose one of" << green << " add " << cyan << "operation:" << white << std::endl;
	std::cout << blue << "1. Add independent (no chained) delivery." << std::endl << "2. Add chain of deliveries." << white << std::endl;
	int user_number = userChoice(1, 2);
	int value_of_deliveries = 0;
	std::list<Delivery*> created_deliveries;
	if (user_number == 1)
	{
		value_of_deliveries = 1;
	}
	else
	{
		std::cout << cyan << "You have to set the length of your delivery`s chain." << white << std::endl;
		value_of_deliveries = userChoice(2);
	}

	created_deliveries.push_back(createUserDelivery());
	addDeliveryInCollection(created_deliveries.back());
	std::cout << std::endl << green << "Added new delivery:" << std::endl;
	std::cout << std::endl << green << "Added " << yellow << 1 << green << "/" << value_of_deliveries << white << std::endl;
	for (int i = 1; i < value_of_deliveries; i++)
	{
		created_deliveries.push_back(createUserDelivery(created_deliveries.back()->reciever));
		addDeliveryInCollection(created_deliveries.back());
		std::cout << std::endl << green << "Added new delivery:" << std::endl;
		std::cout << *created_deliveries.back() << std::endl;
		std::cout << std::endl << green << "Added " << yellow << i + 1 << green << "/" << value_of_deliveries << white << std::endl;
	}
	
}
#pragma endregion

#pragma region FindRequest

std::list<Delivery*>* DeliveryManager<std::pair<float, unsigned int>, Delivery*>::findData() {
	std::list<Delivery*>* foundData;
	std::cout << blue << "You can search only by comparator type: " << yellow << comp_str << white << std::endl;
	float search_param = getFloatInput(GET, comp_str);
	foundData = collection->find(std::make_pair(search_param, 0));
	return foundData;
}

std::list<Delivery*>* DeliveryManager<std::pair<std::string*, unsigned int>, Delivery*>::findData() {
	std::list<Delivery*>* foundData;
	std::cout << blue << "You can search only by comparator type: " << yellow << comp_str << white << std::endl << "> ";
	std::string find_request = "";
	std::cin.clear();
	std::getline(std::cin, find_request);
	std::cin.clear();
	foundData = collection->find(std::make_pair(&find_request, 0));
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

