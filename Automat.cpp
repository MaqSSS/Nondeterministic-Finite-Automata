#include<iostream>
#include<cstring>
#include<ostream>
#include"Automat.h"

///���� ��������
void open(std::ofstream& out, const char* fileName)
{
	if (!out)
	{
		out.open(fileName, std::ios::in|std::ios::out);
		out.clear();
	}
	out.open(fileName, std::ios::in|std::ios::out);
	std::cout << "Successfully opened " << fileName << std::endl;
}

void close(std::ofstream& out, const char* fileName)
{
	open(out, fileName);
	out.close();
	std::cout << "Successfully closed " << fileName << std::endl;
}

void save(std::ofstream out, const char* fileName)
{
	open(out, fileName);
	std::cout << "Successfully saved " << fileName << std::endl;
}

void saveAs(std::ofstream& out, const char* fileName1, const char* fileName2)
{
	open(out, fileName1);
	std::cout << "Successfully saved as " << fileName2 << std::endl;
}

void help()
{
	std::cout << "The following commands are supported:\n"
		<< "open <file>     opens <file>\n"
		<< "close           closes currently opened file\n"
		<< "save            saves the currently opened file\n"
		<< "saveAs <file1>  saves the currently opened file in <file1>\n"
		<< "help            shows this information\n"
		<< "exit            exist the program\n";
}

void exit()
{
	std::cout << "Exiting the program...\n";
}

///������������
void write(const char* fileName, std::ofstream& out)
{
	out.open(fileName, std::ios::app); /// �������� ���� �� �������� � ���� ��

	if (!out.is_open()) /// ��� ����� �� �� � �������
		std::cerr << "WARNING: Cannot save information in " << fileName << " !\n";

	out << " A = < " << Automat::getSetOfStates << " , " << Automat::getFirstStates << " , " << Automat::getTransitions << " , "
		<< Automat::getFinalStates << " >\n";

	out.close(); /// ��������� �����
}

bool read(std::istream& in)
{
	if (!in)
	{
		std::cerr << "File does not exist or cannot be read!\n";
		return false;
	}

	std::cout <<Automat::getSetOfStates;
	std::cout << Automat::getFirstStates;
	std::cout << Automat::getTransitions;
	std::cout <<Automat::getFinalStates;
	std::cout << Automat::getID;
	return true;
}

///������� �������
void Automat::copy(const Automat& A)
{
	delete[] this->setOfStates;
	this->setOfStates = A.setOfStates;
	delete[] this->firstStates;
	this->firstStates = A.firstStates;
	delete[] this->finalStates;
	this->finalStates = A.finalStates;
	delete[]this->transitions;
	this->transitions = A.transitions;
	///����������������� ����� �� �� ������, ������ � �������� �� ����� �������
}

void Automat::erase()
{
	delete[] this->setOfStates;
	this->setOfStates = nullptr;
}

///������������
Automat::Automat() : setOfStates(nullptr), firstStates(nullptr), finalStates(nullptr), transitions(nullptr), ID(0)
{
	///����������� �� ������������
}

Automat::Automat(int* allStates, int* first, char** transitions, int* final, long id)
{
	///����������� � ���������
	this->setOfStates = allStates;
	this->firstStates = first;
	this->transitions = transitions;
	this->finalStates = final;
	this->ID = id;
}

Automat::Automat(const Automat& other)
{
	///����������� �� ��������
	copy(other);
}

Automat& Automat::operator=(const Automat& other)
{
	///�������� �� �����������
	if (this != &other)
	{
		erase();
		copy(other);
	}
	return *this;
}

Automat::~Automat()
{
	///����������
	erase();
}

///��������� �� ��������
void Automat::setSetOfStates(int* allStates)
{
	this->setOfStates = allStates;
}

void Automat::setFirstStates(int* first)
{
	this->firstStates = first;
}

void Automat::setTransitions(char** transitions)
{
	if (this->transitions == nullptr)
		this->transitions = transitions;
}

void Automat::setFinalStates(int* final)
{
	this->finalStates = final;
}

void Automat::setID(long id)
{
	this->ID = id;
}

///�������� �� ��������
int* Automat::getSetOfStates() const
{
	return this->setOfStates;
}

