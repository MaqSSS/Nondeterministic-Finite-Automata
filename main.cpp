#include"Automat.cpp"

void test1()
{
	Automat M;
	M.print();
	Automat M2;
	M2 = M;
	M2.setID(324324);
	std::cout << M.empty() << std::endl;
	std::cout << M.deterministic() << std::endl;
	M2.print();
}

void test2()
{
	Automat K;
	K.print();
	Automat K2 = K;
	K2.setID(3435);
	K2.print();
	std::cout << K.Union(K2) << std::endl;
	std::cout << K.concat(K2) << std::endl;
	K.print();
}

int main()
{
	test1();

	test2();

	///switch - case за конзолните операции
	std::cout << "Enter command (open, close, save saveas, help exit) :\n";
	int cmd_num;
	char* file;
	std::cin >> cmd_num;
	std::cout << "Path...\n";
	std::cin >> file;
	//switch (cmd_num)
	//{
	//case 1 : open(file);
	//case 2 : close(file);
	//case 3: save(file);
	//case 4 : saveAs(file);
	//case 5 : help();
	//case 6 : exit();
	//default:
	//	"WRONG COMMAND!";
	//}
	return 0;
}
