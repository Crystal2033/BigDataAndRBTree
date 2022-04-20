#include"Colours.h"
#include "RedBlackTree.h"
#include <chrono>
#include <map>
#include "Queue.h"
#include "Factory.h"

int main(int argc, char* argv[])
{
	
	Comparator<int>* comparator = new ComparatorInt(INCREASE);
	try
	{
		RedBlackTree<int, std::string>* tree = new RedBlackTree<int, std::string>(comparator);
		InterfaceFactory* factory = new DeliGeneratorFactory;
		InterfaceGenerator* generator = factory->createGenerator();
		

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