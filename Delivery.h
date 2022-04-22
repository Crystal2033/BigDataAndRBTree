#pragma once
#include "Colours.h"
class Delivery {
public:
	Delivery();
	unsigned int hash_code;
	std::string* name;             // Название груза. names DONE
	std::string* content;          // Содержимое  contents  DONE
	float weight;                    // Вес
	float price;                     // Цена содержимого
	float deliver_price;             // Цена доставки
	std::string* sender;           // Отправитель contries  DONE
	std::string* departure_comp;   // Пункт отсылки    companies DONE
	//Time depart_time;
	std::string* reciever;     // Получатель  contries  DONE
	std::string* destination_comp;       // Пункт назначения companies DONE 
	//Time dest_time;
	std::string* type_of_transport; // Тип транспорта. transport_types DONE
	friend std::ostream& operator<<(std::ostream& out, const Delivery& delivery);
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

std::ostream& operator<<(std::ostream& out, const Delivery& delivery) {
	out << yellow << "HashCode: " << pink << delivery.hash_code << white << std::endl;
	if (delivery.name != nullptr) {
		out << yellow << "name: " << cyan << *delivery.name << white << std::endl;
	}
	else {
		throw DeliveryNullException("Name is nullptr.");
	}

	if (delivery.content != nullptr) {
		out << yellow << "content: " << cyan << *delivery.content << white << std::endl;
	}
	else {
		throw DeliveryNullException("Content is nullptr.");
	}

	if (delivery.weight != 0.0) {
		out << yellow << "weight: " << cyan << delivery.weight << " kg" << white << std::endl;
	}
	else {
		throw DeliveryNullException("Weight is 0.0");
	}

	out << yellow << "price: " << green << delivery.price << " $" << white << std::endl;
	out << yellow << "delivery price: " << green << delivery.deliver_price << " $" << white << std::endl;

	if (delivery.sender != nullptr) {
		out << yellow << "from (country): " << cyan << *delivery.sender << white << std::endl;
	}
	else {
		throw DeliveryNullException("Sender is nullptr");
	}


	if (delivery.departure_comp != nullptr) {
		out << yellow << "by (company): " << cyan << *delivery.departure_comp << white << std::endl;
	}
	else {
		throw DeliveryNullException("Departure company is nullptr");
	}

	if (delivery.reciever != nullptr) {
		out << yellow << "to (country): " << cyan << *delivery.reciever << white << std::endl;
	}
	else {
		throw DeliveryNullException("Reciever is nullptr");
	}

	if (delivery.destination_comp != nullptr) {
		out << yellow << "for (company): " << cyan << *delivery.destination_comp << white << std::endl;
	}
	else {
		throw DeliveryNullException("Destination company is nullptr");
	}

	if (delivery.type_of_transport != nullptr) {
		out << yellow << "transport type: " << cyan << *delivery.type_of_transport << white << std::endl;
	}
	else {
		throw DeliveryNullException("Type of transport is nullptr");
	}
	
	return out;
}