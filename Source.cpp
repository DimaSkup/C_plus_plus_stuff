#include <iostream>

#pragma warning (disable : 4996)

char** addPtr(char** pp, int size, char* str);
char** delPtr(char** pp, int size, int ncell);
char** insPtr(char** pp, int size, int ncell, char* str);

int main(int argc, char* argv[])
{
	char** pp = nullptr;
	int size = 0;

	std::cout << "~~~~ Add pointers to char into pointers array and fill in the lines ~~~~" << std::endl;

	pp = addPtr(pp, size, "1111111");
	size++;

	pp = addPtr(pp, size, "2222222");
	size++;

	pp = addPtr(pp, size, "3333333");
	size++;

	pp = addPtr(pp, size, "4444444");
	size++;

	pp = addPtr(pp, size, "5555555");
	size++;

	for (int i = 0; i < size; i++)
	{
		std::cout << pp[i] << '\n';
	}
	std::cout << std::endl;


	std::cout << "~~~~ Deletion of the pointer to 3-rd line from pointer array and clean up this line ~~~~" << std::endl;

	pp = delPtr(pp, size, 2);
	size--;

	for (int i = 0; i < size; i++)
	{
		std::cout << pp[i] << '\n';
	}
	std::cout << std::endl;


	std::cout << "~~~~ Insertion of the pointer to line after 2-nd line into pointers array and fill in this line ~~~~" << std::endl;
	
	pp = insPtr(pp, size, 2, "333");
	size++;

	for (int i = 0; i < size; i++)
	{
		std::cout << pp[i] << '\n';
	}
	std::cout << std::endl;

	return 0;
}


char** addPtr(char** pp, int size, char* str)
{
	if (pp == nullptr)
	{
		pp = new(std::nothrow) char *[size + 1];
		if (!pp)
		{
			std::cout << "Error! Can't allocate memory" << std::endl;
			std::exit(EXIT_FAILURE);
		}
	}
	else
	{
		char** copy = new(std::nothrow) char *[size + 1];
		if (!copy)
		{
			std::cout << "Error! Can't allocate memory" << std::endl;
			std::exit(EXIT_FAILURE);
		}

		for (int i = 0; i < size; i++)
		{
			copy[i] = pp[i];
		}

		delete[] pp;
		pp = copy;
	}

	pp[size] = new(std::nothrow) char[strlen(str) + 1];
	if (!pp[size])
	{
		std::cout << "Error! Can't allocate memory" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	strcpy(pp[size], str);

	return pp;
}


char** delPtr(char** pp, int size, int ncell)
{
	if (size > 1 && pp != nullptr)				// there is more than one cell in the array
	{
		char** copy = new(std::nothrow) char *[size - 1];

		for (int i = 0; i < ncell; i++)
		{
			copy[i] = pp[i];
		}

		for (int i = ncell; i < size - 1; i++)
		{
			copy[i] = pp[i + 1];
		}

		delete[] pp[ncell];
		delete[] pp;
		pp = copy;
	}
	else if (size == 1 && pp != nullptr)		// there is only one cell in the array
	{
		delete[] pp[0];
		delete[] pp;
		pp = nullptr;
	}
	else if (pp == nullptr)	// there is already no cell in the array
	{
		std::cout << "Warning! This array is already empty " << '\n' << '(' << __FILE__ << " at the function: " <<  __FUNCTION__ << ':' << __LINE__ << ')'<< std::endl;
	}

	return pp;
}


char** insPtr(char** pp, int size, int ncell, char* str)
{
	if (size > ncell)		// the number of cells (size of the array) is more that ncell
	{
		char** copy = new(std::nothrow) char *[size + 1];
		if (!copy)
		{
			std::cout << "Error! Can't allocate memory" << std::endl;
			std::exit(EXIT_FAILURE);
		}


		for (int i = 0; i < ncell; i++)
		{
			copy[i] = pp[i];
		}

		copy[ncell] = new(std::nothrow) char[strlen(str) + 1];
		if (!copy[ncell])
		{
			std::cout << "Error! Can't allocate memory" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		strcpy(copy[ncell], str);

		for (int i = ncell + 1; i < size + 1; i++)
		{
			copy[i] = pp[i - 1];
		}

		delete[] pp;
		pp = copy;
	}
	else // the number of cells is equal or less that ncell then we'll put a new line at the end of the array
	{
		std::cout << "Warning! The number of cells is less than ncell, we'll put a new line at the end of the array" << std::endl;
		pp = addPtr(pp, size, str);
	}

	return pp;
}