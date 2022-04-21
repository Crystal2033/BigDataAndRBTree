#pragma once
class Delivery {
public:
	std::string* name;              // Название груза. names DONE
	std::string* content;           // Содержимое  contents  DONE
	int weight;                    // Вес
	int price;                     // Цена содержимого
	int deliver_price;             // Цена доставки
	std::string* sender;            // Отправитель contries  DONE
	std::string* departure_point;   // Пункт отсылки    companies DONE
	//Time depart_time;
	std::string* reciever;          // Получатель  contries  DONE
	std::string* destination;       // Пункт назначения companies DONE 
	//Time dest_time;
	std::string* type_of_transport; // Тип транспорта. transport_types DONE
};