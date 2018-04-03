calculator
=======

A calculator that can either evaluate expressions or solve equations:

- The calculator supports addition, subtraction, multiplication, division, log/sin/cos on floating point numbers.
- The calculator can solve simple linear equations with a single variable (namely, x), for simplicity, only addition, subtraction and multiplication operations are allowed.
- The calculator supports parentheses in both modes.

It has tests and some very simple GUI using [imgui](https://github.com/ocornut/imgui) and [glfw](https://github.com/glfw/glfw).

Example input:

> 5 + 8 * -log((-12 + log(100)) * -10) * log(1000)

and the result will be ```-43```

> (((2 + x) * 2 + 1) * (3 - 1 * 2) - 5) * 2 - 1 = x * (5 + 2)

and the result will be x = ```-0.3333333333```

### Building:

- CMake 3.0 or higher
- a C++14 compiler (tested with GCC 6, VS 2017)
