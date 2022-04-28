#pragma once
#include "Generator.h"
#include "Container.h"
#include <chrono>
#include <string>
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


	public:
	void generateData(const int user_choice);
	const std::string& getStringChoice() const { return comp_str; };

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
			std::cout << blue << "Please, input data which you want to find, comparator is a" << yellow << request_str << blue << " field: (example: 123.45)" << white << std::endl << "> ";
		}
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
	delivery->weight = getFloatInput(POST, "weight");
	delivery->price = getFloatInput(POST, "price");
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

	setChoice(cmp_choice);
	auto begin = std::chrono::steady_clock::now();

	for (int i = 0; i < 1000000; i++)
	{
		deliveries = &generator->generateData();

		for (auto delivery : *deliveries) {

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

	setChoice(cmp_choice);
	auto begin = std::chrono::steady_clock::now();

	for (int i = 0; i < 1000000; i++)
	{
		deliveries = &generator->generateData();

		for (auto delivery : *deliveries) {

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
		delete deliveries;
	}
	
	auto end = std::chrono::steady_clock::now();
	std::cout << azure << "Generated value: " << cyan << generator->getGeneratedCount() << white << std::endl;
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	std::cout << blue << "The time of generation: " << cyan << elapsed_ms.count() << blue << " ms" << white << std::endl;
}
#pragma endregion


#pragma region AddRequest

void DeliveryManager<std::pair<float, unsigned int>, Delivery*>::addData()
{
	Delivery* createdDeliv = createUserDelivery();
	switch (comp_type)
	{
		case WEIGHT: //weight
		{
			collection->add(std::make_pair(createdDeliv->weight, createdDeliv->hash_code), createdDeliv);
			break;
		}
		case PRICE: //price
		{
			collection->add(std::make_pair(createdDeliv->price, createdDeliv->hash_code), createdDeliv);
			break;
		}
		case DELI_PRICE: //delivery price
		{
			collection->add(std::make_pair(createdDeliv->deliver_price, createdDeliv->hash_code), createdDeliv);
			break;
		}
	}
	std::cout << std::endl << green << "Added new delivery:" << std::endl;
	std::cout << *createdDeliv << std::endl;
}


void DeliveryManager<std::pair<std::string*, unsigned int>, Delivery*>::addData()
{
	Delivery* createdDeliv = createUserDelivery();
	switch (comp_type)
	{
		case NAME: //name
		{
			collection->add(std::make_pair(createdDeliv->name, createdDeliv->hash_code), createdDeliv);
			break;
		}
		case CONTENT: //content
		{
			collection->add(std::make_pair(createdDeliv->content, createdDeliv->hash_code), createdDeliv);
			break;
		}
		case SENDER: //sender
		{
			collection->add(std::make_pair(createdDeliv->sender, createdDeliv->hash_code), createdDeliv);
			break;
		}
		case DEPART: //departure point
		{
			collection->add(std::make_pair(createdDeliv->departure_comp, createdDeliv->hash_code), createdDeliv);
			break;
		}
		case RECIEVER: //reciever
		{
			collection->add(std::make_pair(createdDeliv->reciever, createdDeliv->hash_code), createdDeliv);
			break;
		}
		case DESTINATION: //destination point
		{
			collection->add(std::make_pair(createdDeliv->destination_comp, createdDeliv->hash_code), createdDeliv);
			break;
		}
		case TRANSPORT: //type of transport
		{
			collection->add(std::make_pair(createdDeliv->type_of_transport, createdDeliv->hash_code), createdDeliv);
			break;
		}
	}
	std::cout << std::endl << green << "Added new delivery:" << std::endl;
	std::cout << *createdDeliv << std::endl;
}
#pragma endregion

#pragma region FindRequest

std::list<Delivery*> DeliveryManager<std::pair<float, unsigned int>, Delivery*>::findData() {
	std::list<Delivery*> foundData;
	std::cout << blue << "You can search only by comparator type: " << yellow << comp_str << white << std::endl;
	float search_param = getFloatInput(GET, comp_str);
	foundData = collection->find(std::make_pair(search_param, 0));
	return foundData;
}

std::list<Delivery*> DeliveryManager<std::pair<std::string*, unsigned int>, Delivery*>::findData() {
	std::list<Delivery*> foundData;
	std::cout << blue << "You can search only by comparator type: " << yellow << comp_str << white << std::endl << "> ";
	std::string find_request = "";
	std::cin >> find_request;
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

