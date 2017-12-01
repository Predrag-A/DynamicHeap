#pragma once
#pragma warning(disable:4996)

#include <iostream>
class Exception
{
private:
	char* text;
public:
	Exception(char* newText)
	{
		text = strdup(newText);
	}

	~Exception()
	{
		if (text != NULL)
			delete text;
	}

	friend std::ostream& operator <<(std::ostream& out, Exception& err) {
		out << err << std::endl;
		return out;
	};

};