int* Automat::getFirstStates() const
{
	return this->firstStates;
}

char** Automat::getTransitions() const
{
	return this->transitions;
}

int* Automat::getFinalStates() const
{
	return this->finalStates;
}

long Automat::getID() const
{
	return this->ID;
}

///��������
void Automat::list(std::istream& in)
{
	///������ � ID  �� ������ ��������� ��������
	if (read(in))
	{
		in >> this->ID;
	}
}

void Automat::print() const
{
	///���������� �� ������ ������� � �������
	std::cout << "{ ";
	int n = sizeof(this->getTransitions());
	for (int i = 0; i < n; ++i)
	{
		std::cout << "(" << this->getTransitions()[i][0] << "," << this->getTransitions()[i][1] << "," << this->getTransitions()[i][2] << ") ";
	}
	std::cout << " }\n";
}

void Automat::save(std::ofstream& out, char* filename)
{
	///������� ������� ��� ����
	out.open(filename, std::ios::out);
	out << "A = < " << this->getSetOfStates() << " , "
		<< this->getFirstStates() << " , "
		<< this->getFinalStates() << " , ";
    this->print();

	out.close();
}

bool Automat::empty()
{
	///��������� ���� ����� �� �������� � ������
	bool flag = false;
	int n = sizeof(this->getTransitions());
	for (int i = 0; i < n; ++i)
	{
		if (this->getTransitions()[i][1] == '-')///  -> ��������� �� �������-������
		{
			flag = true;
		}
		else
		{
			flag = false;
		}
	}
	return flag;
}

bool Automat::deterministic()
{
	///��������� ���� ������� � ������������
	bool flag = false;
	if (sizeof(this->getFirstStates()) == 1)
	{
		flag = true;
	}
	else
	{
		flag = false;
	}
	int t = sizeof(this->getTransitions());
	for(int i =  0; i < t; ++i)
    {
        if (this->getTransitions()[i][2] != '-')
	    {
		     flag = true;
	    }
       else
	   {
		    flag = false;
	   }
    }
	if (t <= 1)
	{
		flag = true;
	}
	else
	{
		flag = false;
	}
	return flag;
}

bool Automat::recognize(char* word)
{
	///��������� ���� ������ ���� � � ����� �� ��������
	bool flag = false;
	int w = sizeof(word);
	int n = sizeof(this->getTransitions());
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			if (word[j] == this->getTransitions()[i][1])
			{
				flag = true;
			}
			else
			{
				flag = false;
			}
		}
	}
	return flag;
}

long Automat::Union(const Automat& A)
{
	///���������� �� ��� ��������
	Automat N;
	int f1 = sizeof(this->getFirstStates());
	int f2 = sizeof(A.getFirstStates());
	int f = f1 + f2;
	for(int i = 0; i < f1; ++i)
    {
        N.firstStates[i] = this->getFirstStates()[i];
    }
    for(int j = f1; j < f; ++j)
    {
        for(int k = 0; k < f2; ++k)
        {
            N.firstStates[j] = A.getFirstStates()[k];
        }
    }
    int s1 = sizeof(this->getSetOfStates());
	int s2 = sizeof(A.getSetOfStates());
	int s = s1 + s2;
	for(int i = 0; i < s1; ++i)
    {
        N.setOfStates[i] = this->getSetOfStates()[i];
    }
    for(int j = s1; j < s; ++j)
    {
        for(int k = 0; k < s2; ++k)
        {
            N.setOfStates[j] = A.getSetOfStates()[k];
        }
    }
    int l1 = sizeof(this->getFinalStates());
	int l2 = sizeof(A.getFinalStates());
	int l = l1 + l2;
	for(int i = 0; i < l1; ++i)
    {
        N.finalStates[i] = this->getFinalStates()[i];
    }
    for(int j = l1; j < l; ++j)
    {
        for(int k = 0; k < l2; ++k)
        {
            N.finalStates[j] = A.getFinalStates()[k];
        }
    }
    int t1 = sizeof(this->getTransitions());
	int t2 = sizeof(A.getFirstStates());
	int t = t1 + t2;
	for(int i = 0; i < t1; ++i)
    {
        N.transitions[i] = this->getTransitions()[i];
    }
    for(int j = t1; j < t; ++j)
    {
        for(int k = 0; k < t2; ++k)
        {
            N.transitions[j] = A.getTransitions()[k];
        }
    }
	N.ID = A.getID() + 10;
	return N.ID;
}

