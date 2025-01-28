# Mathematical Calculator with GUI

This is a basic mathematical calculator created using C++ and the Qt framework.

## Features

- Performs basic arithmetic operations such as:
    - Addition.
    - Subtraction.
    - Multiplication.
    - Division.
- Error handling for divide by zero.
- Clear input button.

## Requirements

C++11
Qt 5

## Build and Run

1. Clone this repo to your local machine:
```bash
    git clone https://github.com/ch-ke/cpp-qt-calculator.git
    cd cpp-qt-calculator
```

2. Compile and run:
```bash
    make && ./calc
```

3. Clean directory:
```bash
    make clean
```

## To do

current calculator logic exists as a placeholder for GUI app development learning.

It does not currently perform correct logic as per the mathematical order of operations

more efficient logic to be implemented soon.

ideas for calculator logic include: 
 - reverse polish notation (RPN) using stack
 - recursive descent parser
 - infix to postfix conversion (shunting yard)

