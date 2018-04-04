
#include "example.hpp"

int main() {
	example e1;
	example e2(e1);
	example e3(std::move(e1));
	example e4, e5, e6;
	e5 = e4;
	e6 = std::move(e4);
}

