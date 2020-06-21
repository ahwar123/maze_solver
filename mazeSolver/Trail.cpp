
#include "Trail.h"
using namespace std;

Trail::Trail() {
	length = 0;
}

Trail::~Trail() {
}

int Trail::size() {
   return length;
}

Breadcrumb* Trail::getPtr(int i) {
   return breadcrumbs[i];
}

void Trail::addCopy(Breadcrumb* t) {
	// set new breadcrumb and increase length for next
	breadcrumbs[length] = t;
	incrementLength();
}

bool Trail::contains(int x, int y) {
	return false;
}


int Trail::getBreadCrumbIndex(int x, int y) {

	// find breadcrumb and return trail index
	for (int i = 0; i < length; i++) {
		if (breadcrumbs[i]->getX() == x && breadcrumbs[i]->getY() == y) {
			return i;
		}
	}
	return -1;
}

void Trail::incrementLength() {
	length++;
}
void Trail::decrementLength() {
	length--;
}