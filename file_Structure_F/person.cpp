//person.cc
#include "person.h"

Person::Person (){Clear ();}

void Person::Clear ()
{
	// set each field to an empty string
	LastName [0] = 0; FirstName [0] = 0; Address [0] = 0;
	City [0] = 0; State [0] = 0; ZipCode [0] = 0;
}

int Person::Pack (IOBuffer & Buffer) const
{// pack the fields into a FixedFieldBuffer, 
 // return TRUE if all succeed, FALSE o/w
	int numBytes;
	Buffer . Clear ();
	numBytes = Buffer . Pack (LastName);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer . Pack (FirstName);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer . Pack (Address);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer . Pack (City);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer . Pack (State);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer . Pack (ZipCode);
	if (numBytes == -1) return FALSE;
	return TRUE;
}

int Person::Unpack (IOBuffer & Buffer)
{
	Clear ();
	int numBytes;
	numBytes = Buffer . Unpack (LastName);
	if (numBytes == -1) return FALSE;
	LastName[numBytes] = 0;
	numBytes = Buffer . Unpack (FirstName);
	if (numBytes == -1) return FALSE;
	FirstName[numBytes] = 0;
	numBytes = Buffer . Unpack (Address);
	if (numBytes == -1) return FALSE;
	Address[numBytes] = 0;
	numBytes = Buffer . Unpack (City);
	if (numBytes == -1) return FALSE;
	City[numBytes] = 0;
	numBytes = Buffer . Unpack (State);
	if (numBytes == -1) return FALSE;
	State[numBytes] = 0;
	numBytes = Buffer . Unpack (ZipCode);
	if (numBytes == -1) return FALSE;
	ZipCode[numBytes] = 0;
	return TRUE;
}

int Person::InitBuffer (FixedFieldBuffer & Buffer)
// initialize a FixedFieldBuffer to be used for Persons
{
	int result;
	result = Buffer . AddField (10); // LastName [11];
	result = result && Buffer . AddField (10); // FirstName [11];
	result = result && Buffer . AddField (15); // Address [16];
	result = result && Buffer . AddField (15); // City [16];
	result = result && Buffer . AddField (2);  // State [3];
	result = result && Buffer . AddField (9); // ZipCode [10];
	return result;
}

int Person::InitBuffer (DelimFieldBuffer& Buffer)
// initialize a DelimFieldBuffer to be used for Persons
{	return TRUE;}

int Person::InitBuffer (LengthFieldBuffer & Buffer)
// initialize a LengthFieldBuffer to be used for Persons
{	return TRUE;}

void Person::Print (ostream& stream, char* label) const
{
	if (label == 0) stream << "Person:";
	else stream << label;
	stream << "\n\n\t Last Name '"<<LastName<<"'\n"
		<< "\tFirst Name '"<<FirstName<<"'\n"
		<< "\t   Address '"<<Address<<"'\n"
		<< "\t      City '"<<City<<"'\n"
		<< "\t     State '"<<State<<"'\n"
		<< "\t  Zip Code '"<<ZipCode<<"'\n\n" <<flush;
}

