#include <iostream>

using namespace std;

class CMemento {
private:
    friend class CPoint;
    int _x, _y;
    void setState(int x, int y) {
        _x = x;
        _y = y;
    }
    void getState(int& x, int& y) {
        x = _x;
        y = _y;
    }
public:
    CMemento() {
        _x = 0; _y = 0;
    }
    virtual ~CMemento() {

    }
};

class CPoint {
private:
    int _x, _y;
public:
    CPoint(int x, int y) {
        _x = x;
        _y = y;
    }
    void move(int dx, int dy) {
        _x += dx;
        _y += dy;
    }
    void report() {
        printf("CPoint is: %d %d\n", _x, _y);
    }
    virtual CMemento* createMemento() {
        CMemento* memento = new CMemento();
        memento->setState(_x, _y);
        return memento;
    }
    virtual void updateFromMemento(CMemento* memento) {
        memento->getState(_x, _y);
    }
    virtual ~CPoint() {}
};

int main()
{
    CPoint* p = new CPoint(10, 20);
    p->report();

    CMemento* memento = p->createMemento();

    p->move(5, 5);
    p->report();

    p->updateFromMemento(memento);
    p->report();

    delete memento;
    delete p;
}

