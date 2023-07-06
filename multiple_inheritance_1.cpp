struct A {
public:
	A(int a = 0) : a(a) {};
	int fooa() { return a; }
	~A() {};
private:
	int a;
};

struct B : A {
public:
	B(int a = 0, int b = 1) : A(a), b(b) {};
	int foob() { return b; }
	~B() {};
private:
	int b;
};

struct C {
public:
	C(int c = 2) : c(c), cp(-2) { };
	int foo() { return c; }
	~C() {};
	int cp;
private:
	int c;
};

struct D : A, C {
public:
	D(int a = 0, int c = 2, int d = 3) : A(a), C(c), d(d) {};
	int food() { return d; }
	~D() {};
private:
	int d;
};

struct E : B, C, D {
public:
	E(int a = 0, int b = 1, int c = 2, int d = 3, int e = 4) : B(a, b), C(c), D(a, c, d), e(e) {};
	int fooe() { return e; }
	~E() {};
private:
	int e;
};

#include <iostream>

int main() {

	E* e = new E();
	std::cout << e->C::foo() << "\n"; // OK
	//std::cout << e->fooa(); //NO
	//std::cout << e->foo(); //NO
	std::cout << e->foob() << "\n"; // OK
	std::cout << e->B::A::fooa() << "\n"; // OK
	std::cout << e->B::A::fooa() << "\n"; // OK
	std::cout << e->D::C::foo() << "\n"; // OK

	std::cout << e->C::cp << "\n"; //OK
	std::cout << e->D::C::cp << "\n"; //OK
	//std::cout << e->cp << "\n"; //NO

	e->C::cp = -3;
	std::cout << e->C::cp << "\n"; // -3
	std::cout << e->D::C::cp << "\n"; // -2

	C* pc = e;
	std::cout << pc->cp; // -3 -> E::C //OK
	pc = (C*)((char*)pc + sizeof(C) + sizeof(A)); // A->B->C->A->C->D->E pc = E::D::C //OK
	std::cout << pc->cp; //-2 //OK

	getchar();
	delete e;
	return 0;
}