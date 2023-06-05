#include <iostream>

using namespace std;

class Zoo {
private:
    static Zoo* _zoo;
protected:
    Zoo() {
        cout << "Zoo::Zoo()\n";
    }
public:
    static Zoo* get_instance() {
        if (_zoo == nullptr)
            _zoo = new Zoo();
        return _zoo;
    }
    void do_something() {
        cout << "Zoo::doSomething()\n";
    }
};

class Zoo2 {
protected:
    Zoo2() {
        cout << "Zoo2::Zoo2()\n";
    }
public:
    static Zoo2& get_instance() {
        static Zoo2 zoo;
        return zoo;
    }
    void do_something() {
        cout << "Zoo2::do_something()\n";
    }
};

Zoo* Zoo::_zoo = nullptr;

int main()
{
    Zoo2::get_instance().do_something();
}

