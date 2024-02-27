#include <assert.h>
#include <iostream>
#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include <exception>
#include <vector>

using namespace std;

bool relation1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedMultiMap smm = SortedMultiMap(relation1);
	assert(smm.size() == 0);
	assert(smm.isEmpty());
    smm.add(1,2);
    smm.add(1,3);
    assert(smm.size() == 2);
    assert(!smm.isEmpty());
    vector<TValue> v= smm.search(1);
    assert(v.size()==2);
    v= smm.search(3);
    assert(v.size()==0);
    
    SMMIterator it = smm.iterator();
    it.first();
    while (it.valid()){
    	TElem e = it.getCurrent();
    	it.next();
    }
  

    assert(smm.remove(1, 2) == true);
    assert(smm.remove(1, 3) == true);
    assert(smm.remove(2, 1) == false);
    assert(smm.isEmpty());

    // Create a SortedMultiMap
    SortedMultiMap smm2 = SortedMultiMap(relation1);

    // Add some key-value pairs
    smm2.add(1, 10);
    smm2.add(2, 20);
    smm2.add(2, 30);
    smm2.add(3, 40);

    // Replace a value for an existing key-value pair
    smm2.replace(2, 20, 25);
    // The key 2 had the value 20, it should be replaced with 25

    // Verify the updated value
    vector<TValue> values = smm2.search(2);
    assert(values.size() == 2);
    assert(values[0] == 25);
    assert(values[1] == 30);

    // Replace a value for a non-existing key-value pair
    smm2.replace(4, 50, 55);
    // The key 4 does not exist in the map, so nothing should be replaced

    // Verify that nothing was changed
    values = smm2.search(4);
    assert(values.empty());

    // Replace a value for an existing key-value pair with multiple values
    smm2.replace(2, 30, 35);
    // The key 2 had the value 30, it should be replaced with 35

    // Verify the updated value
    values = smm2.search(2);
    assert(values.size() == 2);
    assert(values[0] == 25);
    assert(values[1] == 35);

    // Replace a value for a key that has multiple occurrences of the same value
    smm2.replace(2, 35, 35);
    // The key 2 had two occurrences of the value 35, one should be replaced

    // Verify the updated value
    values = smm2.search(2);
    assert(values.size() == 2);
    assert(values[0] == 25);
    assert(values[1] == 35);

    // Replace a value for a key-value pair with negative keys
    smm2.add(-1, 100);
    smm2.replace(-1, 100, 200);
    // The key -1 had the value 100, it should be replaced with 200

    // Verify the updated value
    values = smm2.search(-1);
    assert(values.size() == 1);
    assert(values[0] == 200);

}

