#include"Colours.h"
#include "RedBlackTree.h"
#include <chrono>
#include "Queue.h"
#include <cctype>
#include "DeliveryManager.h"
#include "Factory.h"

void print_tree_for_deliv_pair_str(const std::pair<std::string*, unsigned int>& key, Delivery* const& data, int depth = 0);
void print_tree_for_deliv_pair_float(const std::pair<float, unsigned int>& key, Delivery* const& data, int depth = 0);

int user_choice(const int left_edge, const int right_edge)
{
	std::string choice_str;
	int choice_number;

	choice_str.clear();
	std::cin >> choice_str;
	choice_number = atoi(choice_str.c_str());

	if (choice_number < left_edge || choice_number > right_edge) {
		std::cout << red << "InputValueError: You have to choose value from <" << yellow << left_edge << red << "> to <" << yellow << right_edge
			<< red << ">." << std::endl;
		return -1;
	}
	return choice_number;
}

void chooseComparator()
{
	std::cout << cyan << "You have to choose the comparator by field for your tree (input 1-10):" << yellow << std::endl;
	std::cout << "1. Name" << std::endl << "2. Content" << std::endl << "3. Weight" << std::endl
		      << "4. Price" << std::endl << "5. Delivery price" << std::endl << "6. Sender (from country)" << std::endl
		      << "7. Departure point (by company)" << std::endl << "8. Reciever (to country)" << std::endl
		      << "9. Destination point (for company)" << std::endl << "10. Type of transport" << std::endl << "> " << white;
}
void greetings() {
	std::cout << cyan << "Hello, my name is Kulikov Pavel, FIIT, M80-211B-20." << white << std::endl;
	std::cout << cyan << "This is a programm which can store and work with your data (" << green << "add" << cyan << " / "
		      << yellow << "find" << cyan << " / " << red << "delete" << cyan << " / " << blue << "generate" << cyan
		      << ")." << white << std::endl << std::endl;
}

void chooseCollection() {
	std::cout << cyan << "At first you have to choose the type of collection (input 1 or 2): " << std::endl
		      << yellow << "1. Red Black tree." << std::endl << "2. Queue" << white << std::endl << yellow << "> " << white;
}

void chooseOperation()
{
	std::cout << cyan << "You have to choose one operation, which works with your comparator key:" << std::endl
			  << green << "1. Add data." << std::endl << yellow << "2. Find data."
			  << red << "3. Delete data." << white << std::endl;
}


int main(int argc, char* argv[])
{
	InterfaceFactory* factory = new DeliGeneratorFactory;
	InterfaceGenerator* generator = factory->createGenerator();
	int choice_number;
	try
	{
		greetings();
		
		while (true)
		{
			
			chooseCollection();
			choice_number = user_choice(1, 2);
			if (choice_number == -1)
			{
				continue;
			}

			if (choice_number == 1) //Tree case
			{
				std::cout << green << "Red Black tree was chosen." << white << std::endl;
				while (true)
				{
					chooseComparator();
					choice_number = user_choice(1, 10);
					if (choice_number == -1)
					{
						continue;
					}
					else
					{
						if (choice_number > 2 && choice_number < 6) //float comparator
						{
							Comparator<std::pair<float, unsigned int>>* comparator = new ComparatorPairFloat(INCREASE);
							RedBlackTree<std::pair<float, unsigned int>, Delivery*>* tree = new RedBlackTree<std::pair<float, unsigned int>, Delivery*>(comparator);
							DeliveryManager< std::pair<float, unsigned int>, Delivery*> manager(tree, generator);
							std::cout << cyan << "To start " << blue << "generating " << cyan << "data press any keyboard button." << white << std::endl;
							getchar();
							getchar();
							manager.generateData(choice_number);
							manager.PrintData(print_tree_for_deliv_pair_float);
							while (true)
							{
								//todo find, add, remove or exit

								break;
							}
							delete tree;
							delete comparator;
							return 0;
						}
						else if(choice_number < 3 || choice_number > 5) //string comparator
						{
							Comparator<std::pair<std::string*, unsigned int>>* comparator = new ComparatorPairStr(INCREASE);
							RedBlackTree<std::pair<std::string*, unsigned int>, Delivery*>* tree = new RedBlackTree<std::pair<std::string*, unsigned int>, Delivery*>(comparator);
							DeliveryManager< std::pair<std::string*, unsigned int>, Delivery*> manager(tree, generator);

							std::cout << cyan << "To start " << blue << "generating " << cyan << "data press any keyboard button." << white << std::endl;
							getchar();
							getchar();
							
							manager.generateData(choice_number);
							manager.PrintData(print_tree_for_deliv_pair_str);
							while (true)
							{
								//todo find, add, remove

								break;
							}
							delete tree;
							delete comparator;
							return 0;
						}
						
					}
				}
				
				
			}
			else if (choice_number == 2) //Queue case
			{
				std::cout << green << "Queue was chosen." << white << std::endl;
				while (true)
				{
					return 0;
				}
			}
			
			
		}
		
		

	}

	catch (KeyNotFoundException<std::string>& err)
	{
		std::cout << red << err.what() << "Key value: " << yellow << err.get_error_key() << white << std::endl;
	}
	catch (KeyNotFoundException<float>& err)
	{
		std::cout << red << err.what() << "Key value: " << yellow << err.get_error_key() << white << std::endl;
	}
	catch (std::bad_alloc)
	{
		std::cout << red << "Bad alloc exception." << white << std::endl;
	}
	catch (DeliveryNullException& err)
	{
		std::cout << red << err.what() << white << std::endl;
	}
	catch (ComparatorNullException& err)
	{
		std::cout << red << err.what() << white << std::endl;
	}
	catch (KeyAlreadyExistsException<std::string>& err)
	{
		std::cout << red << err.what() << "Key value: " << yellow << err.get_error_key() << white << std::endl;
	}
	catch (...)
	{
		std::cout << red << "Unpredictable exception." << white << std::endl;

	}
	return 0;
}

void print_tree_for_deliv_pair_str(const std::pair<std::string*, unsigned int>& key, Delivery* const& data, int depth)
{
	if (depth == 0)
	{
		std::cout << red << "ROOT: " << white << " ";
	}
	else
	{
		std::cout << azure << "Depth: " << depth << "." << white << " " << std::endl;
	}
	std::cout << red << "Key: " << green << *key.first << white << " " << red << "Hash: " << pink << key.second << white << " " << std::endl;
	std::cout << blue << "Data: " << std::endl << *data << white << std::endl;
}

void print_tree_for_deliv_pair_float(const std::pair<float, unsigned int>& key, Delivery* const& data, int depth)
{
	if (depth == 0)
	{
		std::cout << red << "ROOT: " << white << " ";
	}
	else
	{
		std::cout << azure << "Depth: " << depth << "." << white << " " << std::endl;
	}
	std::cout << red << "Key: " << green << key.first << white << " " << red << "Hash: " << pink <<key.second << white << " " << std::endl;
	std::cout << blue << "Data: " << std::endl << *data << white << std::endl;
}