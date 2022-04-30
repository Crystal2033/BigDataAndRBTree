#include"Colours.h"
#include "RedBlackTree.h"
#include <chrono>
#include "Queue.h"
#include <cctype>
#include "DeliveryManager.h"
#include "Factory.h"
#define FLOAT_DATA_START 2
#define FLOAT_DATA_END 6
#define FIRST_STR_DATA_END 3
#define SECOND_STR_DATA_START 5

int main(int argc, char* argv[])
{
	InterfaceFactory<Delivery>* factory = new DeliGeneratorFactory;
	InterfaceGenerator<Delivery>* generator = factory->createGenerator();
	int choice_number;
	try
	{
		greetingsPrint();
		
		chooseCollectionPrint(); //TODO добавить возможность отказаться от генерации данных.
		choice_number = userChoice(1, 2);

		if (choice_number == 1) //Tree case
		{
			std::cout << green << "Red Black tree was chosen." << white << std::endl;
			std::cout << cyan << "You have to choose the comparator by field for your tree (input 1-10):" << white <<  std::endl;
			chooseFieldPrint();
			choice_number = userChoice(1, 10);

			if (choice_number > FLOAT_DATA_START && choice_number < FLOAT_DATA_END) //float comparator
			{
				Comparator<std::pair<float, unsigned int>>* comparator = new ComparatorPairFloat(INCREASE);
				RedBlackTree<std::pair<float, unsigned int>, Delivery*>* tree = new RedBlackTree<std::pair<float, unsigned int>, Delivery*>(comparator);
				DeliveryManager< std::pair<float, unsigned int>, Delivery*> manager(tree, generator);
				manager.workWithUser(choice_number);
				delete tree;
				delete comparator;
			}
			else if(choice_number < FIRST_STR_DATA_END || choice_number > SECOND_STR_DATA_START) //string comparator
			{
				Comparator<std::pair<std::string*, unsigned int>>* comparator = new ComparatorPairStr(INCREASE);
				RedBlackTree<std::pair<std::string*, unsigned int>, Delivery*>* tree = new RedBlackTree<std::pair<std::string*, unsigned int>, Delivery*>(comparator);
				DeliveryManager< std::pair<std::string*, unsigned int>, Delivery*> manager(tree, generator);
				manager.workWithUser(choice_number);
				delete tree;
				delete comparator;
				
			}
				
		}
		else if (choice_number == 2) //Queue case
		{
			std::cout << green << "Queue was chosen." << white << std::endl;
			chooseFieldPrint();
			choice_number = userChoice(1, 10);

		}
			
		delete factory;
		delete generator;
	}

	catch (KeyNotFoundException<std::pair<std::string*, unsigned int>>& err)
	{
		std::cout << red << err.what() << "Key value: " << yellow << *err.get_error_key().first << pink << " Hash: " << err.get_error_key().second << white << std::endl;
	}
	catch (KeyNotFoundException<std::pair<float, unsigned int>>& err)
	{
		std::cout << red << err.what() << "Key value: " << yellow << err.get_error_key().first << pink << " Hash: " << err.get_error_key().second << white << std::endl;
	}
	catch (KeyAlreadyExistsException<std::pair<float, unsigned int>>& err)
	{
		std::cout << red << err.what() << "Key value: " << yellow << err.get_error_key().first << pink << " Hash: " << err.get_error_key().second << white << std::endl;
	}
	catch (KeyAlreadyExistsException<std::pair<std::string*, unsigned int>>& err)
	{
		std::cout << red << err.what() << "Key value: " << yellow << *err.get_error_key().first << pink << " Hash: " << err.get_error_key().second << white << std::endl;
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
	catch (NullException& err)
	{
		std::cout << red << err.what() <<  white << std::endl;
	}
	catch (...)
	{
		std::cout << red << "Unpredictable exception." << white << std::endl;
	}
	return 0;
}

