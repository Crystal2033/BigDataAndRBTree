#include"Colours.h"
#include "RedBlackTree.h"
#include <chrono>
#include "Queue.h"
#include <cctype>
#include "DeliveryManager.h"
#include "Factory.h"
#include "UserFuncsAndCallbacks.h"


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
								chooseOperation();
								choice_number = user_choice(1, 3);
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

