#pragma once
#include "Generator.h"
#include "Container.h"
#include <chrono>
#include <string>
#include "UserFuncsAndCallbacks.h"
#include <regex>

typedef enum RequestType {POST, GET, PATCH} REQ_TYPE;
template <typename TKey, typename TData>
class DeliveryManager {
private:
	Container<TKey, TData>* collection;
	InterfaceGenerator<Delivery>* generator;
	std::string comp_str;
	DELITYPES comp_type;
	DELITYPES setChoiceGetType(const int choice_num, RequestType req_type=POST);
	std::string* getStringInput(DELITYPES type, const std::string& request_str);
	unsigned int getHashInput();
	std::string* addToDataPool(DELITYPES type, const std::string& str);
	bool getTimeStr(std::string& str, std::cmatch& matcher);
	void inputTimeStr(std::string& str);

	float getFloatInput(REQ_TYPE type, const std::string& request_str);
	void addDeliveryInCollection(Delivery*& delivery);
	void addData();
	void getUserData();
	bool wantToChangeData();
	void makeChanging(Delivery*& delivery);
	void changeByField(const DELITYPES type, Delivery*& delivery);
	std::list<Delivery*>* findData();

	void removeData();
	void makeDeleting(Delivery* delivery);
	bool deleteHook(const DELITYPES type, Delivery* const& delivery);
	Delivery* createUserDelivery(std::string* const& sender_chain = nullptr);
	void generateData(const int user_choice);//said
	const std::string& getStringChoice() const { return comp_str; };
	/////////////////////////////////PUBLIC////////////////////////////////////
	public:
	int workWithUser(int choice_user); //said
	
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
DELITYPES DeliveryManager<TKey, TData>::setChoiceGetType(const int choice_num, RequestType req_type)
{
	switch (choice_num)
	{
		case 1:
		{
			if (req_type == POST)
			{
				comp_str = "Name";
				comp_type = NAME;
			}
			return NAME;

		}
		case 2:
		{
			if (req_type == POST)
			{
				comp_str = "Content";
				comp_type = CONTENT;
			}
			return CONTENT;

		}
		case 3:
		{
			if (req_type == POST)
			{
				comp_str = "Weight";
				comp_type = WEIGHT;
			}
			return WEIGHT;

		}
		case 4:
		{
			if (req_type == POST)
			{
				comp_str = "Price";
				comp_type = PRICE;
			}
			return PRICE;

		}
		case 5:
		{
			if (req_type == POST)
			{
				comp_type = DELI_PRICE;
				comp_str = "Delivery price";
			}
			return DELI_PRICE;

		}
		case 6:
		{
			if (req_type == POST)
			{
				comp_type = SENDER;
				comp_str = "Sender (from country)";
			}
			return SENDER;

		}
		case 7:
		{
			if (req_type == POST)
			{
				comp_type = SEND_TIME;
				comp_str = "Sending data";
			}
			return SEND_TIME;

		}
		case 8:
		{
			if (req_type == POST)
			{
				comp_type = DEPART;
				comp_str = "Departure point (by company)";
			}
			return DEPART;

		}
		case 9:
		{
			if (req_type == POST)
			{
				comp_type = RECIEVER;
				comp_str = "Reciever (to country)";
			}
			return RECIEVER;

		}
		case 10:
		{
			if (req_type == POST)
			{
				comp_type = RECI_TIME;
				comp_str = "Recieving data";
			}
			return RECI_TIME;

		}
		case 11:
		{
			if (req_type == POST)
			{
				comp_type = DESTINATION;
				comp_str = "Destination point (for company)";
			}
			return DESTINATION;

		}
		case 12:
		{
			if (req_type == POST)
			{
				comp_type = TRANSPORT;
				comp_str = "Type of transport";
			}
			return TRANSPORT;
		}
	}
}



template<typename TKey, typename TData>
std::string* DeliveryManager<TKey, TData>::getStringInput(DELITYPES type, const std::string& request_str) 
{
	std::string input_data;
	std::string* dataField;

	input_data.clear();
	std::cout << blue << "Please, input data in " << yellow << request_str << blue << " field:" << white << std::endl << "> ";
	if (type == RECI_TIME || type == SEND_TIME)
	{
		inputTimeStr(input_data);
	}
	else
	{
		userInput(input_data);
	}
	dataField = addToDataPool(type, input_data);
	if (dataField == nullptr)
	{
		throw NullException("There is an error with nullptr, which shouldn`t be.");
	}
	return dataField;
}

template<typename TKey, typename TData>
unsigned int DeliveryManager<TKey, TData>::getHashInput()
{
	std::string input_data;
	std::string* dataField;
	unsigned int hash_value;
	while (true)
	{
		std::cout << blue << "You have to choose delivery by " << pink << "hash:" << blue << std::endl << "Input hash value (unsigned int number):" << std::endl << white << "> ";
		input_data.clear();
		userInput(input_data);
		hash_value = strtoul(input_data.c_str(), nullptr, 10);
		if (hash_value == 0)
		{
			std::cout << red << "Transform to unsigned int error. Please, try again." << white << std::endl;
				continue;
		}
		break;
	}

	return hash_value;
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
		if (req_type == POST || req_type == PATCH)
		{
			std::cout << blue << "Please, input data in " << yellow << request_str << blue << " field: (example: 123,456)" << white << std::endl << "> ";
		}
		else if (req_type == GET)
		{
			std::cout << blue << "Please, input data which you want to find, comparator is a " << yellow << request_str << blue << " field: (example: 123,456)" << white << std::endl << "> ";
		}
		userInput(number_str);
		for (int i = 0; i < number_str.size(); i++)
		{

			curr_char = number_str[i];
			if (isdigit(curr_char) || curr_char == ',')
			{
				if (curr_char == ',')
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
			std::cout << red << "You have to input float number (example 123,45). Please try again." << white << std::endl;
			continue;
		}
		try
		{
			number = std::stof(number_str);
		}
		catch (std::invalid_argument)
		{
			std::cout << red << "You have to input float number (example 123,45). Please try again." << white << std::endl;
			continue;
		}
		catch (std::out_of_range)
		{
			std::cout << red << "You have to input not big float number (example 123,45). Please try again." << white << std::endl;
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

template<typename TKey, typename TData>
bool DeliveryManager<TKey, TData>::getTimeStr(std::string& str, std::cmatch& matcher)
{
	int day;
	int month;
	int year;

	if (matcher[1].str().size() != 2)//day
	{
		return false;
	}
	day = std::stoi(matcher[1].str());
	if (day > 31 || day <= 0) // need to correct to other months
	{
		return false;
	}

	if (matcher[2].str().size() != 2)
	{
		return false;
	}
	month = std::stoi(matcher[2].str());
	if (month > 12 || month <= 0)
	{
		return false;
	}

	if (matcher[3].str().size() != 4)//day
	{
		return false;
	}
	year = std::stoi(matcher[3].str());
	if (year <= 0)
	{
		return false;
	}
	str = "";
	str = ((day < 10)? "0" : "") + std::to_string(day) + ':' + ((month < 10) ? "0" : "") + std::to_string(month) + ':' + std::to_string(year);
	return true;
}

template<typename TKey, typename TData>
void DeliveryManager<TKey, TData>::inputTimeStr(std::string& str)
{
	while (true)
	{
		std::regex regular;
		std::cmatch regular_match;
		regular = "([\\d]{2}):([\\d]{2}):([\\d]{4})";
		userInput(str);
		if (!std::regex_match(str.c_str(), regular_match, regular))
		{
			std::cout << red << "Incorrect data. Example: 01:02:2002." << white << std::endl;
			std::cout << blue << "Please, try again:" << std::endl << white << "> ";
			continue;
		}
		if (!getTimeStr(str, regular_match))
		{
			std::cout << red << "Incorrect data. Example: 01:02:2002." << white << std::endl;
			std::cout << blue << "Please, try again:" << std::endl << white << "> ";
			continue;
		}
		break;
	}
}




void DeliveryManager<std::pair<std::string*, unsigned int>, Delivery*>::addDeliveryInCollection(Delivery*& delivery)
{
	switch (comp_type)
	{
		case NAME:
		{
			collection->add(std::make_pair(delivery->name, delivery->hash_code), delivery);
			break;
		}
		case CONTENT:
		{
			collection->add(std::make_pair(delivery->content, delivery->hash_code), delivery);
			break;
		}
		case SENDER:
		{
			collection->add(std::make_pair(delivery->sender, delivery->hash_code), delivery);
			break;
		}
		case DEPART:
		{
			collection->add(std::make_pair(delivery->departure_comp, delivery->hash_code), delivery);
			break;
		}
		case RECIEVER:
		{
			collection->add(std::make_pair(delivery->reciever, delivery->hash_code), delivery);
			break;
		}
		case DESTINATION:
		{
			collection->add(std::make_pair(delivery->destination_comp, delivery->hash_code), delivery);
			break;
		}
		case TRANSPORT:
		{
			collection->add(std::make_pair(delivery->type_of_transport, delivery->hash_code), delivery);
			break;
		}
		case SEND_TIME:
		{
			collection->add(std::make_pair(delivery->send_time, delivery->hash_code), delivery);
			break;
		}
		case RECI_TIME:
		{
			collection->add(std::make_pair(delivery->recieve_time, delivery->hash_code), delivery);
			break;
		}
	}
}


void DeliveryManager<std::pair<float, unsigned int>, Delivery*>::addDeliveryInCollection(Delivery*& delivery)
{
	switch (comp_type)
	{
		case WEIGHT:
		{
			collection->add(std::make_pair(delivery->weight, delivery->hash_code), delivery);
			break;
		}
		case PRICE:
		{
			collection->add(std::make_pair(delivery->price, delivery->hash_code), delivery);
			break;
		}
		case DELI_PRICE:
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
	delivery->send_time = getStringInput(SEND_TIME, "sending data");
	delivery->departure_comp = getStringInput(DEPART, "departure point (by company)");
	delivery->reciever = getStringInput(RECIEVER, "reciever (to country)");
	delivery->recieve_time = getStringInput(RECI_TIME, "recieving data");
	delivery->destination_comp = getStringInput(DESTINATION, "destination (for company)");
	delivery->type_of_transport = getStringInput(TRANSPORT, "type of transport");

	DeliGenerator* delivery_gen = reinterpret_cast<DeliGenerator*>(generator);
	delivery->deliver_price = delivery_gen->get_delivery_price(*delivery);
	generator->generateHash(*delivery, gen);
	return delivery;
}

template <typename TKey, typename TData>
void DeliveryManager<TKey, TData>::generateData(const int cmp_choice)
{
	std::list<Delivery*>* deliveries;

	setChoiceGetType(cmp_choice, POST);
	auto begin = std::chrono::steady_clock::now();

	for (int i = 0; i < DATA_SIZE; i++)
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
	generateData(choice_number);
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
			getUserData();
		}
		else if (choice_number == 3) //DELETE
		{
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

	auto begin = std::chrono::steady_clock::now();
	addDeliveryInCollection(created_deliveries.back());
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	std::cout << blue << "The time of inserting: " << cyan << elapsed_ms.count() << blue << " micro s" << white << std::endl;

	std::cout << std::endl << green << "Added new delivery:" << std::endl;
	std::cout << *created_deliveries.back() << std::endl;
	std::cout << std::endl << green << "Added " << yellow << 1 << green << "/" << value_of_deliveries << white << std::endl;
	for (int i = 1; i < value_of_deliveries; i++)
	{
		created_deliveries.push_back(createUserDelivery(created_deliveries.back()->reciever));

		begin = std::chrono::steady_clock::now();
		addDeliveryInCollection(created_deliveries.back());
		end = std::chrono::steady_clock::now();
		elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
		std::cout << blue << "The time of inserting: " << cyan << elapsed_ms.count() << blue << " micro s" << white << std::endl;

		std::cout << std::endl << green << "Added new delivery:" << std::endl;
		std::cout << *created_deliveries.back() << std::endl;
		std::cout << std::endl << green << "Added " << yellow << i + 1 << green << "/" << value_of_deliveries << white << std::endl;
	}
	
}
template<typename TKey, typename TData>
void DeliveryManager<TKey, TData>::getUserData()
{
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
			DELITYPES type;
			if (!wantToChangeData())
			{
				break;
			}

			if (found_data->size() == 1)
			{
				Delivery* delivery = found_data->back();
				makeChanging(delivery);
				break;
			}
			else //find by HASH
			{
				unsigned int hash_value;
				Delivery* actual_delivery = nullptr;
				std::list<Delivery*>::iterator iter;
				std::cout << cyan << "Was found: " << green << found_data->size() << cyan << " deliveries." << white << std::endl;
				while (true)
				{
					hash_value = getHashInput();

					for (iter = found_data->begin(); iter != found_data->end(); iter++)
					{
						if ((*iter)->hash_code == hash_value)
						{
							actual_delivery = *iter;
							found_data->erase(iter);
							break;
						}
					}
					if (actual_delivery == nullptr)
					{
						std::cout << red << "Hash was not found by your search request." << white << std::endl;
						continue;
					}
					makeChanging(actual_delivery);
					break;
				}
				break;
			}

		}

	}
	delete found_data;

}
template<typename TKey, typename TData>
bool DeliveryManager<TKey, TData>::wantToChangeData()
{
	
	std::string find_request = "";
	while (true)
	{
		std::cout << cyan << "Do you want to change data (y/n)?" << white << std::endl << "> ";
		find_request.clear();
		userInput(find_request);
		if (find_request.size() != 1)
		{
			std::cout << red << "You have to input 'y' or 'n'. " << white << std::endl;
			continue;
		}
		
		if (tolower(find_request[0]) == 'y')
		{
			return true;
		}
		else if (tolower(find_request[0]) == 'n')
		{
			return false;
		}
		else
		{
			std::cout << red << "You have to input 'y' or 'n'. " << white << std::endl;
			continue;
		}
	}
}
template<typename TKey, typename TData>
void DeliveryManager<TKey, TData>::makeChanging(Delivery*& delivery)
{
	int choice_number;
	std::cout << cyan << "Was found:" << white << std::endl;
	std::cout << *delivery << std::endl;
	std::cout << cyan << "Choose field to change data:" << white << std::endl;
	chooseFieldPrint();
	choice_number = userChoice(1, 12);
	DELITYPES type = setChoiceGetType(choice_number, PATCH);
	
	changeByField(type, delivery);
	
	std::cout << *delivery << std::endl;
}
template<typename TKey, typename TData>
void DeliveryManager<TKey, TData>::changeByField(const DELITYPES type, Delivery*& delivery)
{
	bool is_deleted = false;
	std::string* new_data_field;
	float new_number;
	Delivery saved_data(*delivery);
	DeliGenerator* delivery_gen = reinterpret_cast<DeliGenerator*>(generator);
	switch (type)
	{
		case NAME:
		{
			is_deleted = deleteHook(type, delivery);
			new_data_field = getStringInput(type, "name");
			if (is_deleted)
			{
				delivery = new Delivery(saved_data);
				delivery->name = new_data_field;
				addDeliveryInCollection(delivery);
				std::cout << green << "Data changed!" << white << std::endl;
				return;
			}
			delivery->name = new_data_field;
			std::cout << green << "Data changed!" << white << std::endl;
			break;
		}
		case CONTENT:
		{
			is_deleted = deleteHook(type, delivery);
			new_data_field = getStringInput(type, "content");
			if (is_deleted)
			{
				delivery = new Delivery(saved_data);
				delivery->content = new_data_field;
				addDeliveryInCollection(delivery);
				std::cout << green << "Data changed!" << white << std::endl;
				return;
			}
			delivery->content = new_data_field;
			std::cout << green << "Data changed!" << white << std::endl;
			break;
		}
		case SENDER:
		{
			is_deleted = deleteHook(type, delivery);
			new_data_field = getStringInput(type, "sender (from country)");
			if (is_deleted)
			{
				delivery = new Delivery(saved_data);
				delivery->sender = new_data_field;
				addDeliveryInCollection(delivery);
				std::cout << green << "Data changed!" << white << std::endl;
				return;
			}
			delivery->sender = new_data_field;
			std::cout << green << "Data changed!" << white << std::endl;
			break;
		}
		case SEND_TIME:
		{
			is_deleted = deleteHook(type, delivery);
			new_data_field = getStringInput(type, "sending data");
			if (is_deleted)
			{
				delivery = new Delivery(saved_data);
				delivery->send_time = new_data_field;
				addDeliveryInCollection(delivery);
				std::cout << green << "Data changed!" << white << std::endl;
				return;
			}
			delivery->send_time = new_data_field;
			std::cout << green << "Data changed!" << white << std::endl;
			break;
		}
		case DEPART:
		{
			is_deleted = deleteHook(type, delivery);
			new_data_field = getStringInput(type, "departure point (by company)");
			if (is_deleted)
			{
				delivery = new Delivery(saved_data);
				delivery->departure_comp = new_data_field;
				addDeliveryInCollection(delivery);
				std::cout << green << "Data changed!" << white << std::endl;
				return;
			}
			delivery->departure_comp = new_data_field;
			std::cout << green << "Data changed!" << white << std::endl;
			break;
		}
		case RECIEVER:
		{
			is_deleted = deleteHook(type, delivery);
			new_data_field = getStringInput(type, "reciever (to country)");
			if (is_deleted)
			{
				delivery = new Delivery(saved_data);
				delivery->reciever = new_data_field;
				addDeliveryInCollection(delivery);
				std::cout << green << "Data changed!" << white << std::endl;
				return;
			}
			delivery->reciever = new_data_field;
			std::cout << green << "Data changed!" << white << std::endl;
			break;
		}
		case RECI_TIME:
		{
			is_deleted = deleteHook(type, delivery);
			new_data_field = getStringInput(type, "recieving data");
			if (is_deleted)
			{
				delivery = new Delivery(saved_data);
				delivery->recieve_time = new_data_field;
				addDeliveryInCollection(delivery);
				std::cout << green << "Data changed!" << white << std::endl;
				return;
			}
			delivery->recieve_time = new_data_field;
			std::cout << green << "Data changed!" << white << std::endl;
			break;
		}
		case DESTINATION:
		{
			is_deleted = deleteHook(type, delivery);
			new_data_field = getStringInput(type, "destination (for company)");
			if (is_deleted)
			{
				delivery = new Delivery(saved_data);
				delivery->destination_comp = new_data_field;
				addDeliveryInCollection(delivery);
				std::cout << green << "Data changed!" << white << std::endl;
				return;
			}
			delivery->destination_comp = new_data_field;
			std::cout << green << "Data changed!" << white << std::endl;
			break;
		}
		case TRANSPORT:
		{

			is_deleted = deleteHook(type, delivery);
			new_data_field = getStringInput(type, "type of transport");
			
			if (is_deleted)
			{
				delivery = new Delivery(saved_data);
				delivery->type_of_transport = new_data_field;
				delivery->deliver_price = delivery_gen->get_delivery_price(*delivery);
				addDeliveryInCollection(delivery);
				std::cout << green << "Data changed!" << white << std::endl;
				return;
			}
			delivery->type_of_transport = new_data_field;
			delivery->deliver_price = delivery_gen->get_delivery_price(*delivery);
			std::cout << green << "Data changed!" << white << std::endl;
			break;
		}
		case WEIGHT:
		{
			is_deleted = deleteHook(type, delivery);
			new_number = getFloatInput(PATCH, "weight");
			
			if (is_deleted)
			{
				delivery = new Delivery(saved_data);
				delivery->weight = new_number;
				delivery->deliver_price = delivery_gen->get_delivery_price(*delivery);
				addDeliveryInCollection(delivery);
				std::cout << green << "Data changed!" << white << std::endl;
				return;
			}
			delivery->weight = new_number;
			delivery->deliver_price = delivery_gen->get_delivery_price(*delivery);
			std::cout << green << "Data changed!" << white << std::endl;
			break;
		}
		case PRICE:
		{
			is_deleted = deleteHook(type, delivery);
			new_number = getFloatInput(PATCH, "price");
			if (is_deleted)
			{
				delivery = new Delivery(saved_data);
				delivery->price = new_number;
				addDeliveryInCollection(delivery);
				std::cout << green << "Data changed!" << white << std::endl;
			}
			delivery->price = new_number;
			std::cout << green << "Data changed!" << white << std::endl;
			break;
		}
		case DELI_PRICE:
		{
			std::cout << red << "Delivery price generates automatically. You don`t have access to change this field." << white << std::endl;
			break;
		}
	}
	
}
#pragma endregion

#pragma region FindRequest

std::list<Delivery*>* DeliveryManager<std::pair<float, unsigned int>, Delivery*>::findData() {
	std::list<Delivery*>* foundData;
	std::cout << blue << "You can search only by comparator type: " << yellow << comp_str << white << std::endl;
	float search_param = getFloatInput(GET, comp_str);


	auto begin = std::chrono::steady_clock::now();
	foundData = collection->find(std::make_pair(search_param, 0));

	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	std::cout << blue << "The time of searching: " << cyan << elapsed_ms.count() << blue << " mcs" << white << std::endl;
	return foundData;
}

std::list<Delivery*>* DeliveryManager<std::pair<std::string*, unsigned int>, Delivery*>::findData() {
	std::list<Delivery*>* foundData;
	std::cout << blue << "You can search only by comparator type: " << yellow << comp_str << white << std::endl << "> ";
	std::string find_request = "";
	userInput(find_request);

	auto begin = std::chrono::steady_clock::now();
	foundData = collection->find(std::make_pair(&find_request, 0));
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	std::cout << blue << "The time of searching: " << cyan << elapsed_ms.count() << blue << " micro s" << white << std::endl;

	return foundData;
}
#pragma endregion

#pragma region RemoveRequest

bool DeliveryManager<std::pair<std::string*, unsigned int>, Delivery*>::deleteHook(const DELITYPES type, Delivery* const& delivery)
{
	switch (type)
	{
		case NAME:
		{
			if (type == comp_type)
			{
				collection->remove(std::make_pair(delivery->name, delivery->hash_code));
				return true;
			}
			return false;
		}
		case CONTENT:
		{
			if (type == comp_type)
			{
				collection->remove(std::make_pair(delivery->content, delivery->hash_code));
				return true;
			}
			return false;
		}
		case SENDER:
		{
			if (type == comp_type)
			{
				collection->remove(std::make_pair(delivery->sender, delivery->hash_code));
				return true;
			}
			return false;
		}
		case SEND_TIME:
		{
			if (type == comp_type)
			{

				collection->remove(std::make_pair(delivery->send_time, delivery->hash_code));
				return true;
			}
			return false;
		}
		case DEPART:
		{
			if (type == comp_type)
			{
				collection->remove(std::make_pair(delivery->departure_comp, delivery->hash_code));
				return true;
			}
			return false;
		}
		case RECIEVER:
		{
			if (type == comp_type)
			{
				collection->remove(std::make_pair(delivery->reciever, delivery->hash_code));
				return true;
			}
			return false;
		}
		case RECI_TIME:
		{
			if (type == comp_type)
			{
				collection->remove(std::make_pair(delivery->recieve_time, delivery->hash_code));
				return true;
			}
			return false;
		}
		case DESTINATION:
		{
			if (type == comp_type)
			{
				collection->remove(std::make_pair(delivery->destination_comp, delivery->hash_code));
				return true;
			}
			return false;
		}
		case TRANSPORT:
		{
			if (type == comp_type)
			{
				collection->remove(std::make_pair(delivery->type_of_transport, delivery->hash_code));
				return true;
			}
			return false;
		}
	}
	return false;
}

bool DeliveryManager<std::pair<float, unsigned int>, Delivery*>::deleteHook(const DELITYPES type, Delivery* const& delivery)
{
	switch (type)
	{
		case WEIGHT:
		{
			if (type == comp_type)
			{
				collection->remove(std::make_pair(delivery->weight, delivery->hash_code));
				return true;
			}
			else if (comp_type == DELI_PRICE)
			{
				collection->remove(std::make_pair(delivery->deliver_price, delivery->hash_code));
				return true;
			}
			return false;
		}
		case PRICE:
		{
			if (type == comp_type)
			{
				collection->remove(std::make_pair(delivery->price, delivery->hash_code));
				return true;
			}
			return false;
		}
		case TRANSPORT:
		{
			if (comp_type == DELI_PRICE)
			{
				collection->remove(std::make_pair(delivery->deliver_price, delivery->hash_code));
				return true;
			}
			return false;
		}
		case DELI_PRICE:
		{
			if (type == DELI_PRICE)
			{
				collection->remove(std::make_pair(delivery->deliver_price, delivery->hash_code));
				return true;
			}
			return false;
		}
	}
	return false;
}

template<typename TKey, typename TData>
void DeliveryManager<TKey, TData>::removeData()
{
	std::cout << cyan << "You have to find data before deleting." << white << std::endl;
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

		int choice_number;
		DELITYPES type;
		Delivery* actual_delivery = nullptr;
		if (found_data->size() == 1)
		{
			actual_delivery = found_data->back();

			auto begin = std::chrono::steady_clock::now();
			deleteHook(comp_type, actual_delivery);
			auto end = std::chrono::steady_clock::now();
			auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
			std::cout << blue << "The time of deleting: " << cyan << elapsed_ms.count() << blue << " micro s" << white << std::endl;

		}
		else //find by HASH
		{
			unsigned int hash_value;
			std::list<Delivery*>::iterator iter;
			std::cout << cyan << "Was found: " << green << found_data->size() << cyan << " deliveries." << white << std::endl;
			while (true)
			{
				hash_value = getHashInput();

				for (iter = found_data->begin(); iter != found_data->end(); iter++)
				{
					if ((*iter)->hash_code == hash_value)
					{
						actual_delivery = *iter;
						found_data->erase(iter);
						break;
					}
				}
				if (actual_delivery == nullptr)
				{
					std::cout << red << "Hash was not found by your search request." << white << std::endl;
					continue;
				}
				auto begin = std::chrono::steady_clock::now();
				deleteHook(comp_type, actual_delivery);
				auto end = std::chrono::steady_clock::now();
				auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
				std::cout << blue << "The time of deleting: " << cyan << elapsed_ms.count() << blue << " micro s" << white << std::endl;
				break;
			}
		}
		
		std::cout << green << "Delivery successfully deleted." << white << std::endl;

	}
	delete found_data;
}
template<typename TKey, typename TData>
void DeliveryManager<TKey, TData>::makeDeleting(Delivery* delivery)
{
	int choice_number;
	std::cout << cyan << "Choose field to change data:" << white << std::endl;
	chooseFieldPrint();
	choice_number = userChoice(1, 12);
	DELITYPES type = setChoiceGetType(choice_number, PATCH);

	changeByField(type, delivery);

	std::cout << *delivery << std::endl;
}
#pragma endregion

