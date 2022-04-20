#pragma once
#include "Delivery.h"
#include <list>
#include <random>
#include <string>
class InterfaceGenerator {
public:
	virtual void generateData(const std::string&) const = 0;
	virtual ~InterfaceGenerator() = default;
};

class DeliGenerator : public InterfaceGenerator {
public:
	void generateData(const std::string&) const override;
	const std::vector<std::string> names {"Cyber", "Java", "C++", "Python", "Pascal", "Ruby", "Scratch",
	"D", "R", "SQL", "MicrosoftAccept", "Joy", "Haskel", "Prolog", "ML", "Lisp", "Mercury", "Unlambda",
	"Agba", "Forth", "Coq", "Refile", "Parsec", "LL", "JavaScript", "HTML", "Basic", "C", 
	"PHP", "Matcad", "Coomir", "Kotlin", "Bash", "Lua", "PowerShell", "Rust", "TypeScript", "Scilab",
	"Sed", "Maple", "Groovy", "Dart", "Haskell", "Perl", "Autolt", "Make", "Pawn", "Julia", "Elixir", "Maxima"};
	const std::vector<std::string> countries {"Moldovia", "Russia", "USA", "Canada", "Baku", "Albania",
	"Angola", "Argentina", "Belgia", "Brazilia", "Bahrain", "Denmark", "Finland", "Germany", "Ghana", 
	"Egypt", "Haity", "Iran", "Iraq", "Japan", "Kenya", "Lybia", "Oman", "Ukraine", "Malta", "Romania", 
	"Uganda", "India", "Iceland", "France", "Italy", "Estonia", "Greece", "Chile", "Andora", "Armenia"
	"Fiji", "Laos", "Netherlands", "Nepal", "Kuwait", "Kazakhstan", "Palau", "Peru", "Portugal", "Poland", 
	"Togo", "Tongo", "Tuvalu", "Uruguay", "Yemen"};
	const std::vector<std::string> contents { "Adobe", "Flash", "Develop", "IntelliJ", "PowerFlasher", "Eclipse",
	"GNATStudio", "SlickEdit", "Fresh", "SASM", "BasicAndroid", "Gambas", "SmallBasic", "Xojo", "MonoDevelop",
	"SharpDevelop", "AqulaSoft", "Anjuta", "Bulder", "AbstractFactory", "FactoryMethod", "CodeBlocks", "CodeLite",
	"Geany", "CLion", "LabWindows", "Oracle", "XCode", "OpenWatcom", "NetBeans", "VSCode", "DevC++", "QTcreator", 
	"SLIME", "Eiffel", "Plato", "BlueJ", "DrJava", "Servoy", "JCreator", "Atom", "Emacs", "Delphi", "MSEide", 
	"Padre", "Eric", "PyCharm", "PIDA", "Spyder", "Thorny"};
	const std::vector<std::string> companies { "Calera", "Chrysler", "Cigna", "CNN", "Tomcat", "Ford", "Peugeot",
	"Mercedes", "Opel", "Nissan", "Porsche", "Clarion", "Coleco", "Fanta", "CocaCola", "Colt", "Deagle",
	"Daewoo", "Datsun", "Dell", "NASA", "EMI", "Lada", "Zeus", "Fiat", "Glaxo", "Google", "Haribo", "SecretServices",
	"Hitachi", "HTC", "Apple", "Samsung", "Intel", "Kesko", "Lukoil", "MineralWater", "Mazda", "Haval", "BMW", 
	"Toyota", "LandRover", "Honda", "Lexus", "Fiat", "Suzuki", "KIA", "SsangYong", "Maserati", "Gaz"};
	const std::vector<std::string> transport_types {"Car", "Plane", "Helicopter", "Rocket", "Van", "Lorry", 
	"Boat", "Tractor", "MotorBike", "Ship"};
	DeliGenerator() = default;
	~DeliGenerator() = default;
};

void DeliGenerator::generateData(const std::string& file_name) const
{
	std::random_device rd;   
	std::mt19937 gen(rd());

	unsigned int price;
	std::string price_str;

	unsigned int weight;
	std::string weight_str;

	unsigned int deliver_price;
	std::string deliver_price_str;


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
	for (int i = 0; i < 100; i++)
	{
		price = gen() %  1000000;// % 100000;
		price_str = std::to_string(price);
		
		std::cout << green << price_str << blue << " " << price_str.size() << white << std::endl;
		
	}

	for (int i = 0; i < 100; i++)
	{
		weight = gen() % 1000;// % 100000;
		weight_str = std::to_string(weight);
		std::cout << azure << weight_str << blue << " " << weight_str.size() << white << std::endl;
	}
	
	
}