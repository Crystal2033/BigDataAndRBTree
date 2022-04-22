#include"Colours.h"
#include "RedBlackTree.h"
#include <chrono>
#include <map>
#include "Queue.h"
#include "Factory.h"
#include <cctype>

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

void generate_data_str_cmp(Container<std::string*, Delivery*>* container, const int cmp_choice) {
	InterfaceFactory* factory = new DeliGeneratorFactory;
	InterfaceGenerator* generator = factory->createGenerator();
	std::list<Delivery*>* deliveries;
	

	auto begin = std::chrono::steady_clock::now();

	for (int i = 0; i < 500; i++)
	{
		deliveries = &generator->generateData();

		for (auto delivery : *deliveries) {
			
			switch (cmp_choice)
			{
				case 1: //name
				{
					container->add(delivery->name, delivery);
					break;
				}
				case 2: //content
				{
					container->add(delivery->content, delivery);
					break;
				}
				case 6: //sender
				{
					container->add(delivery->sender, delivery);
					break;
				}
				case 7: //departure point
				{
					container->add(delivery->departure_comp, delivery);
					break;
				}
				case 8: //reciever
				{
					container->add(delivery->reciever, delivery);
					break;
				}
				case 9: //destination point
				{
					container->add(delivery->destination_comp, delivery);
					break;
				}
				case 10: //type of transport
				{
					container->add(delivery->type_of_transport, delivery);
					break;
				}
			}
			
		}
		delete deliveries;
	}

	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	std::cout << blue << "The time of generation: " << cyan << elapsed_ms.count() << blue << " ms" << white << std::endl;
	delete factory;
	delete generator;
}

void generate_data_float_cmp(Container<float, Delivery*>* container, const int cmp_choice) {
	InterfaceFactory* factory = new DeliGeneratorFactory;
	InterfaceGenerator* generator = factory->createGenerator();
	std::list<Delivery*>* deliveries;


	auto begin = std::chrono::steady_clock::now();

	for (int i = 0; i < 500; i++)
	{
		deliveries = &generator->generateData();

		for (auto delivery : *deliveries) {

			switch (cmp_choice)
			{
				case 3: //weight
				{
					container->add(delivery->weight, delivery);
					break;
				}
				case 4: //price
				{
					container->add(delivery->price, delivery);
					break;
				}
				case 5: //delivery price
				{
					container->add(delivery->deliver_price, delivery);
					break;
				}
			}

		}
		delete deliveries;
	}

	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	std::cout << blue << "The time of generation: " << cyan << elapsed_ms.count() << blue << " ms" << white << std::endl;
	delete factory;
	delete generator;
}

int main(int argc, char* argv[])
{
	
	//Comparator<float>* comparator = new ComparatorFloat(INCREASE);
	std::cout << cyan << "Hello, my name is Kulikov Pavel, FIIT, M80-211B-20." << white << std::endl;
	std::cout << cyan << "This is a programm which can store and work with your data (" << green << "add" << cyan << " / "
		      << yellow << "find" << cyan << " / " << red << "delete" << cyan << " / " << blue << "generate" << cyan 
		      << ")." << white << std::endl << std::endl;
	int choice_number;
	try
	{
		while (true)
		{
			std::cout << cyan << "At first you have to choose the type of collection (input 1 or 2): " << std::endl
				      << yellow << "1. Red Black tree." << std::endl << "2. Queue" << white << std::endl << yellow << "> " << white;

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
					std::cout << cyan << "You have to choose the comparator by field for your tree (input 1-10):" << yellow << std::endl;
					std::cout << "1. Name" << std::endl << "2. Content" << std::endl << "3. Weight" << std::endl
						<< "4. Price" << std::endl << "5. Delivery price" << std::endl << "6. Sender (from country)" << std::endl
						<< "7. Departure point (by company)" << std::endl << "8. Reciever (to country)" << std::endl
						<< "9. Destination point (for company)" << std::endl << "10. Type of transport" << std::endl << "> " << white;
					choice_number = user_choice(1, 10);
					if (choice_number == -1)
					{
						continue;
					}
					else
					{
						if (choice_number > 2 || choice_number < 6) //float comparator
						{
							Comparator<float>* comparator = new ComparatorFloat(INCREASE);
							RedBlackTree<float, Delivery*>* tree = new RedBlackTree<float, Delivery*>(comparator);
							generate_data_float_cmp(tree, choice_number);
							delete tree;
							delete comparator;
						}
						else //string comparator
						{
							Comparator<std::string>* comparator = new ComparatorStr(INCREASE);
							RedBlackTree<std::string*, Delivery*>* tree = new RedBlackTree<std::string*, Delivery*>(comparator);
							generate_data_str_cmp(tree, choice_number);
							delete tree;
							delete comparator;
						}
						
					}
				}
				
				
			}
			else if (choice_number == 2) //Queue case
			{

			}
			while (true)
			{
				return 0;
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