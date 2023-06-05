#include <iostream>
#include <vector>

using namespace std;

class CShape {
public:
    virtual void draw() = 0;
    virtual ~CShape() {};
};

class CPoint : public CShape {
private:
    int _x, _y;
public:
    CPoint(int x, int y) {
        _x = x; _y = y;
    }
    void move(int dx, int dy) {
        _x += dx;
        _y += dy;
    }
    void draw() override {
        printf("(%d, %d)", _x, _y);
    }
    ~CPoint() {

    }
};

class CDecorator : public CShape {
private:
    CShape* _shape;
public:
    CDecorator(CShape* shape) {
        _shape = shape;
    }
    virtual void draw() {
        printf("*");
        _shape->draw();
        printf("*");
    }
    ~CDecorator() {
        delete _shape;
    }
};

int main()
{
    vector<CShape*> shapes(3);

    shapes[0] = new CPoint(1, 1);
    shapes[1] = new CDecorator(new CPoint(2, 2));
    shapes[2] = new CDecorator(new CDecorator(new CPoint(3, 3)));

    for (const auto &i : shapes)
        if (i != nullptr) {
            i->draw();
            printf("\n");
        }

    for (vector<CShape*>::iterator i = shapes.begin(); i != shapes.end(); i++)
        if (*i != nullptr)
            delete* i;
}

