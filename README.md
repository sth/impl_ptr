# impl\_ptr

A smart pointer for the [PImpl idiom][1].

## Use cases

This is a header only library that provides a `impl_ptr<T>` class template, useful
as the pointer inside a [PImpl][1] class or similar classes that contain
pointers to data they own.

It assumes the data it points to is only a pointer for technical reasons but should
behave like a normal member as much as possible. So when the `impl_ptr` is created
it allocates the pointed to object, when it is destroyed it destroys the pointed to
object. When it is copied, moved or copy/move assigned it does that action for the
pointed-to object.

It does not share data between instances (unlike `std::shared_ptr<>`) and allows
copying (unlike `std::unique_ptr<>`).

Assignment and destruction are `noexcept` if the pointed-to type permits this.

`impl_ptr` can be used with incomplete types, as is often desired in Pimpl classes.

## Example

The [basic usage](examples/basic/) looks like this:

```
#include "impl_ptr.hpp"

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
```

## Incomplete types

The `impl_ptr<>` can be declared pointing to an incomplete type, but the
complete type is required when the pointed-to data is accessed. This
includes construction, destruction and assignment, even in their default
implementation. Implementing those methods directly in the class definition
will lead to errors with an incomplete type, the need to be defined where
the complete type is available.

### [Typical implementation](examples/incomplete/)

In the header file there would be a forward declaration of the pointed to data type
and declarations of the constructors/... without implementations:

```
// example.hpp
#include "impl_ptr.hpp"

struct detail;

class example {
   impl_ptr<detail> ptr;

public:
   example();
   example(const example &);
   example(example &&);
   ~example();

   example& operator=(const example &);
   example& operator=(example &&);
};
```

The associated .cpp file then contains the method definitions. In this case they can
all be declared as `= default` since `detail` and `example` don't contain any special
members:

```
// example.cpp
#include "example.hpp"

struct detail {
   std::string somedata;
};

example::example() = default;
example::example(const example &) = default;
example::example(example &&) = default;
example::~example() = default;
example& example::operator=(const example &) = default;
example& example::operator=(example &&) = default;
```

The methods could of course also be implemented by hand if necessary or declared
as `= delete` in the header, if they are not desired.

 [1]: http://en.cppreference.com/w/cpp/language/pimpl

