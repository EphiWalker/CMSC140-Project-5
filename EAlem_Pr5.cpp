/*
 * Class: CMSC140 CRN 10016
 * Instructor: Hui-Mei Margaret Tseng
 * Project 5
 * Description: A program that takes 9 numbers from the user and sets them in a 3 x 3 grid,
 *				and checks if this 3 x 3 square is a Lo Shu Magic Square.
 * Due Date: 08/09/2024
 * Platform/Compiler: Microsoft Visual Studio
 * I pledge that I have completed the programming assignment independently.
   I have not copied the code from a student or any source.
   I have not given my code to any student.
   Print your Name here: Ephrem Alem
*/

#include <iostream>
#include <set>
using namespace std;

const int ROWS = 3;
const int COLS = 3;
const int MIN = 1;
const int MAX = 9;
set <int> rowSumSet, colSumSet, diagSumSet;

bool isMagicSquare(int[], int[], int[], int);
bool checkRange(int[], int[], int[], int, int, int);
bool checkUnique(int[], int[], int[], int);
bool checkRowSum(int[], int[], int[], int);
bool checkColSum(int[], int[], int[], int);
bool checkDiagSum(int[], int[], int[], int);
void fillArray(int[], int[], int[], int);
void showArray(int[], int[], int[], int);
void programmerOutro();

int main()
{

	int magicArrayRow1[COLS], magicArrayRow2[COLS], magicArrayRow3[COLS];
	int size = sizeof(magicArrayRow1) / sizeof(magicArrayRow1[0]);
	char retry;

	do {

		fillArray(magicArrayRow1, magicArrayRow2, magicArrayRow3, size);

		showArray(magicArrayRow1, magicArrayRow2, magicArrayRow3, size);

		bool magicSquare = isMagicSquare(magicArrayRow1, magicArrayRow2, magicArrayRow3, size);

		if (magicSquare) {
			cout << "\nThis is a Lo Shu magic square.\n";
		}
		else {
			cout << "\nThis is not a Lo Shu magic square.\n";
		}

		cout << "Do you want to try again? ";
		cin >> retry;

		if (tolower(retry) == 'y') {
			continue;
		}
		else {
			break;
		}

	} while (true);	//use 'true', but avoid an infinite loop by forcing the if statement to choose between limited conditions

	programmerOutro();

	return 0;
}

void fillArray(int arrayRow1[], int arrayRow2[], int arrayRow3[], int size) {
	for (int i = 0; i < size; i++) {
		cout << "Enter the number for row 0 and column " << i << " :";
		cin >> arrayRow1[i];
	}

	for (int i = 0; i < size; i++) {
		cout << "Enter the number for row 1 and column " << i << " :";
		cin >> arrayRow2[i];
	}

	for (int i = 0; i < size; i++) {
		cout << "Enter the number for row 2 and column " << i << " :";
		cin >> arrayRow3[i];
	}
}

void showArray(int arrayRow1[], int arrayRow2[], int arrayRow3[], int size) {
	for (int i = 0; i < size; i++) {
		cout << arrayRow1[i] << " ";
	}
	
	cout << "\n";
	
	for (int i = 0; i < size; i++) {
		cout << arrayRow2[i] << " ";
	}
	
	cout << "\n";
	
	for (int i = 0; i < size; i++) {
		cout << arrayRow3[i] << " ";
	}
	
	cout << "\n";
}

bool checkRange(int arrayRow1[], int arrayRow2[], int arrayRow3[], int size, int min, int max) {
	for (int i = 0; i < size; i++) {
		if (arrayRow1[i] < min || arrayRow1[i] > max) {
			return false;
		}
	}

	for (int i = 0; i < size; i++) {
		if (arrayRow2[i] < min || arrayRow2[i] > max) {
			return false;
		}
	}

	for (int i = 0; i < size; i++) {
		if (arrayRow3[i] < min || arrayRow3[i] > max) {
			return false;
		}
	}

	return true;
}

bool checkUnique(int arrayRow1[], int arrayRow2[], int arrayRow3[], int size) {
	set <int> setRow1(arrayRow1, arrayRow1 + size), setRow2(arrayRow2, arrayRow2 + size), 
				setRow3(arrayRow3, arrayRow3 + size); // copy all three arrays into sets to check for uniqueness

	if (setRow1.size() == size && setRow2.size() == size && setRow3.size() == size) {	//the sets will reduce duplicates to single instances,
		return true;																	//and that reduces the size of the set from the size of the array.
	}																					//If there's a duplicate, the set size will be different from
																						//the array size stored in the 'size' variable.
	return false;
}

bool checkRowSum(int arrayRow1[], int arrayRow2[], int arrayRow3[], int size) {
	int rowSumArray[ROWS] = { 0 };

	for (int i = 0; i < size; i++) {
		rowSumArray[0] += arrayRow1[i];
	}

	for (int i = 0; i < size; i++) {
		rowSumArray[1] += arrayRow2[i];
	}

	for (int i = 0; i < size; i++) {
		rowSumArray[2] += arrayRow3[i];
	}

	rowSumSet.insert(rowSumArray, rowSumArray + size);	//copy the array of row sums to a set. If the three elements of the array are
														//similar, the set will only copy one of them as sets don't stored duplicates.

	if (rowSumSet.size() == 1) {	//If the set has more than one element, the row sums in the array must not have been similar.
		return true;
	}

	return false;
}

bool checkColSum(int arrayRow1[], int arrayRow2[], int arrayRow3[], int size) {
	int colSumArray[COLS] = { 0 };
	
	for (int i = 0; i < size; i++) {
		colSumArray[i] += arrayRow1[i] + arrayRow2[i] + arrayRow3[i];
	}

	colSumSet.insert(colSumArray, colSumArray + size);
	
	if (colSumSet.size() == 1) {
		return true;
	}

	return false;
}

bool checkDiagSum(int arrayRow1[], int arrayRow2[], int arrayRow3[], int size) {
	int diagSumArray[2] = { 0 };
	diagSumArray[0] = arrayRow1[0] + arrayRow2[1] + arrayRow3[2];
	diagSumArray[1] = arrayRow1[2] + arrayRow2[1] + arrayRow3[0];

	diagSumSet.insert(diagSumArray, diagSumArray + 2);

	if (diagSumSet.size() == 1) {
		return true;
	}

	return false;
}

bool isEqualSum() {
	if (rowSumSet == colSumSet && rowSumSet == diagSumSet) {	//If our three sum sets are equal (i.e., contain the same one sum element),
		return true;											//we've equal sum in rows, columns & diagonals.
	}

	return false;
}

bool isMagicSquare(int arrayRow1[], int arrayRow2[], int arrayRow3[], int size) {
	bool correctRange = checkRange (arrayRow1, arrayRow2, arrayRow3, size, MIN, MAX);
	bool correctUnique = checkUnique(arrayRow1, arrayRow2, arrayRow3, size);
	bool correctRowSum = checkRowSum(arrayRow1, arrayRow2, arrayRow3, size);
	bool correctColSum = checkColSum(arrayRow1, arrayRow2, arrayRow3, size);
	bool correctDiagSum = checkDiagSum(arrayRow1, arrayRow2, arrayRow3, size);
	bool equalSum = isEqualSum();

	if ((correctRange && correctUnique && correctRowSum && correctColSum && correctDiagSum && equalSum) == true) {
		return true;
	}

	return false;
}

void programmerOutro() {
	cout << "\n\nClass: CMSC140 CRN 10016\n";
	cout << "Assignment: Project 5\n";
	cout << "Programmer: Ephrem Alem\n";
	cout << "Due Date: 08/09/2024";
}