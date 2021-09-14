#include <iostream>
#include <assert.h>

#pragma warning (disable : 4996)

void printLines(char** pPtr, int size);
char** AddPtr(char** pPtr, int size, char *str);			// add a string at the end of the pointers array (pPtr)
char** InsPtr(char** pPtr, int* size, int ncell, char* str);	// add a string at the particular position (ncell) of the pointers array (pPtr)
char** DelPtr(char** pPtr, int size, int ncell);			// delete a pointer to char and a string from the particular position (ncell) of the pointers array (pPtr)


int main(int argc, char *argv[])
{
	char **pPtr = nullptr;
	int size = 0;

	pPtr = AddPtr(pPtr, size, "first line");
	size++;

	pPtr = AddPtr(pPtr, size, "second line");
	size++;

	pPtr = AddPtr(pPtr, size, "third line");
	size++;

	pPtr = AddPtr(pPtr, size, "fourth line");
	size++;

	pPtr = AddPtr(pPtr, size, "fifth line");
	size++;

	std::cout << " ~~~~ after 5 calls of AddPtr() function: ~~~~\n";
	printLines(pPtr, size);



	std::cout << " ~~~~ call DelPtr() function and delete third line ~~~~\n";
	pPtr = DelPtr(pPtr, size, 2);
	size--;

	printLines(pPtr, size);

	

	int pos = 10;
	std::cout << " ~~~~ call InsPtr() function and insert a line into the " << pos << " position ~~~~\n";
	pPtr = InsPtr(pPtr, &size, pos, "-CUSTOM POSITION-");

	printLines(pPtr, size);

	// release the memory
	for (int i = 0; i < size; i++)
	{
		delete[] pPtr[i];		// release the string (char*)
	}

	delete[] pPtr;	// release the pointers array

	return 0;
}

char** AddPtr(char** pPtr, int size, char* str)
{
	if (pPtr == nullptr)
	{
		pPtr = new char*[size + 1];
		assert(pPtr);
	}
	else
	{
		char** copy = new char*[size + 1];
		assert(copy);

		for (int i = 0; i < size; i++)
		{
			copy[i] = pPtr[i];
		}

		delete[] pPtr;
		pPtr = copy;
	}

	pPtr[size] = new char[strlen(str) + 1];
	strcpy(pPtr[size], str);

	return pPtr;
}

char** DelPtr(char** pPtr, int size, int ncell)
{
	if (pPtr == nullptr)	// no lines
	{
		std::cout << "There are no lines already" << std::endl;

		return nullptr;
	}
	else if (size == 1)		// only one line
	{
		delete[] pPtr[0];	// release the string
		delete[] pPtr;		// release the pointers array
		pPtr = nullptr;

		return nullptr;
	}
	else					// more than one line
	{
		char** copy = new char*[size - 1];
		assert(copy);

		for (int i = 0; i < ncell; i++)
		{
			copy[i] = pPtr[i];
		}

		for (int i = ncell; i < size - 1; i++)
		{
			copy[i] = pPtr[i + 1];
		}

		delete pPtr[ncell];		// release the string
		delete pPtr;			// release the pointers array
		pPtr = copy;
	}

	return pPtr;
}

char** InsPtr(char** pPtr, int* size, int ncell, char* str)
{
	if (ncell > 0)
	{
		if (pPtr == nullptr)	// there are no lines yet
		{

			pPtr = new char*[ncell + 1];
			assert(pPtr);

			int emptyLineSize = strlen("empty line");

			for (int i = 0; i < ncell; i++)
			{

				pPtr[i] = new char[emptyLineSize + 1];
				assert(pPtr[i]);
				strcpy(pPtr[i], "empty line");
			}

			pPtr[ncell] = new char[strlen(str) + 1];
			assert(pPtr[ncell]);
			strcpy(pPtr[ncell], str);
		}
		else if ((*size) < ncell)	// size of the pointers array < ncell
		{
			for ( ; (*size) < ncell; (*size)++)
			{
				pPtr = AddPtr(pPtr, *size, "empty line");
			}

			pPtr[ncell] = new char[strlen(str) + 1];
			assert(pPtr[ncell]);
			strcpy(pPtr[ncell], str);
		}
		else		// size of the pointers array > ncell
		{
			char** copy = new char*[(*size) + 1];
			assert(copy);

			// from 0 to ncell
			for (int i = 0; i < ncell; i++)
			{
				copy[i] = pPtr[i];
			}

			// skip ncell line

			// from ncell + 1 to size
			for (int i = ncell + 1; i < (*size) + 1; i++)
			{
				copy[i] = pPtr[i + 1];
			}

			// here we put the string at the ncell position
			copy[ncell] = new char[strlen(str) + 1];
			assert(copy[ncell]);
			strcpy(copy[ncell], str);

			delete[] pPtr;
			pPtr = copy;
		}
	}

	return pPtr;
	
}


void printLines(char **pPtr, int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << pPtr[i] << '\n';
	}
	std::cout << std::endl;
}