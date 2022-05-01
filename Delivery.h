#pragma once
#include "Colours.h"
typedef enum {NAME, CONTENT, WEIGHT, PRICE, DELI_PRICE, SENDER, DEPART, RECIEVER, DESTINATION, TRANSPORT, SEND_TIME, RECI_TIME} DELITYPES;
class Delivery {
public:
	Delivery();
	unsigned int hash_code;
	std::string* name;					// Название груза. names DONE
	std::string* content;				// Содержимое  contents  DONE
	float weight;						 // Вес
	float price;						 // Цена содержимого
	float deliver_price;				// Цена доставки
	std::string* sender;				// Отправитель contries  DONE
	std::string* departure_comp;		 // Пункт отсылки    companies DONE
	//Time depart_time;
	std::string* reciever;				// Получатель  contries  DONE
	std::string* destination_comp;       // Пункт назначения companies DONE 
	//Time dest_time;
	std::string* type_of_transport;		// Тип транспорта. transport_types DONE
	//std::string* send_time;			// Время отправки
	//std::string* recieve_time;		//Время получения
	friend std::ostream& operator<<(std::ostream& out, const Delivery& delivery);
	void operator=(const Delivery& first);
};

Delivery::Delivery() {
	hash_code = 0;
	name = nullptr;             
	content = nullptr;          
	weight = 0.0;               
	price = 0.0;;               
	deliver_price = 0.0;        
	sender = nullptr;           
	departure_comp = nullptr;   
	//Time depart_time;
	reciever = nullptr;         
	destination_comp = nullptr; 
	//Time dest_time;
	type_of_transport = nullptr;
}

inline void Delivery::operator=(const Delivery& first)
{
	this->content = first.content;
	this->deliver_price = first.deliver_price;
	this->departure_comp = first.departure_comp;
	this->destination_comp = first.destination_comp;
	this->name = first.name;
	this->price = first.price;
	this->reciever = first.reciever;
	this->sender = first.sender;
	this->type_of_transport = first.type_of_transport;
	this->weight = first.weight;

}

std::ostream& operator<<(std::ostream& out, const Delivery& delivery) {
	out << blue << "HashCode: " << pink << delivery.hash_code << white << std::endl;
	if (delivery.name != nullptr) {
		out << blue << "name: " << cyan << *delivery.name << white << std::endl;
	}
	else {
		throw DeliveryNullException("Name is nullptr.");
	}

	if (delivery.content != nullptr) {
		out << blue << "content: " << cyan << *delivery.content << white << std::endl;
	}
	else {
		throw DeliveryNullException("Content is nullptr.");
	}

	if (delivery.weight != 0.0) {
		out << blue << "weight: " << cyan << delivery.weight << " kg" << white << std::endl;
	}
	else {
		throw DeliveryNullException("Weight is 0.0");
	}

	out << blue << "price: " << green << delivery.price << " $" << white << std::endl;
	out << blue << "delivery price: " << green << delivery.deliver_price << " $" << white << std::endl;

	if (delivery.sender != nullptr) {
		out << blue << "from (country): " << cyan << *delivery.sender << white << std::endl;
	}
	else {
		throw DeliveryNullException("Sender is nullptr");
	}


	if (delivery.departure_comp != nullptr) {
		out << blue << "by (company): " << cyan << *delivery.departure_comp << white << std::endl;
	}
	else {
		throw DeliveryNullException("Departure company is nullptr");
	}

	if (delivery.reciever != nullptr) {
		out << blue << "to (country): " << cyan << *delivery.reciever << white << std::endl;
	}
	else {
		throw DeliveryNullException("Reciever is nullptr");
	}

	if (delivery.destination_comp != nullptr) {
		out << blue << "for (company): " << cyan << *delivery.destination_comp << white << std::endl;
	}
	else {
		throw DeliveryNullException("Destination company is nullptr");
	}

	if (delivery.type_of_transport != nullptr) {
		out << blue << "transport type: " << cyan << *delivery.type_of_transport << white << std::endl;
	}
	else {
		throw DeliveryNullException("Type of transport is nullptr");
	}
	
	return out;
}
