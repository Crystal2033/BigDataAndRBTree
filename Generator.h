#pragma once
#include "Delivery.h"
#include <list>
#include <random>
#include <string>
#include <math.h>
#include <boost/functional/hash.hpp>
#include "DataPool.h"
#define DATA_SIZE 1000

#define WEIGHT_FREE_LIMIT 1000
#define WEIGHT_FINE 0.5

#define CAR_FINE 1
#define PLANE_FINE 2
#define HELICOPTER_FINE 3
#define ROCKET_FINE 5
#define VAN_FINE 1
#define LORRY_FINE 1
#define BOAT_FINE 2
#define TRACTOR_FINE 0
#define MOTORBIKE_FINE 1
#define SHIP_FINE 3
template<typename GenerType>
class InterfaceGenerator {
public:
	virtual std::list<GenerType*>& generateData() = 0;
	virtual unsigned getGeneratedCount() const = 0;
	virtual std::list<std::string>* getPoolCollection(DELITYPES typeOfData) const = 0;
	virtual void generateHash(GenerType&, std::mt19937& gen) const = 0;
	virtual ~InterfaceGenerator() = default;
};

class DeliGenerator : public InterfaceGenerator<Delivery> {
public:
	std::list<Delivery*>& generateData() override;
	DataPool* data;
	unsigned getGeneratedCount() const override { return value_of_dels; };
	DeliGenerator();
	~DeliGenerator();
	std::list<std::string>* getPoolCollection(DELITYPES typeOfData) const override;
	void generateHash(Delivery& delivery, std::mt19937& gen) const override;
	float get_delivery_price(const Delivery& delivery) const;
private:
	unsigned int value_of_dels = 0;
	Delivery& startChain() const;
	Delivery& continueChain(std::string* const& last_dep_point) const;
	void createData(Delivery& delivery, std::string* const& last_dep_point =nullptr) const;
};


DeliGenerator::DeliGenerator()
{
	data = new DataPool;
}

DeliGenerator::~DeliGenerator()
{
	delete data;
}

std::list<std::string>* DeliGenerator::getPoolCollection(DELITYPES typeOfData) const
{
	if (typeOfData == NAME)
	{
		return &data->names;
	}
	else if (typeOfData == CONTENT)
	{
		return &data->contents;
	}
	else if (typeOfData == SENDER || typeOfData == RECIEVER)
	{
		return &data->countries;
	}
	else if (typeOfData == DEPART || typeOfData == DESTINATION)
	{
		return &data->companies;
	}
	else if (typeOfData == TRANSPORT)
	{
		return &data->transport_types;
	}
	else if (typeOfData == SEND_TIME || typeOfData == RECI_TIME)
	{
		return &data->time;
	}
}

void DeliGenerator::generateHash(Delivery& delivery, std::mt19937& gen) const
{
	boost::hash<std::string> hash_str;
	char random_char1 = char(' ' + (gen() % '['));
	char random_char2 = char(' ' + (gen() % '['));
	delivery.hash_code = hash_str(*delivery.content + *delivery.name + random_char1 + random_char2);
}

Delivery& DeliGenerator::startChain() const {
	Delivery* delivery = new Delivery;
	createData(*delivery);

	return *delivery;
}

float DeliGenerator::get_delivery_price(const Delivery& delivery) const {
	const float start_delivery_price = 200.0;
	float total_delivery_price = start_delivery_price;
	if (delivery.weight < WEIGHT_FREE_LIMIT) {
		total_delivery_price += start_delivery_price * WEIGHT_FINE;
	}

	std::string transport_type = *delivery.type_of_transport;
	if (transport_type == "Car") {
		total_delivery_price += start_delivery_price * CAR_FINE;
	}
	else if (transport_type == "Plane") {
		total_delivery_price += start_delivery_price * PLANE_FINE;
	}
	else if (transport_type == "Helicopter") {
		total_delivery_price += start_delivery_price * HELICOPTER_FINE;
	}
	else if (transport_type == "Rocket") {
		total_delivery_price += start_delivery_price * ROCKET_FINE;
	}
	else if (transport_type == "Van") {
		total_delivery_price += start_delivery_price * VAN_FINE;
	}
	else if (transport_type == "Lorry") {
		total_delivery_price += start_delivery_price * LORRY_FINE;
	}
	else if (transport_type == "Boat") {
		total_delivery_price += start_delivery_price * BOAT_FINE;
	}
	else if (transport_type == "Tractor") {
		total_delivery_price += start_delivery_price * TRACTOR_FINE;
	}
	else if (transport_type == "MotorBike") {
		total_delivery_price += start_delivery_price * MOTORBIKE_FINE;
	}
	else if (transport_type == "Ship") {
		total_delivery_price += start_delivery_price * SHIP_FINE;
	}
	return total_delivery_price;
}

