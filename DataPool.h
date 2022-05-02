#pragma once
class DataPool {
public:
	DataPool() = default;
	~DataPool() = default;
	std::list<std::string> names{ "Cyber", "Java", "C++", "Python", "Pascal", "Ruby", "Scratch",
	"D", "R", "SQL", "MicrosoftAccept", "Joy", "Haskel", "Prolog", "ML", "Lisp", "Mercury", "Unlambda",
	"Agba", "Forth", "Coq", "Refile", "Parsec", "LL", "JavaScript", "HTML", "Basic", "C",
	"PHP", "Matcad", "Coomir", "Kotlin", "Bash", "Lua", "PowerShell", "Rust", "TypeScript", "Scilab",
	"Sed", "Maple", "Groovy", "Dart", "Haskell", "Perl", "Autolt", "Make", "Pawn", "Julia", "Elixir", "Maxima" };
	std::list<std::string> countries{ "Moldovia", "Russia", "USA", "Canada", "Baku", "Albania",
	"Angola", "Argentina", "Belgia", "Brazilia", "Bahrain", "Denmark", "Finland", "Germany", "Ghana",
	"Egypt", "Haity", "Iran", "Iraq", "Japan", "Kenya", "Lybia", "Oman", "Ukraine", "Malta", "Romania",
	"Uganda", "India", "Iceland", "France", "Italy", "Estonia", "Greece", "Chile", "Andora", "Armenia"
	"Fiji", "Laos", "Netherlands", "Nepal", "Kuwait", "Kazakhstan", "Palau", "Peru", "Portugal", "Poland",
	"Togo", "Tongo", "Tuvalu", "Uruguay", "Yemen" };
	std::list<std::string> contents{ "Adobe", "Flash", "Develop", "IntelliJ", "PowerFlasher", "Eclipse",
	"GNATStudio", "SlickEdit", "Fresh", "SASM", "BasicAndroid", "Gambas", "SmallBasic", "Xojo", "MonoDevelop",
	"SharpDevelop", "AqulaSoft", "Anjuta", "Bulder", "AbstractFactory", "FactoryMethod", "CodeBlocks", "CodeLite",
	"Geany", "CLion", "LabWindows", "Oracle", "XCode", "OpenWatcom", "NetBeans", "VSCode", "DevC++", "QTcreator",
	"SLIME", "Eiffel", "Plato", "BlueJ", "DrJava", "Servoy", "JCreator", "Atom", "Emacs", "Delphi", "MSEide",
	"Padre", "Eric", "PyCharm", "PIDA", "Spyder", "Thorny" };
	std::list<std::string> companies{ "Calera", "Chrysler", "Cigna", "CNN", "Tomcat", "Ford", "Peugeot",
	"Mercedes", "Opel", "Nissan", "Porsche", "Clarion", "Coleco", "Fanta", "CocaCola", "Colt", "Deagle",
	"Daewoo", "Datsun", "Dell", "NASA", "EMI", "Lada", "Zeus", "Fiat", "Glaxo", "Google", "Haribo", "SecretServices",
	"Hitachi", "HTC", "Apple", "Samsung", "Intel", "Kesko", "Lukoil", "MineralWater", "Mazda", "Haval", "BMW",
	"Toyota", "LandRover", "Honda", "Lexus", "Fiat", "Suzuki", "KIA", "SsangYong", "Maserati", "Gaz" };
	std::list<std::string> transport_types{ "Car", "Plane", "Helicopter", "Rocket", "Van", "Lorry",
	"Boat", "Tractor", "MotorBike", "Ship" };
	std::list<std::string> time{"11:12:2002", "02:20:2015", "05:02:2000", "15:07::2012", "30:01:2010", "25:10:1990",
	"02:11:2000", "14:04:2003", "11:10:2001", "27:09:2019", "31:03:2011", "01:01:2020", "12:12:2012", "24:10:2000",
	"17:05:1999", "22:09:2020", "19:07:2013", "14:06:2016", "10:04:2015", "06:09:2009", "17:08:2002", "12:10:2010",
	"03:09:2010", "05:11:2000", "15:01:2012", "18:08:2013", "19:01:1998", "13:11:2011", "13:02:2002", "10:12:2010",
	"15:01:2008", "08:02:2002", "12:11:2015", "13:11:2010", "15:03:2007", "10:01:2003", "13:11:2001", "18:10:2010",
	"21:10:2000", "18:10:2012", "14:10:2010", "11:01:2021", "03:03:2011", "16:08:2001", "18:03:2012", "09:09:1998",
	"10:11:2009", "17:03:2012", "09:02:2010", "12:04:2012", "18:02:2005", "17:04:2000", "15:01:2017", "08:01:2012"};
};
