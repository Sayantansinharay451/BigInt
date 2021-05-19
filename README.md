# Big_integer_cpp


# **BigInt**
>**`C++` class/lib to handel integer arbitrary length.**


<font size='20'><u>Content</u></font>
- [Big_integer_cpp](#big_integer_cpp)
- [**BigInt**](#bigint)
	- [**Description**](#description)
	- [**Usage**](#usage)
		- [**Initialization & Assignment**](#initialization--assignment)
		- [**Input/Output**](#inputoutput)

## **Description**
I have made a `c++` class that can handle both integers as well as an integer of arbitrary length.

This class can work with different operators such as `+`, `-`, `*` and `/` [***Not stable yet. will be updated soon***].

*I have also used `make` to automate the build for my project.*

**If you want to contribute to this project you are also very welcome :grinning:. You can also raise issues if you find a bug or any suggestion about modification.**


## **Usage**



***Note-*** Namespace used is `bigint`.

You can include `namespace` like this:  

```cpp
using namespace bigint;
```
or can used `::` scope resolution operator to include the `namespace`.

**Example :-**
```cpp
bigint::BigInt i = 1234567890;
std::cout<<i;	//1234567890
```

### **Initialization & Assignment**
Initialization is very simple and similar just like normal variables. In case if you cant to initialize arbitrary-sized integers you can pass it as a string or used the given `macro function` to initialize. 

**Demonstration :-**

```cpp
/**
 * I am not using namespace because if you are not using 
 * namespace for any reason you may find it difficult to use 
 * if you have no prior knowledge in c++. And this will be 
 * followed through out the documentation.
 **/

// Initializing integers.
bigint::BigInt i = 123;
// Using Macro function.
bigint::BigInt j = bigint::BIG_INT(456);
// Initializing from integer variable. 
int val = 123456;
bigint::BigInt k = val;
// Initializing from string.
k = "567";
// Default initialization
bigint::BigInt n;	//0
n=j;			//456
// Negative BigInt

```


### **Input/Output**
Input and Output is also similar to how we I/O integers.

**Demonstration :-**

```cpp
bigint::BigInt i;
// Input from User
std::cin>>i;			//123456
// Output
std::cout<<i<<std::endl;	//123456
```
