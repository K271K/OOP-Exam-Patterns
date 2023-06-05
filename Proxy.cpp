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
    CPoint(int x, int y) : _x(x), _y(y) {

    }
    void move(int dx, int dy) {
        _x += dx;
        _y += dy;
    }
    void draw() override {
        printf("CPoint::draw() : drawing at (%d, %d)\n", _x, _y);
    }
    ~CPoint() {

    }
};

class CProxyPoint : public CShape {
private:
    int _x, _y;
    CPoint* point;
public:
    CProxyPoint(int x, int y) : _x(x), _y(y), point(nullptr) {

    }
    void draw() override {
        if (point == nullptr)
            point = new CPoint(_x, _y);
        point->draw();
    }
    ~CProxyPoint() {
        if (point != nullptr)
            delete point;
    }
};

int main()
{
    vector<CShape*> shapes(3);
    shapes[0] = new CPoint(1, 1);
    shapes[1] = new CProxyPoint(2, 2);
    shapes[2] = new CPoint(3, 3);

    for (const auto& i : shapes)
        if (i != nullptr)
            i->draw();

    for (vector<CShape*>::iterator i = shapes.begin(); i != shapes.end(); i++)
        if (*i != nullptr)
            delete* i;
}

