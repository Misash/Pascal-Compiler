
# Pascal Compiler

Simplified pascal compiler developed during the Compilers course
## Documentation

this compiler includes the following parts:

- Scanner: Read the pascal code  and storage errors and tokens
- Parser : Parse tokens into logical syntax components, returning a parse tree


## Installation

Install my-project with g++ >=9.3.0  and GNU Make >=4.2.1

It is recommended that you use Linux

Install dependencies :

```bash
sudo apt install g++
sudo apt-get install build-essential

```



## Run Locally

Clone the project

```bash
  git clone https://github.com/Misash/Pascal-Compiler.git 
```

Go to the project directory

```bash
  cd my-project
```


Execute the Scanner  with g++

```bash
  cd scr/
  g++ parser.cpp -o myprog && ./myprog
```

Execute the Scanner  with Makefile

```bash
  make run
```

Clean object code
```bash
  make clean
```
