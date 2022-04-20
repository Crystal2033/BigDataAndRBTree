#pragma once
class Delivery {
public:
	std::string name;              // Название груза.
	std::string sender;            // Отправитель
	std::string reciever;          // Получатель
	std::string content;           // Содержимое
	double weight;                 // Вес
	double price;                  // Цена содержимого
	double deliver_price;          // Цена доставки

	std::string destination;       // Пункт назначения
	std::string departure_point;   // Пункт отсылки
	//Time dest_time;
	//Time depart_time;
	std::string type_of_transport; // Тип транспорта.
};