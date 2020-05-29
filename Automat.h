#pragma once
#ifndef AUTOMAT_H
#define AUTOMAT_H
#include<fstream>

char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                   'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
	               'u', 'v', 'w', 'x', 'y', 'z',
				   '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-' }; /// -  -> ��������� �� �������-���������

class Automat
{
public:
	Automat();
	Automat(int*, int*, char**, int*, long);
	Automat(const Automat&);
	Automat& operator=(const Automat&);
	~Automat();


	void setSetOfStates(int*);
	void setFirstStates(int*);
	void setTransitions(char**);
	void setFinalStates(int*);

	void setID(long);


	int* getSetOfStates() const;
	int* getFirstStates() const;
	char** getTransitions() const;
	int* getFinalStates() const;

	long getID() const;


	void list(std::istream& in);
	void print() const;
	void save(std::ofstream& out, char*);
	bool empty();
	bool deterministic();
	bool recognize(char*);
	long Union(const Automat&);
	long concat(const Automat&);
	long un();
	long reg(char*);


	void determinize(const Automat&);

	bool isFiniteLanguage(const Automat&);

private:
	int* setOfStates; ///������ ��������� �� ����������� �� ��������
	int* firstStates; ///��������� �� ��������� ���������
	char** transitions; ///��������� �� ���������
	int* finalStates; ///��������� �� �������� ���������

	long ID; ///���������������� �����, �������� �� ����� �������

	void copy(const Automat&);
	void erase();
};

#endif // !AUTOMAT_H
