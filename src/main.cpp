#include "translator.h"
#include "ord_arr.h"
#include "avl_tree.h"
#include "address_hash.h"
#include "unord_arr.h"
#include "rb_tree.h"
#include "hash_chain.h"

int main() {
	int choice = startup() - '0';
	std::shared_ptr<BaseTranslator> t;
	switch (choice) {
	case 1:
		t = std::shared_ptr<BaseTranslator>(new Translator<OrderedTable<std::string, Polynom>>());
		break;
	case 2:
		t = std::shared_ptr<BaseTranslator>(new Translator<UnorderedTable<std::string, Polynom>>());
		break;
	case 3:
		t = std::shared_ptr<BaseTranslator>(new Translator<AVLTree<std::string, Polynom>>());
		break;
	case 4:
		t = std::shared_ptr<BaseTranslator>(new Translator<RBTree<std::string, Polynom>>());
		break;
	case 5:
		t = std::shared_ptr<BaseTranslator>(new Translator<AddressHashTable<std::string, Polynom>>());
		break;
	case 6:
		t = std::shared_ptr<BaseTranslator>(new Translator<HashTableChaining<std::string, Polynom>>());
		break;
	default:
		output_line("Default option was chosen: Ordered Table.");
		t = std::shared_ptr<BaseTranslator>(new Translator<OrderedTable<std::string, Polynom>>());
		break;
	}
	output_line("Type \"help\" for more information.");
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while (true)
		t->execute();
}