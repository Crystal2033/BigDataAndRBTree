#pragma once
class DataPool {
public:
	DataPool() = default;
	~DataPool() = default;
	std::vector<std::string> names{ "Cyber", "Java", "C++", "Python", "Pascal", "Ruby", "Scratch",
	"D", "R", "SQL", "MicrosoftAccept", "Joy", "Haskel", "Prolog", "ML", "Lisp", "Mercury", "Unlambda",
	"Agba", "Forth", "Coq", "Refile", "Parsec", "LL", "JavaScript", "HTML", "Basic", "C",
	"PHP", "Matcad", "Coomir", "Kotlin", "Bash", "Lua", "PowerShell", "Rust", "TypeScript", "Scilab",
	"Sed", "Maple", "Groovy", "Dart", "Haskell", "Perl", "Autolt", "Make", "Pawn", "Julia", "Elixir", "Maxima" };
	std::vector<std::string> countries{ "Moldovia", "Russia", "USA", "Canada", "Baku", "Albania",
	"Angola", "Argentina", "Belgia", "Brazilia", "Bahrain", "Denmark", "Finland", "Germany", "Ghana",
	"Egypt", "Haity", "Iran", "Iraq", "Japan", "Kenya", "Lybia", "Oman", "Ukraine", "Malta", "Romania",
	"Uganda", "India", "Iceland", "France", "Italy", "Estonia", "Greece", "Chile", "Andora", "Armenia"
	"Fiji", "Laos", "Netherlands", "Nepal", "Kuwait", "Kazakhstan", "Palau", "Peru", "Portugal", "Poland",
	"Togo", "Tongo", "Tuvalu", "Uruguay", "Yemen" };
	std::vector<std::string> contents{ "Adobe", "Flash", "Develop", "IntelliJ", "PowerFlasher", "Eclipse",
	"GNATStudio", "SlickEdit", "Fresh", "SASM", "BasicAndroid", "Gambas", "SmallBasic", "Xojo", "MonoDevelop",
	"SharpDevelop", "AqulaSoft", "Anjuta", "Bulder", "AbstractFactory", "FactoryMethod", "CodeBlocks", "CodeLite",
	"Geany", "CLion", "LabWindows", "Oracle", "XCode", "OpenWatcom", "NetBeans", "VSCode", "DevC++", "QTcreator",
	"SLIME", "Eiffel", "Plato", "BlueJ", "DrJava", "Servoy", "JCreator", "Atom", "Emacs", "Delphi", "MSEide",
	"Padre", "Eric", "PyCharm", "PIDA", "Spyder", "Thorny" };
	std::vector<std::string> companies{ "Calera", "Chrysler", "Cigna", "CNN", "Tomcat", "Ford", "Peugeot",
	"Mercedes", "Opel", "Nissan", "Porsche", "Clarion", "Coleco", "Fanta", "CocaCola", "Colt", "Deagle",
	"Daewoo", "Datsun", "Dell", "NASA", "EMI", "Lada", "Zeus", "Fiat", "Glaxo", "Google", "Haribo", "SecretServices",
	"Hitachi", "HTC", "Apple", "Samsung", "Intel", "Kesko", "Lukoil", "MineralWater", "Mazda", "Haval", "BMW",
	"Toyota", "LandRover", "Honda", "Lexus", "Fiat", "Suzuki", "KIA", "SsangYong", "Maserati", "Gaz" };
	std::vector<std::string> transport_types{ "Car", "Plane", "Helicopter", "Rocket", "Van", "Lorry",
	"Boat", "Tractor", "MotorBike", "Ship" };
};