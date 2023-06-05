#include <iostream>
#include <vector>

using namespace std;

class CShape {
public:
    virtual void move(int dx, int dy) = 0;
    virtual void draw() = 0;
    virtual ~CShape() {};
};

class CPoint : public CShape {
private:
    int _x, _y;
public:
    CPoint(int x, int y) : _x(x), _y(y) {

    }
    void move(int dx, int dy) override {
        _x += dx;
        _y += dy;
    }
    void draw() override {
        printf("CPoint::draw() : drawing at (%d, %d)\n", _x, _y);
    }
    ~CPoint() {

    }
};

class CGroup : public CShape {
private:
    vector<CShape*> _shapes;
public:
    CGroup() {
        printf("CGroup::CGroup()\n");
    }
    void addShape(CShape* shape) {
        _shapes.push_back(shape);
    }
    void move(int dx, int dy) override {
        printf("CGroup::move(%d, %d)\n", dx, dy);
        for (const auto& shape : _shapes)
            shape->move(dx, dy);
    }
    void draw() override {
        printf("CGroup::draw()\n");
        for (const auto& shape : _shapes)
            shape->draw();
    }
    ~CGroup() {
        printf("start CGroup::~CGroup()\n");
        for (const auto& shape : _shapes)
            delete shape;
        printf("finish CGroup::~CGroup()\n");
    }
};

int main()
{
    CGroup* shapes = new CGroup;
    shapes->addShape(new CPoint(1, 1));
    shapes->addShape(new CPoint(1, 2));

    CGroup* childshapes = new CGroup;
    childshapes->addShape(new CPoint(3, 3));
    childshapes->addShape(new CPoint(4, 4));

    shapes->addShape(childshapes);

    shapes->move(10, 10);
    shapes->draw();

    delete shapes;
}

