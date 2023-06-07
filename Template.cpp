#include <iostream>

class Base {
public:
    virtual void FOO() = 0;
    void TemplateMethod() {
        printf("D1\n");
        printf("D2\n");
        this->FOO();
        printf("D4\n");
    }
};

class A: public Base {
public:
    void FOO() override {
        printf("DX\n");    
    }
};

class B: public Base {
public:
    void FOO() override {
        printf("DY\n");
    }
};

int main()
{
    B* b = new B;
    A* a = new A;
    a->TemplateMethod();
    b->TemplateMethod();
}

