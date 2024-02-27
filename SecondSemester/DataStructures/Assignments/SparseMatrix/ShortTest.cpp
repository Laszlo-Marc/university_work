#include <assert.h>
#include "Matrix.h"

using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);	
	m.modify(1, 1, 5);
	assert(m.element(1, 1) == 5);
	TElem old = m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);
	assert(old == 5);
	Matrix t(3, 3);
	t.modify(1, 1, 2);
	t.modify(1, 2, 2);
	t.modify(1, 3, 2);
	t.modify(2,1, 3);
	t.modify(2,2, 3);
	t.modify(2,3,3);
	t.modify(3,1, 4);
	t.modify(3, 2, 4);
	t.modify(3, 3, 4);
	t.setElemsOnLine(2, 5);
	assert(t.element(2, 1) == 5);
	assert(t.element(2, 2) == 5);
	assert(t.element(2, 3) == 5);
}