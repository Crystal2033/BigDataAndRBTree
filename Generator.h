#pragma once
#include "Delivery.h"
#include <list>
#include <random>
#include <string>
class InterfaceGenerator {
public:
	virtual std::list<Delivery*>& generateData() const = 0;
	virtual ~InterfaceGenerator() = default;
};

class DeliGenerator : public InterfaceGenerator {
public:
	std::list<Delivery*>& generateData() const override;
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

	Delivery& startChain() const;
	Delivery& continueChain(const std::string last_dep_point) const;
	void createData(Delivery& delivery, std::string last_dep_point="") const;
};

//DeliGenerator::DeliGenerator() {
//	std::string name = "Cyber";
//	names.push_back("Cyber");
//	names.push_back("Java");
//	names.push_back("C++");
//	names.push_back("Python");
//	names.push_back("Pascal");
//	names.push_back("Ruby");
//	names.push_back("Scratch");
//	names.push_back("D");
//	names.push_back("R");
//	names.push_back("SQL");
//	names.push_back("MicrosoftAccept");
//	names.push_back("Joy");
//	names.push_back("Haskel");
//	names.push_back("Prolog");
//	names.push_back("ML");
//	names.push_back("Lisp");
//	names.push_back("Mercury");
//	names.push_back("Unlambda");
//	names.push_back("Agba");
//	names.push_back("Forth");
//	names.push_back("Coq");
//	names.push_back("Refile");
//	names.push_back("Parsec");
//	names.push_back("LL");
//	names.push_back("JavaScript");
//	names.push_back("HTML");
//	names.push_back("Basic");
//	names.push_back("C");
//	names.push_back("PHP");
//	names.push_back("Matcad");
//	names.push_back("Coomir");
//	names.push_back("Kotlin");
//	names.push_back("Bash");
//	names.push_back("Lua");
//	names.push_back("PowerShell");
//	names.push_back("Rust");
//	names.push_back("TypeScript");
//	names.push_back("Scilab");
//	names.push_back("Sed");
//	names.push_back("Maple");
//	names.push_back("Groovy");
//	names.push_back("Dart");
//	names.push_back("Haskell");
//	names.push_back("Perl");
//	names.push_back("Autolt");
//	names.push_back("Make");
//	names.push_back("Pawn");
//	names.push_back("Julia");
//	names.push_back("Elixir");
//	names.push_back("Maxima");
//
//
//
//}

Delivery& DeliGenerator::startChain() const {
	

	Delivery* delivery = new Delivery;
	createData(*delivery);

	return *delivery;
}

Delivery& DeliGenerator::continueChain(const std::string last_dep_point) const {

	Delivery* delivery = new Delivery;
	createData(*delivery, last_dep_point);

	return *delivery;
}

void DeliGenerator::createData(Delivery& delivery, std::string last_dep_point) const {
	std::random_device rd;
	std::mt19937 gen(rd());
	float random_float = 0.0;
	unsigned int random_number = 0;

	//////////////////////////////////////NAME///////////////////////////////////////
	random_number = gen() % names.size();
	std::vector<std::string> not_const_vec = const_cast<std::vector<std::string>&>(names);
	delivery.name = &not_const_vec[random_number];

	//////////////////////////////////////CONTENT///////////////////////////////////////

	random_number = gen() % contents.size();
	not_const_vec = const_cast<std::vector<std::string>&>(contents);
	delivery.content = &not_const_vec[random_number];

	//////////////////////////////////////WEIGHT///////////////////////////////////////

	random_float = float(gen()) / float(rand()) / 10000;
	delivery.weight = random_float;

	//////////////////////////////////////PRICE///////////////////////////////////////

	random_float = float(gen()) / float(rand()) / 1000;
	delivery.price = random_float;

	//////////////////////////////////////SENDER///////////////////////////////////////

	not_const_vec = const_cast<std::vector<std::string>&>(countries);
	if (last_dep_point.empty()) { //start chain case
		random_number = gen() % countries.size();
		delivery.sender = &not_const_vec[random_number];
	}
	else {
		delivery.sender = &last_dep_point;
	}

	//////////////////////////////////////DEPARTURE_POINT///////////////////////////////////////

	random_number = gen() % countries.size();
	delivery.departure_point = &not_const_vec[random_number];
	
	//////////////////////////////////////NAME///////////////////////////////////////



}

std::list<Delivery*>& DeliGenerator::generateData() const
{
	

	/*unsigned int price;
	std::string price_str;

	unsigned int weight;
	std::string weight_str;

	unsigned int deliver_price;
	std::string deliver_price_str;

	unsigned int chain_size = 1;
	chain_size = gen() % 10 + 1;
	std::string last_depart_point = "";*/
	std::random_device rd;
	std::mt19937 gen(rd());
	unsigned int chain_size = 1;
	chain_size = gen() % 10 + 1;
	std::list<Delivery*>* delivery_chain = new std::list<Delivery*>;
	
	delivery_chain->push_back(&startChain());
	for (int i = 0; i < chain_size - 1; i++) {
		
		delivery_chain->push_back(&continueChain(*(delivery_chain->front()->departure_point)));
	}

	return *delivery_chain;






	/*std::cout << yellow << names.size() << white << std::endl;
	for (auto name_in_vector : names) {
		std::cout << purple << name_in_vector << blue << " " << name_in_vector.size() << white <<std::endl;
	}

	std::cout << yellow << countries.size() << white << std::endl;
	for (auto country : countries) {
		std::cout << green << country << blue << " " << country.size() << white << std::endl;
	}

	std::cout << yellow << contents.size() << white << std::endl;
	for (auto content : contents) {
		std::cout << azure << content << blue << " " << content.size() << white << std::endl;
	}

	std::cout << yellow << companies.size() << white << std::endl;
	for (auto company : companies) {
		std::cout << pink << company << blue << " " << company.size() << white << std::endl;
	}*/
	//for (int i = 0; i < 100; i++)
	//{
	//	price = gen() %  1000000;// % 100000;
	//	price_str = std::to_string(price);
	//	
	//	std::cout << green << price_str << blue << " " << price_str.size() << white << std::endl;
	//	
	//}

	//for (int i = 0; i < 100; i++)
	//{
	//	weight = gen() % 1000;// % 100000;
	//	weight_str = std::to_string(weight);
	//	std::cout << azure << weight_str << blue << " " << weight_str.size() << white << std::endl;
	//}
	//std::list<Delivery*>* dels = new std::list<Delivery*>;
	//return dels;
	
}