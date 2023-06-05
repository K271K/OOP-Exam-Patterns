#include <iostream>
#include <vector>

using namespace std;

class CShape {
public:
    virtual void save(FILE* stream) = 0;
    virtual void load(FILE* stream) = 0;
    virtual ~CShape() {}
};

class CPoint : public CShape {
private:
    int _x, _y;
public:
    CPoint(int x, int y) {
        _x = x;
        _y = y;
    }
    void save(FILE* stream) override {
        fprintf(stream, "P\n");
        fprintf(stream, "%d %d\n", _x, _y);
    }
    void load(FILE* stream) override {
        fscanf(stream, "%d %d\n", &_x, &_y);
    }
};
class CCircle : public CShape {
private:
    int _x, _y, _r;
public:
    CCircle(int x, int y, int r) {
        _x = x;
        _y = y;
        _r = r;
    }
    void save(FILE* stream) override {
        fprintf(stream, "C\n");
        fprintf(stream, "%d %d %d\n", _x, _y, _r);
    }
    void load(FILE* stream) override {
        fscanf(stream, "%d %d %d\n", &_x, &_y, &_r);
    }
};

class CShapeArray {
private:
    vector<CShape*> shapes;
public:
    virtual CShape* createShape(char code) {
        return nullptr;
    }
    void loadShapes(string filename) {
        FILE* stream;
        int count;
        char code;
        CShape* shape;

        if ((stream = fopen(filename.c_str(), "r")) != nullptr) {
            fscanf(stream, "%d\n", &count);
            for (int i = 0; i < count; i++) {
                fscanf(stream, "%c\n", &code);
                shape = createShape(code);
                if (shape != nullptr) {
                    shape->load(stream);
                    shapes.push_back(shape);
                }
            }
            fclose(stream);
        }
    }
    virtual ~CShapeArray() {
        for (const auto& s : shapes)
            delete s;
    }
};
class CMyShapeArray : public CShapeArray {
public:
    CShape* createShape(char code) override {
        CShape* shape = nullptr;
        switch (code)
        {
        case 'P':
            shape = new CPoint(0, 0);
            break;
        case 'C':
            shape = new CCircle(0, 0, 0);
            break;
        default:
            break;
        }
        return shape;
    }
};

int main()
{
    const string filename = "data.txt";
    FILE* stream;
    CShape* shape;
    if ((stream = fopen(filename.c_str(), "w")) != nullptr) {
        fprintf(stream, "%d\n", 2);
        shape = new CPoint(10, 20);
        shape->save(stream);
        delete shape;
        shape = new CCircle(30, 40, 5);
        shape->save(stream);
        delete shape;
        fclose(stream);
    }
    CMyShapeArray shapeArray;
    shapeArray.loadShapes(filename);
}

