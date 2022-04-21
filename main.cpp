#include"Colours.h"
#include "RedBlackTree.h"
#include <chrono>
#include <map>
#include "Queue.h"
#include "Factory.h"
//
int main(int argc, char* argv[])
{
	
	Comparator<int>* comparator = new ComparatorInt(INCREASE);
	try
	{
		RedBlackTree<int, Delivery*>* tree = new RedBlackTree<int, Delivery*>(comparator);
		InterfaceFactory* factory = new DeliGeneratorFactory;
		InterfaceGenerator* generator = factory->createGenerator();
		std::list<Delivery*>* deliveries;
		deliveries = &generator->generateData();
		int counter = 0;
		//FourInts* my_int = new FourInts;
		/*while (1)
		{
			try
			{
				FourInts* my_int = new FourInts;
				tree->add(counter, *my_int);
				counter++;
			}
			catch (std::bad_alloc)
			{
				std::cout << red << counter << white << std::endl;
			}
		}*/
		

		auto begin = std::chrono::steady_clock::now();

		auto end = std::chrono::steady_clock::now();
		auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
		std::cout << yellow << "The time: " << cyan << elapsed_ms.count() << yellow << " ms" << white << std::endl;
		//tree->infix_stepover_tree(print_tree);
	}
	catch (KeyNotFoundException<int>& err)
	{
		std::cout << red << err.what() << "Key value: " << yellow << err.get_error_key() << white << std::endl;
	}
	catch (KeyAlreadyExistsException<int>& err)
	{
		std::cout << red << err.what() << "Key value: " << yellow << err.get_error_key() << white << std::endl;
	}
	return 0;
}