#pragma once
class Delivery {
public:
	std::string name;              // Название груза. names DONE
	std::string sender;            // Отправитель contries  DONE
	std::string reciever;          // Получатель  contries  DONE
	std::string content;           // Содержимое  contents  DONE
	double weight;                 // Вес
	double price;                  // Цена содержимого
	double deliver_price;          // Цена доставки

	std::string destination;       // Пункт назначения companies DONE 
	std::string departure_point;   // Пункт отсылки    companies DONE
	//Time dest_time;
	//Time depart_time;
	std::string type_of_transport; // Тип транспорта. transport_types DONE
};