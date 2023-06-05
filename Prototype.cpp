#include <iostream>

using namespace std;

class Animal {    
public:
    string name;
    Animal() {
        cout << "Animal()\n";
    }
    virtual Animal* clone() = 0;
    virtual void printName() {
        cout << "I am an Animal, and my name is " << name << endl;
    }
    virtual ~Animal() {
        cout << "~Animal()\n";
    }
};

class Dog : public Animal {
public:
    Dog() {
        cout << "Dog()\n";
    }
    Animal* clone() override {
        return new Dog(*this);
    }
    void printName() override {
        cout << "I am a Dog, and my name is " << name << endl;
    }
};

class Cat : public Animal {
public:
    Cat() {
        cout << "Cat()\n";
    }
    Animal* clone() override {
        return new Cat(*this);
    }
    void printName() override {
        cout << "I am a Cat, and my name is " << name << endl;
    }
};

int main()
{
    cout << "Prototype\n";

    Animal* cages[2] = { new Cat(), new Dog() };
;
    Animal *newAnimal1 = cages[0]->clone(); // Cat created
    Animal *newAnimal2 = cages[1]->clone(); // Dog created

    Animal* p = new Cat();
    Animal* a = p->clone();
    Animal* b = p->clone();
}