Delivery& DeliGenerator::continueChain(std::string* const& last_dep_point) const {

	Delivery* delivery = new Delivery;
	createData(*delivery, last_dep_point);

	return *delivery;
}

void getListNode(std::list<std::string>::iterator* it, std::list<std::string>* const& list, std::string*& destin, const int offset)
{
	std::advance(*it, offset);
	destin = &(**it);
	*it = list->begin();
}

void DeliGenerator::createData(Delivery& delivery, std::string* const& last_dep_point) const {
	std::random_device rd;
	std::mt19937 gen(rd());
	float random_float = 0.0;
	unsigned int random_number = 0;
	
	auto names_front = data->names.begin();
	auto contents_front = data->contents.begin();
	auto countries_front = data->countries.begin();
	auto companies_front = data->companies.begin();
	auto transports_front = data->transport_types.begin();
	auto times_front = data->time.begin();

	//////////////////////////////////////NAME///////////////////////////////////////
	random_number = gen() % data->names.size();
	getListNode(&names_front, &data->names, delivery.name, random_number);
	//delivery.name = &(data->names[random_number]);

	//////////////////////////////////////CONTENT///////////////////////////////////////
	random_number = gen() % data->contents.size();
	getListNode(&contents_front, &data->contents, delivery.content, random_number);
	//delivery.content = &(data->contents[random_number]);

	//////////////////////////////////////WEIGHT///////////////////////////////////////
	random_float = float(gen()) / float(rand() + 1.0) / 10000;
	delivery.weight = random_float;

	//////////////////////////////////////PRICE///////////////////////////////////////
	random_float = float(gen()) / float(rand() + 1.0) / 100;
	delivery.price = random_float;

	//////////////////////////////////////SENDER///////////////////////////////////////
	if (last_dep_point == nullptr) { 
		random_number = gen() % data->countries.size();
		getListNode(&countries_front, &data->countries, delivery.sender, random_number);
		//delivery.sender = &(data->countries[random_number]);
	}
	else { //Start chain case. Condition that n end point has to be equal n+1 start point in chain
		delivery.sender = last_dep_point;
	}

	//////////////////////////////////////SEND_TIME///////////////////////////////////////
	random_number = gen() % data->time.size();
	getListNode(&times_front, &data->time, delivery.send_time, random_number);

	//////////////////////////////////////DEPARTURE_COMP///////////////////////////////////////
	random_number = gen() % data->companies.size();
	getListNode(&companies_front, &data->companies, delivery.departure_comp, random_number);
	//delivery.departure_comp = &(data->companies[random_number]);
	
	//////////////////////////////////////RECEIVER///////////////////////////////////////
	while (true) {
		random_number = gen() % data->countries.size();
		getListNode(&countries_front, &data->countries, delivery.reciever, random_number);
		//delivery.reciever = &(data->countries[random_number]);
		if (delivery.reciever != delivery.sender) {
			break;
		}
	}

	//////////////////////////////////////RECEIVER_TIME///////////////////////////////////////
	random_number = gen() % data->time.size();
	getListNode(&times_front, &data->time, delivery.recieve_time, random_number);

	//////////////////////////////////////DESTINATION///////////////////////////////////////
	random_number = gen() % data->companies.size();
	getListNode(&companies_front, &data->companies, delivery.destination_comp, random_number);
	//delivery.destination_comp = &(data->companies[random_number]);

	//////////////////////////////////////TRANSPORT_TYPE///////////////////////////////////////
	random_number = gen() % data->transport_types.size();
	getListNode(&transports_front, &data->transport_types, delivery.type_of_transport, random_number);

	//////////////////////////////////////DEPARTURE_PRICE///////////////////////////////////////
	delivery.deliver_price = get_delivery_price(delivery);
	generateHash(delivery, gen);
	
}

std::list<Delivery*>& DeliGenerator::generateData()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	unsigned int chain_size = 1;
	chain_size = gen() % 10 + 1;
	value_of_dels += chain_size;
	std::list<Delivery*>* delivery_chain = new std::list<Delivery*>;
	//std::cout << purple << "The chain size: " << blue << chain_size << white << std::endl;
	delivery_chain->push_back(&startChain());
	for (int i = 0; i < chain_size - 1; i++) {
		delivery_chain->push_back(&continueChain(delivery_chain->back()->reciever));
	}

	return *delivery_chain;

}