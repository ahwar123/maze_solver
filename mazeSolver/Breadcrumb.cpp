
#include "Breadcrumb.h"
using namespace std;
Breadcrumb::Breadcrumb() {
	Breadcrumb::x = 0;
	Breadcrumb::y = 0;
	Breadcrumb::stale = false;
}


Breadcrumb::Breadcrumb(int x, int y, bool stale) {
	Breadcrumb::x = x;
	Breadcrumb::y = y;
	Breadcrumb::stale = stale;
}

Breadcrumb::~Breadcrumb() {
}

int Breadcrumb::getX() {
   return x;
}

int Breadcrumb::getY() {
   return y;
}

bool Breadcrumb::isStale() {
	return stale;
}

void Breadcrumb::setStale(bool stale) {
	Breadcrumb::stale = stale;
}
