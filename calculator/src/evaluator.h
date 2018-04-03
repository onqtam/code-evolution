#pragma once

#include <stdexcept>

namespace evaluator
{
class ParseException : public std::runtime_error
{
    size_t m_pos;

public:
    ParseException(const char* msg, size_t pos = 0)
            : runtime_error(msg)
            , m_pos(pos) {}

    size_t pos() const { return m_pos; }
};

// this is the entire API of the evaluator - depending on its input it either evaluates expressions or solves equations
// - can throw ParseException while parsing - with a number to indicate at which character pos was the error
// - can throw std::runtime_error while evaluating (division by zero, non-positive number in log, non-linear equation)
// some errors that can be caught at parsing time are thrown during evaluation - such as:
// - unsupported operators/functions in equation mode
// - variable or equality operator missing in equation mode
// - too many equality operators found in equation
double eval(const char* in);

} // namespace evaluator
