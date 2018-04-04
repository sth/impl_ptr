#include "impl_ptr.hpp"
#include <cassert>

struct details {
	std::string somedata;

	explicit details(const std::string &sd) : somedata(sd) {
	}
};

struct example {
	impl_ptr<details> ptr;

	// The impl_ptr passes constructor arguments to the pointed-to class
	example() : ptr("abc") {
	}
};

int main() {
	example e1;
	assert(e1.ptr->somedata == "abc");

	// the pointed to data can be accessed with the usual operators -> and *
	e1.ptr->somedata = "xyz";

	// move/copy default implementations work with impl_ptr<> members
	example e2(e1);
	assert(e1.ptr->somedata == "xyz");
	assert(e2.ptr->somedata == "xyz");
	e2.ptr->somedata = "abc";
	assert(e1.ptr->somedata == "xyz");
	assert(e2.ptr->somedata == "abc");
}

