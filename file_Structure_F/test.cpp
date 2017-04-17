#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <iomanip>
#include <cstring>
#include "iobuffer.h"
#include "fixfld.h"
#include "length.h"
#include "person.h"

using namespace std;

Person* person_ ;
int num;

template <class IOB>
void testBuffer (IOB& Buff, char* myfile)
{
	Person person;
	int result;
	int *recaddr = new int[num];

	// Test writing
	Buff . Print (cout);
	ofstream TestOut (myfile,ios::out);
	result = Buff . WriteHeader (TestOut);
	cout << "write header "<<result<<endl;

	for (int i = 0; i < num; i++) {
		person_[i].Pack(Buff);
		Buff.Print(cout);
		recaddr[i] = Buff.Write(TestOut);
		cout << "write at " << recaddr[i] << endl;
	}

	/*AlanMason. Pack (Buff);
	buff . print (cout);
	recaddr2 = buff . write (testout);
	cout << "write at "<<recaddr2<<endl;*/
	TestOut . close ();

	// test reading
	ifstream TestIn (myfile, ios::in);
	result = Buff . ReadHeader (TestIn);
	cout <<"read header "<<result<<endl;

	stringstream ss;
	for (int i = 0; i < num; i++) {
		cout << "[ " << i << " ] RECORD ";
		Buff.DRead(TestIn, recaddr[i]);
		person.Unpack(Buff);
		person.Print(cout);
		cout << endl;
	}
	/*Buff . DRead (TestIn, recaddr2);
	person . Unpack (Buff);
	person . Print (cout, "Second record:");*/
}

void InitPerson()
{
	while (1) {
		cout << "How many information you will input : ";
		cin >> num;
		if (num < 5) 
			cout << " Information must be bigger than 5" << endl;
		else break;
	}

	person_ = new Person[num];
	cout << endl;
	for (int i = 0; i < num; i++) {
		cout << "LastName\t:";
		cin >> person_[i].LastName;
		cout << "FirstName\t:";
		cin >> person_[i].FirstName;
		cout << "Address\t\t:";
		cin >> person_[i].Address;
		cout << "City\t\t:";
		cin >> person_[i].City;
		cout << "State\t\t:";
		cin >> person_[i].State;
		cout << "Zipcode\t\t:";
		cin >> person_[i].ZipCode;
		cout << endl;
		person_[i].Print(cout);
	}
}

void testFixedField ()
{
	cout <<"Testing Fixed Field Buffer"<<endl;
	FixedFieldBuffer Buff (6);
	Person :: InitBuffer (Buff);
	testBuffer (Buff, "fixlen.dat");
}

void testLength ()
{
	cout << "\nTesting LengthTextBuffer"<<endl;
	LengthFieldBuffer Buff;
	Person :: InitBuffer (Buff);
	testBuffer (Buff, "length.dat");
}

void testDelim ()
{
	cout << "\nTesting DelimTextBuffer"<<endl;
	DelimFieldBuffer::SetDefaultDelim ('|');
	DelimFieldBuffer Buff;
	Person :: InitBuffer (Buff);
	testBuffer (Buff, "delim.dat");
}

int main(int argc, char ** argv)
{
	InitPerson();
	testFixedField ();
	testLength ();
	testDelim ();
	getchar();
	getchar();
}