long Automat::concat(const Automat& A)
{
	///������������ �� ��� ��������
	Automat N;
	N.firstStates = this->getFirstStates();
	int s1 = sizeof(this->getSetOfStates());
	int s2 = sizeof(A.getSetOfStates());
	int s = s1 + s2;
	for(int i = 0; i < s1; ++i)
    {
        N.setOfStates[i] = this->getSetOfStates()[i];
    }
    for(int j = s1; j < s; ++j)
    {
        for(int k = 0; k < s2; ++k)
        {
            N.setOfStates[j] = A.getSetOfStates()[k];
        }
    }
	N.finalStates = A.getFinalStates();
	int t1 = sizeof(this->getTransitions());
	int t2 = sizeof(A.getTransitions());
	int t = t1 + t2;
	for(int i = 0; i < t1; ++i)
    {
        N.transitions[i] = this->getTransitions()[i];
    }
    for(int j = t1; j < t; ++j)
    {
        for(int k = 0; k < t2; ++k)
        {
            N.transitions[j] = A.getTransitions()[k];
        }
    }
	N.ID = A.getID() + 10;
	return N.ID;
}

long Automat::un()
{
	///������ ��������� ������� �� ������� � ������� ��� �������
	int n = sizeof(this->getTransitions());
	for (int i = 0; i < n; ++i)
	{
		if (this->getTransitions()[i][1] == '-')
			delete[] this->getTransitions()[i];
	}

	Automat N;
	N.setOfStates = this->getSetOfStates();
	N.firstStates = this->getFirstStates();
	N.finalStates = this->getFinalStates();
	N.transitions = this->getTransitions();
	N.ID = this->getID() + 10;
	return N.ID;
}

long Automat::reg(char* regex)
{
	///������� ��� ������� �� ����� ��������� �����
	Automat N;
	int r = sizeof(regex);

	for (int i = 1; i < r; ++i)
	{
	    N.firstStates[0] = 1;
		N.setOfStates[i] = i;
		N.finalStates[0] = r;
	}

	int transitionSize = r - 1;
	for (int i = 0; i < transitionSize; ++i)
	{
		for (int j = 0; j < r - 1; ++j)
		{
			N.transitions[i][0] = j;
			N.transitions[i][1] = regex[j];
			N.transitions[i][2] = j + 1;
		}
	}

	N.ID = this->getID() + 10;
	return N.ID;
}

///�������, ������������ ����� �������
void determinize(const Automat& A)
{
	///���� �� ��� ���� 1 ������� ���������
	int k = sizeof(A.getFirstStates());
	while (k > 1)
	{
		delete A.getFirstStates();
	}

	///�� ������ �� ��� �������-�������
	///-   -> ��������� �� �������-������
	int n = sizeof(A.getTransitions());
	for (int i = 0; i < n; ++i)
	{
		if (A.getTransitions()[i][2] == '-')
		{
			delete[] A.getTransitions()[i];
		}
	}

	///�� ����� ��������� �� ����������� �� �����������, �� ����� ����� �� ��������,
	///���� ���������, ����� �� � ������� � ������� ��������� �� ������ �� ��������� 1
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (sizeof(A.getTransitions()[i][2]) > 1)
			{
				if (A.getTransitions()[i][2] == A.getTransitions()[j][2])
					delete[] A.getTransitions()[j];
			}
		}
	}
}

///��������, �����������, ���� ������ �� ����� ������� � �����
bool isFiniteLanguage(const Automat& A)
{
	int n = sizeof(A.getSetOfStates());
	int m = sizeof(alphabet);
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			if (A.getTransitions()[i][0] >= 1 && A.getTransitions()[i][0] <= n &&
				A.getTransitions()[i][1] == alphabet[j] &&
				A.getTransitions()[i][2] <= n && A.getTransitions()[i][2] >= 1)
				return true;
		}
	}
	return false;
}
