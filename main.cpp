#include"Colours.h"
#include "RedBlackTree.h"
int main(int argc, char* argv[])
{
	Comparator<int>* comparator = new ComparatorInt(INCREASE);
	try
	{
		RedBlackTree<int, std::string>* tree = new RedBlackTree<int, std::string>(comparator);
		/*for(int i = 11; i != -1; i--)
		{
			tree->add(i, " ");
		}*/
		tree->add(150, "Pasha");
		tree->add(200, "Kesha");
		tree->add(250, "Lesha");
		tree->add(100, "Lena");
		tree->add(300, "Sema");

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
		//std::cout << cyan << tree->find(80) << white <<std::endl;
		/*std::cout << pink << "DELETE:" << white << std::endl;
		tree->remove(150);*/
		//tree->infix_stepover_tree(print_tree);


		std::cout << pink << "DELETE:" << white << std::endl;
		tree->remove(100);
		tree->infix_stepover_tree(print_tree);
		std::cout << pink << "DELETE:" << white << std::endl;
		tree->remove(200);
		tree->infix_stepover_tree(print_tree);
		std::cout << pink << "DELETE:" << white << std::endl;
		tree->remove(150);
		tree->infix_stepover_tree(print_tree);
		std::cout << pink << "DELETE:" << white << std::endl;
		tree->remove(300);
		tree->infix_stepover_tree(print_tree);
		std::cout << pink << "DELETE:" << white << std::endl;
		tree->remove(500);
		tree->infix_stepover_tree(print_tree);
		std::cout << pink << "DELETE:" << white << std::endl;
		tree->remove(520);
		tree->infix_stepover_tree(print_tree);
		std::cout << pink << "DELETE:" << white << std::endl;
		tree->remove(10);
		tree->infix_stepover_tree(print_tree);
		std::cout << pink << "DELETE:" << white << std::endl;
		tree->remove(234);
		tree->infix_stepover_tree(print_tree);
		std::cout << pink << "DELETE:" << white << std::endl;
		tree->remove(170);
		tree->infix_stepover_tree(print_tree);
		std::cout << pink << "DELETE:" << white << std::endl;
		tree->remove(12);
		tree->infix_stepover_tree(print_tree);
		std::cout << pink << "DELETE:" << white << std::endl;
		tree->remove(250);
		tree->infix_stepover_tree(print_tree);
		std::cout << pink << "DELETE:" << white << std::endl;
		tree->remove(75);
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