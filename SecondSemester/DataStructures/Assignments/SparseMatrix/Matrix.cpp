#include "Matrix.h"
#include <exception>
#include <iostream>

using namespace std;



Matrix::Matrix(int nrLines, int nrCols) {
	   
	this->capacity = 10;
	this->values = new TElem[this->capacity];
	this->lenCols = nrCols;
	this->lenLines = nrLines;
	this->cols = new int[this->lenCols];
	this->lines = new int[this->lenLines];
	this->length = 0;

}


int Matrix::nrLines() const {
	return this->lenLines;
}


int Matrix::nrColumns() const {
	return this->lenCols;
}


TElem Matrix::element(int i, int j) const {
	if (i<0 || i>nrLines() || j<0 || j>nrColumns()) {
		throw exception();
	}
	for (int c = 0; c < this->length; c++) {
		if (this->lines[c] == i && this->cols[c] == j) {
			return this->values[c];
		}
	}
	return NULL_TELEM;
}

TElem Matrix::modify(int i, int j, TElem e) {
	if (i<0 || i>nrLines() || j<0 || j>nrColumns()) {
		throw exception();
	}

	TElem previous = element(i, j);
	int k;
	if (previous != NULL_TELEM) {
		if (e == NULL_TELEM) {
			int pos = -1;
			for (k = 0; k < this->length; k++) {
				if (this->lines[k] == i && this->cols[k] == j) {
					pos = k;
				}
			}
			for (k = pos; k <= this->length; k++) {
				this->lines[k] = this->lines[k + 1];
				this->cols[k] = this->cols[k + 1];
				this->values[k] = this->values[k + 1];
			}
			this->length--;
		}
		else {
			for (k = 0; k < this->length; k++) {
				if (this->lines[k] == i && this->cols[k] == j)
					this->values[k] = e;
			}
		}
	}  
	else {
		if (this->capacity == this->length) {
			this->capacity *= 2;
			auto* auxLines = new TElem[this->capacity];
			auto* auxCols = new TElem[this->capacity];
			auto* auxValues = new TElem[this->capacity];
			for (k = 0; k < this->length; k++) {
				auxLines[k] = this->lines[k];
				auxCols[k] = this->cols[k];
				auxValues[k] = this->values[k];
			}
			delete[] this->lines;
			delete[] this->cols;
			delete[] this->values;
			this->lines = auxLines;
			this->cols = auxCols;
			this->values = auxValues;
		}
		this->length++; // we add it
		int pos = 0;
		for (k = 0; k < this->length; k++) {
			if (this->lines[k] == i && this->cols[k] == j) {
				pos = k + 1;
				break;
			}
		}
	for (k = this->length - 1; k >= pos; k--) {
		this->lines[k] = this->lines[k - 1];
		this->cols[k] = this->cols[k - 1];
		this->values[k] = this->values[k - 1];
	}
	this->lines[pos] = i;
	this->cols[pos] = j;
	this->values[pos] = e;

	}
	return previous;
}

void Matrix::setElemsOnLine(int line, TElem elem)
{
	if (line >= this->nrLines() || line < 0) {
		throw exception();
	}

	for (int i = 0; i < this->nrColumns(); i++) {
		this->modify(line, i, elem);
	}
}


