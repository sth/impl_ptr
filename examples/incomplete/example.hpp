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
