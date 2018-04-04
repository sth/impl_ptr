
#define BOOST_TEST_MODULE impl_ptr
#include <boost/test/included/unit_test.hpp>

#include "impl_ptr.hpp"

BOOST_AUTO_TEST_CASE(template_instantiation) {
	// instantiate all the template functions to make sure they compile

	struct details {
		std::string data;
	};

	// construction
	impl_ptr<details> a;
	impl_ptr<details> b(a);
	impl_ptr<details> c(std::move(a));
	const impl_ptr<details> d;

	// assignment
	b = a;
	c = std::move(b);

	// ->
	(void) a->data;
	(void) d->data;

	// *
	(void) *a;
	(void) *d;
	(void) *std::move(a);

	// destruction
}

BOOST_AUTO_TEST_CASE(default_methods) {
	struct details {
		std::string data;
	};
	struct base {
		impl_ptr<details> ptr;
	};

	base b1;
	b1.ptr->data = "abc";

	// copy
	base b2(b1);
	BOOST_CHECK_EQUAL(b2.ptr->data, "abc");
	// ptr target is not shared
	b1.ptr->data = "def";
	BOOST_CHECK_EQUAL(b2.ptr->data, "abc");

	// move
	base b3(std::move(b1));
	BOOST_CHECK_EQUAL(b3.ptr->data, "def");
	// ptr target moved from, but not deallocated and not shared
	b1.ptr->data = "ghi";
	BOOST_CHECK_EQUAL(b3.ptr->data, "def");

	// copy assignment
	base b4, b5;
	b4.ptr->data = "abc";
	b5 = b4;
	BOOST_CHECK_EQUAL(b5.ptr->data, "abc");
	// ptr target copied and not shared
	b4.ptr->data = "def";
	BOOST_CHECK_EQUAL(b5.ptr->data, "abc");

	// move assignment
	b5 = std::move(b4);
	BOOST_CHECK_EQUAL(b5.ptr->data, "def");
	// ptr target moved from, but not deallocated and not shared
	b4.ptr->data = "ghi";
	BOOST_CHECK_EQUAL(b5.ptr->data, "def");
}


BOOST_AUTO_TEST_CASE(example_basic) {
	// The basic usage example from the readme file
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

	example e1;
	BOOST_CHECK_EQUAL(e1.ptr->somedata, "abc");

	// the pointed to data can be accessed with the usual operators -> and *
	e1.ptr->somedata = "xyz";

	// move/copy default implementations work with impl_ptr<> members
	example e2(e1);
	BOOST_CHECK_EQUAL(e1.ptr->somedata, "xyz");
	BOOST_CHECK_EQUAL(e2.ptr->somedata, "xyz");
	e2.ptr->somedata = "abc";
	BOOST_CHECK_EQUAL(e1.ptr->somedata, "xyz");
	BOOST_CHECK_EQUAL(e2.ptr->somedata, "abc");
}
