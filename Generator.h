#pragma once
#include "Delivery.h"
#include <list>
#include <random>
#include <string>
#include <math.h>
#define WEIGHT_FREE_LIMIT 1000
#define WEIGHT_FINE 0.1

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
class InterfaceGenerator {
public:
	virtual std::list<Delivery*>& generateData() = 0;
	virtual unsigned get_generated_value() const = 0;
	virtual ~InterfaceGenerator() = default;
};

class DeliGenerator : public InterfaceGenerator {
public:
	std::list<Delivery*>& generateData() override;
	unsigned get_generated_value() const override { return value_of_dels; };
	std::vector<std::string> names {"Cyber", "Java", "C++", "Python", "Pascal", "Ruby", "Scratch",
	"D", "R", "SQL", "MicrosoftAccept", "Joy", "Haskel", "Prolog", "ML", "Lisp", "Mercury", "Unlambda",
	"Agba", "Forth", "Coq", "Refile", "Parsec", "LL", "JavaScript", "HTML", "Basic", "C", 
	"PHP", "Matcad", "Coomir", "Kotlin", "Bash", "Lua", "PowerShell", "Rust", "TypeScript", "Scilab",
	"Sed", "Maple", "Groovy", "Dart", "Haskell", "Perl", "Autolt", "Make", "Pawn", "Julia", "Elixir", "Maxima"};
	std::vector<std::string> countries {"Moldovia", "Russia", "USA", "Canada", "Baku", "Albania",
	"Angola", "Argentina", "Belgia", "Brazilia", "Bahrain", "Denmark", "Finland", "Germany", "Ghana", 
	"Egypt", "Haity", "Iran", "Iraq", "Japan", "Kenya", "Lybia", "Oman", "Ukraine", "Malta", "Romania", 
	"Uganda", "India", "Iceland", "France", "Italy", "Estonia", "Greece", "Chile", "Andora", "Armenia"
	"Fiji", "Laos", "Netherlands", "Nepal", "Kuwait", "Kazakhstan", "Palau", "Peru", "Portugal", "Poland", 
	"Togo", "Tongo", "Tuvalu", "Uruguay", "Yemen"};
	std::vector<std::string> contents { "Adobe", "Flash", "Develop", "IntelliJ", "PowerFlasher", "Eclipse",
	"GNATStudio", "SlickEdit", "Fresh", "SASM", "BasicAndroid", "Gambas", "SmallBasic", "Xojo", "MonoDevelop",
	"SharpDevelop", "AqulaSoft", "Anjuta", "Bulder", "AbstractFactory", "FactoryMethod", "CodeBlocks", "CodeLite",
	"Geany", "CLion", "LabWindows", "Oracle", "XCode", "OpenWatcom", "NetBeans", "VSCode", "DevC++", "QTcreator", 
	"SLIME", "Eiffel", "Plato", "BlueJ", "DrJava", "Servoy", "JCreator", "Atom", "Emacs", "Delphi", "MSEide", 
	"Padre", "Eric", "PyCharm", "PIDA", "Spyder", "Thorny"};
	std::vector<std::string> companies { "Calera", "Chrysler", "Cigna", "CNN", "Tomcat", "Ford", "Peugeot",
	"Mercedes", "Opel", "Nissan", "Porsche", "Clarion", "Coleco", "Fanta", "CocaCola", "Colt", "Deagle",
	"Daewoo", "Datsun", "Dell", "NASA", "EMI", "Lada", "Zeus", "Fiat", "Glaxo", "Google", "Haribo", "SecretServices",
	"Hitachi", "HTC", "Apple", "Samsung", "Intel", "Kesko", "Lukoil", "MineralWater", "Mazda", "Haval", "BMW", 
	"Toyota", "LandRover", "Honda", "Lexus", "Fiat", "Suzuki", "KIA", "SsangYong", "Maserati", "Gaz"};
	std::vector<std::string> transport_types {"Car", "Plane", "Helicopter", "Rocket", "Van", "Lorry", 
	"Boat", "Tractor", "MotorBike", "Ship"};
	DeliGenerator() = default;
	~DeliGenerator() = default;
private:
	unsigned int value_of_dels = 0;
	Delivery& startChain();
	Delivery& continueChain(std::string* const& last_dep_point);
	void createData(Delivery& delivery, std::string* const& last_dep_point =nullptr) ;
	float get_delivery_price(Delivery& delivery);
};


Delivery& DeliGenerator::startChain() {
	Delivery* delivery = new Delivery;
	createData(*delivery);

	return *delivery;
}

float DeliGenerator::get_delivery_price(Delivery& delivery) {
	const float start_delivery_price = 300.0;
	float total_delivery_price = start_delivery_price;
	if (delivery.weight > WEIGHT_FREE_LIMIT) {
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

Delivery& DeliGenerator::continueChain(std::string* const& last_dep_point) {

	Delivery* delivery = new Delivery;
	createData(*delivery, last_dep_point);

	return *delivery;
}

void DeliGenerator::createData(Delivery& delivery, std::string* const& last_dep_point) {
	std::random_device rd;
	std::mt19937 gen(rd());
	float random_float = 0.0;
	unsigned int random_number = 0;
	

	//////////////////////////////////////NAME///////////////////////////////////////
	random_number = gen() % names.size();
	delivery.name = &names[random_number];

	//////////////////////////////////////CONTENT///////////////////////////////////////
	random_number = gen() % contents.size();
	delivery.content = &contents[random_number];

	//////////////////////////////////////WEIGHT///////////////////////////////////////
	random_float = float(gen()) / float(rand() + 1.0) / 10000;
	delivery.weight = random_float;

	//////////////////////////////////////PRICE///////////////////////////////////////
	random_float = float(gen()) / float(rand() + 1.0) / 100;
	delivery.price = random_float;

	//////////////////////////////////////SENDER///////////////////////////////////////
	if (last_dep_point == nullptr) { 
		random_number = gen() % countries.size();
		delivery.sender = &countries[random_number];
	}
	else { //Start chain case. Condition that n end point has to be equal n+1 start point in chain
		delivery.sender = last_dep_point;
	}

	//////////////////////////////////////DEPARTURE_COMP///////////////////////////////////////
	random_number = gen() % companies.size();
	delivery.departure_comp = &companies[random_number];
	
	//////////////////////////////////////RECEIVER///////////////////////////////////////
	while (1) {
		random_number = gen() % countries.size();
		delivery.reciever = &countries[random_number];
		if (delivery.reciever != delivery.sender) {
			break;
		}
	}
	

	//////////////////////////////////////DESTINATION///////////////////////////////////////
	random_number = gen() % companies.size();
	delivery.destination_comp = &companies[random_number];

	//////////////////////////////////////TRANSPORT_TYPE///////////////////////////////////////
	random_number = gen() % transport_types.size();
	delivery.type_of_transport = &transport_types[random_number];

	//////////////////////////////////////DEPARTURE_PRICE///////////////////////////////////////
	
	delivery.deliver_price = get_delivery_price(delivery);;

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