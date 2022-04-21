#include"Colours.h"
#include "RedBlackTree.h"
#include <chrono>
#include <map>
#include "Queue.h"
#include "Factory.h"

int main(int argc, char* argv[])
{
	InterfaceFactory* factory = new DeliGeneratorFactory;
	InterfaceGenerator* generator = factory->createGenerator();
	Comparator<std::string>* comparator = new ComparatorStr(INCREASE);
	auto begin = std::chrono::steady_clock::now();
	try
	{
		RedBlackTree<std::string, Delivery*>* tree = new RedBlackTree<std::string, Delivery*>(comparator);
		
		std::list<Delivery*>* deliveries;
		//auto begin = std::chrono::steady_clock::now();
		//std::cout << azure << "================================================================" << std::endl;
		for (int i = 0; i < 50; i++)
		{
			deliveries = &generator->generateData();
			/*for (auto delivery : *deliveries) {
				std::cout << *delivery << std::endl;
			}*/
			//std::cout << azure << "================================================================" << std::endl;
			for (auto delivery : *deliveries) {
				tree->add(*delivery->name, delivery);
			}
			delete deliveries;
		}
		tree->infix_stepover_tree(print_tree_for_delivery);
		//std::list<Delivery**> found_data = tree->find("PASCAl");
		/*for (auto delivery : found_data) {
				std::cout << *delivery << std::endl;
			}*/
		auto end = std::chrono::steady_clock::now();
		std::cout << azure << generator->get_generated_value() << white << std::endl;
		auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
		std::cout << yellow << "The time: " << cyan << elapsed_ms.count() << yellow << " ms" << white << std::endl;
		//tree->infix_stepover_tree(print_tree);
	}
	catch (KeyNotFoundException<std::string>& err)
	{
		std::cout << red << err.what() << "Key value: " << yellow << err.get_error_key() << white << std::endl;
	}
	catch (std::bad_alloc)
	{
		std::cout << red << "Bad alloc exception." << white << std::endl;
		//std::cout << yellow << "Critical data is: " << generator->get_generated_value() <<  blue << std::endl;
		auto end = std::chrono::steady_clock::now();
		//std::cout << azure << generator->get_generated_value() << white << std::endl;
		auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	}
	catch (DeliveryNullException& err)
	{
		std::cout << red << err.what() << white << std::endl;
	}
	catch (KeyAlreadyExistsException<int>& err)
	{
		std::cout << red << err.what() << "Key value: " << yellow << err.get_error_key() << white << std::endl;
	}
	return 0;
}