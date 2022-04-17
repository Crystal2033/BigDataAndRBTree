#include"Colours.h"
#include "RedBlackTree.h"
#include <chrono>
#include <map>
int main(int argc, char* argv[])
{
	Comparator<int>* comparator = new ComparatorInt(INCREASE);
	try
	{
		

		
		std::map<int, std::string> map;
		RedBlackTree<int, std::string>* tree = new RedBlackTree<int, std::string>(comparator);
		
		//for (int i = 0; i <= 500; i++)
		//{
		//	//tree->infix_stepover_tree(print_tree);
		//	//std::cout << green << "ADD:" << white << std::endl;
		//	tree->add(i, " ");
		//	//map.insert(std::make_pair(i, " "));
		//}

		//for (int i = 450; i != 425; i--)
		//{
		//	//tree->infix_stepover_tree(print_tree);
		//	//std::cout << red << "DELETE:" << white << std::endl;
		//	tree->remove(i);
		//	//map.erase(i);
		//}


		//for (int i = 150; i != 200; i++)
		//{
		//	//tree->infix_stepover_tree(print_tree);
		//	//std::cout << red << "DELETE:" << white << std::endl;
		//	tree->remove(i);
		//	//map.erase(i);
		//}

		//for (int i = 475; i != 500; i++)
		//{
		//	//tree->infix_stepover_tree(print_tree);
		//	//std::cout << red << "DELETE:" << white << std::endl;
		//	tree->remove(i);
		//	//map.erase(i);
		//}

		//std::cout << cyan << "REMAINED:" << white << std::endl;
		

		
		
		tree->add(300, "Sema");
		tree->add(300, "Semen");
		tree->add(250, "Lesha");
		tree->add(200, "Pasha");
		tree->add(150, "Kesha");
		tree->add(100, "Lena");
		

		tree->add(75, "Alfred");
		tree->add(80, "Sergey");
		tree->add(12, "Adam");
		tree->add(170, "Eva");
		tree->add(500, "asdasd");

		tree->add(0, "asdasd");
		tree->add(234, "asdadasd");
		tree->add(340, "asdasdads");
		tree->add(520, "Leasdasdasdna");
		tree->add(10, "asdasdasd");
		tree->infix_stepover_tree(print_tree);
		std::list<std::string> found_data;
		found_data = tree->find(300);
		for (auto data : found_data) {
			std::cout << cyan << data << white << std::endl;
		}
		
		auto begin = std::chrono::steady_clock::now();
		//tree->infix_stepover_tree(print_tree);

		tree->remove(300);
		//tree->infix_stepover_tree(print_tree);
		std::cout << pink << "DELETE:" << white << std::endl;

		
		std::cout << pink << "DELETE:" << white << std::endl;
		tree->remove(150);
		//tree->infix_stepover_tree(print_tree);
		std::cout << pink << "DELETE:" << white << std::endl;
		
		tree->remove(100);
		//tree->infix_stepover_tree(print_tree);
		std::cout << pink << "DELETE:" << white << std::endl;
		tree->remove(250);
		//tree->infix_stepover_tree(print_tree);
		//tree->infix_stepover_tree(print_tree);
		std::cout << pink << "DELETE:" << white << std::endl;
		tree->remove(500);
		//tree->infix_stepover_tree(print_tree);
		std::cout << pink << "DELETE:" << white << std::endl;
		tree->remove(520);
		//tree->infix_stepover_tree(print_tree);
		std::cout << pink << "DELETE:" << white << std::endl;
		tree->remove(10);
		//tree->infix_stepover_tree(print_tree);
		std::cout << pink << "DELETE:" << white << std::endl;
		tree->remove(234);
		//tree->infix_stepover_tree(print_tree);
		std::cout << pink << "DELETE:" << white << std::endl;
		tree->remove(170);
		//tree->infix_stepover_tree(print_tree);
		std::cout << pink << "DELETE:" << white << std::endl;
		tree->remove(12);
		//tree->infix_stepover_tree(print_tree);
		std::cout << pink << "DELETE:" << white << std::endl;
		tree->remove(75);
		
		auto end = std::chrono::steady_clock::now();
		auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
		std::cout << yellow << "The time: " << cyan << elapsed_ms.count() << yellow << " ms" << white << std::endl;
		tree->infix_stepover_tree(print_tree);
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