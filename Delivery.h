#pragma once
class Delivery {
private:
	std::string name; //Ќазвание груза.
	double weight; //вес
	std::string sender_name; //отправитель
	std::string reciever; //получатель
	double price; //цена содержимого
	double deliver_price; // цена доставки
	std::string content; //содержимое
};