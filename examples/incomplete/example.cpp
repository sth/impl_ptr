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
