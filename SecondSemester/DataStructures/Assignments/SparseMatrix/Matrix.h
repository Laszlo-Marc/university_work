#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

class Matrix {

private:
	TElem* values;
	TElem* lines;
	TElem* cols;
	int length;
	int capacity;
	int lenLines;
	int lenCols;
public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	//BC: Theta(1)
	//AC: Theta(1)
	//WC: Theta(1)
	int nrLines() const;

	//returns the number of columns
	//BC: Theta(1)
	//AC: O(1)
	//WC: Theta(1)
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	//BC: Theta(1)
	//AC: O(n)
	//WC: Theta(n)
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	//BC: Theta(1)
	//AC: O(n)
	//WC: Theta(n)
	TElem modify(int i, int j, TElem e);

	//sets all the values from line to the value elem
	//throws exception if line is not valid
	void setElemsOnLine(int line, TElem elem);

};
