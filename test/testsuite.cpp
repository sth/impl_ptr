
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

