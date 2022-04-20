#pragma once
#include "Delivery.h"
#include <list>
class InterfaceGenerator {
public:
	virtual std::list<Delivery*>* generateData() const = 0;
	virtual ~InterfaceGenerator() = default;
};

class DeliGenerator : public InterfaceGenerator {
public:
	std::list<Delivery*>* generateData() const override;
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
	DeliGenerator() = default;
	~DeliGenerator() = default;
};

std::list<Delivery*>* DeliGenerator::generateData() const
{
	std::cout << yellow << names.size() << white << std::endl;
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
	
	//Delivery* dels = new Delivery;
	std::list<Delivery*>* my_list = new std::list<Delivery*>;
	return my_list;
}