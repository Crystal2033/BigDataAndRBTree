#pragma once
#include "Generator.h"
#include "Container.h"
#include <chrono>
#include <string>
#include "UserFuncsAndCallbacks.h"

typedef enum RequestType {POST, GET, PATCH} REQ_TYPE;
template <typename TKey, typename TData>
class DeliveryManager {
private:
	Container<TKey, TData>* collection;
	InterfaceGenerator<Delivery>* generator;
	std::string comp_str;
	DELITYPES comp_type;
	//CONT_TYPE container_type; // нужно для deleteHook, чтобы из очереди при поиске и смене поля компаратора не удалялась доставка.
	DELITYPES setChoiceGetType(const int choice_num, RequestType req_type=POST);
	std::string* getStringInput(DELITYPES type, const std::string& request_str);
	unsigned int getHashInput();
	std::string* addToDataPool(DELITYPES type, const std::string& str);

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
	void generateData(const int user_choice);
	const std::string& getStringChoice() const { return comp_str; };
	/////////////////////////////////PUBLIC////////////////////////////////////
	public:
	int workWithUser(int choice_user);
	
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
				comp_type = DEPART;
				comp_str = "Departure point (by company)";
			}
			return DEPART;

		}
		case 8:
		{
			if (req_type == POST)
			{
				comp_type = RECIEVER;
				comp_str = "Reciever (to country)";
			}
			return RECIEVER;

		}
		case 9:
		{
			if (req_type == POST)
			{
				comp_type = DESTINATION;
				comp_str = "Destination point (for company)";
			}
			return DESTINATION;

		}
		case 10:
		{
			if (req_type == POST)
			{
				comp_type = TRANSPORT;
				comp_str = "Type of transport";
			}
			return TRANSPORT;
		}
		/*case 11: TODO:
		{
			return SEND_TIME;
		}
		case 12:
		{
			return RECI_TIME;
		}*/
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
unsigned int DeliveryManager<TKey, TData>::getHashInput()
{
	std::string input_data;
	std::string* dataField;
	unsigned int hash_value;
	while (true)
	{
		std::cout << blue << "You have to choose delivery by " << pink << "hash:" << blue << std::endl << "Input hash value (unsigned int number):" << std::endl << white << "> ";
		input_data.clear();
		std::cin.clear();
		std::getline(std::cin, input_data);
		std::cin.clear();
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
		std::cin.clear();
		std::getline(std::cin, number_str);
		std::cin.clear();
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
			getUserData();
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
	std::cout << *created_deliveries.back() << std::endl;
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
					//found_data->push_back(actual_delivery);
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
		std::cin.clear();
		std::getline(std::cin, find_request);
		std::cin.clear();
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
	std::cout << cyan << "Choose field to change data:" << white << std::endl;
	chooseFieldPrint();
	choice_number = userChoice(1, 10);
	DELITYPES type = setChoiceGetType(choice_number, PATCH);
	
	changeByField(type, delivery);
	std::cout << green << "Data changed!" << white << std::endl;
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
		case NAME: //name
		{
			is_deleted = deleteHook(type, delivery);
			new_data_field = getStringInput(type, "name");
			if (is_deleted)
			{
				delivery = new Delivery(saved_data);
				delivery->name = new_data_field;
				addDeliveryInCollection(delivery);
				return;
			}
			delivery->name = new_data_field;
			break;
		}
		case CONTENT: //content
		{
			is_deleted = deleteHook(type, delivery);
			new_data_field = getStringInput(type, "content");
			if (is_deleted)
			{
				delivery = new Delivery(saved_data);
				delivery->content = new_data_field;
				addDeliveryInCollection(delivery);
				return;
			}
			delivery->content = new_data_field;
			break;
		}
		case SENDER: //sender
		{
			is_deleted = deleteHook(type, delivery);
			new_data_field = getStringInput(type, "sender (from country)");
			if (is_deleted)
			{
				delivery = new Delivery(saved_data);
				delivery->sender = new_data_field;
				addDeliveryInCollection(delivery);
				return;
			}
			delivery->sender = new_data_field;
			break;
		}
		case DEPART: //departure point
		{
			is_deleted = deleteHook(type, delivery);
			new_data_field = getStringInput(type, "departure point (by company)");
			if (is_deleted)
			{
				delivery = new Delivery(saved_data);
				delivery->departure_comp = new_data_field;
				addDeliveryInCollection(delivery);
				return;
			}
			delivery->departure_comp = new_data_field;
			break;
		}
		case RECIEVER: //reciever
		{
			is_deleted = deleteHook(type, delivery);
			new_data_field = getStringInput(type, "reciever (to country)");
			if (is_deleted)
			{
				delivery = new Delivery(saved_data);
				delivery->reciever = new_data_field;
				addDeliveryInCollection(delivery);
				return;
			}
			delivery->reciever = new_data_field;
			break;
		}
		case DESTINATION: //destination point
		{
			is_deleted = deleteHook(type, delivery);
			new_data_field = getStringInput(type, "destination (for company)");
			if (is_deleted)
			{
				delivery = new Delivery(saved_data);
				delivery->destination_comp = new_data_field;
				addDeliveryInCollection(delivery);
				return;
			}
			delivery->destination_comp = new_data_field;
			break;
		}
		case TRANSPORT: //type of transport
		{

			is_deleted = deleteHook(type, delivery);
			new_data_field = getStringInput(type, "type of transport");
			
			if (is_deleted)
			{
				delivery = new Delivery(saved_data);
				delivery->type_of_transport = new_data_field;
				delivery->deliver_price = delivery_gen->get_delivery_price(*delivery);
				addDeliveryInCollection(delivery);
				return;
			}
			delivery->type_of_transport = new_data_field;
			delivery->deliver_price = delivery_gen->get_delivery_price(*delivery);
			break;
		}
		case WEIGHT: //weight
		{
			is_deleted = deleteHook(type, delivery);
			new_number = getFloatInput(PATCH, "weight");
			
			if (is_deleted)
			{
				delivery = new Delivery(saved_data);
				delivery->weight = new_number;
				delivery->deliver_price = delivery_gen->get_delivery_price(*delivery);
				addDeliveryInCollection(delivery);
				return;
			}
			delivery->weight = new_number;
			delivery->deliver_price = delivery_gen->get_delivery_price(*delivery);
			break;
		}
		case PRICE: //price
		{
			is_deleted = deleteHook(type, delivery);
			new_number = getFloatInput(PATCH, "price");
			if (is_deleted)
			{
				delivery = new Delivery(saved_data);
				delivery->price = new_number;
				addDeliveryInCollection(delivery);
			}
			delivery->price = new_number;
			break;
		}
		case DELI_PRICE: //delivery price
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

bool DeliveryManager<std::pair<std::string*, unsigned int>, Delivery*>::deleteHook(const DELITYPES type, Delivery* const& delivery)
{
	switch (type)
	{
		case NAME: //name
		{
			if (type == comp_type)
			{

				collection->remove(std::make_pair(delivery->name, delivery->hash_code));
				return true;

				
			}
			return false;
		}
		case CONTENT: //content
		{
			if (type == comp_type)
			{
				
				collection->remove(std::make_pair(delivery->content, delivery->hash_code));
				return true;
				
			}
			return false;
		}
		case SENDER: //sender
		{
			if (type == comp_type)
			{
				
				collection->remove(std::make_pair(delivery->sender, delivery->hash_code));
				return true;
				
			}
			return false;
		}
		case DEPART: //departure point
		{
			if (type == comp_type)
			{
				
				collection->remove(std::make_pair(delivery->departure_comp, delivery->hash_code));
				return true;
				
			}
			return false;
		}
		case RECIEVER: //reciever
		{
			if (type == comp_type)
			{
				
				collection->remove(std::make_pair(delivery->reciever, delivery->hash_code));
				return true;
				
			}
			return false;
		}
		case DESTINATION: //destination point
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
		case WEIGHT: //weight
		{
			if (type == comp_type || comp_type == DELI_PRICE) //deli_price формируется из веса +  вид транспорта.
			{
				
				collection->remove(std::make_pair(delivery->weight, delivery->hash_code));
				return true;
				
			}
			return false;
		}
		case PRICE: //price
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
			deleteHook(comp_type, actual_delivery);
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
				
				deleteHook(comp_type, actual_delivery);
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
	choice_number = userChoice(1, 10);
	DELITYPES type = setChoiceGetType(choice_number, PATCH);

	changeByField(type, delivery);
	std::cout << green << "Data changed!" << white << std::endl;
	std::cout << *delivery << std::endl;
}
#pragma endregion

