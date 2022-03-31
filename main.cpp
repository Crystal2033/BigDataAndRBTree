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

		tree->add(-100, "asdasd");
		tree->add(234, "asdadasd");
		tree->add(340, "asdasdads");
		tree->add(520, "Leasdasdasdna");
		tree->add(10, "asdasdasd");
		tree->infix_stepover_tree(print_tree);
		std::cout << green << "Hello world!" << white << std::endl;
	}
	catch (KeyNotFoundException<int>& err)
	{
		std::cout << red << err.what() << "Key value: " << yellow << err.get_error_key() << white << std::endl;
	}
	catch (KeyAlreadyExistsException<int>& err)
	{
		std::cout << red << err.what() << "Key value: " << yellow << err.get_error_key() << white << std::endl;
	}
	catch (ParentNodeNotExistsException& err)
	{
		std::cout << red << err.what() << white << std::endl;
	}
	return 0;
}