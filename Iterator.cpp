#include <iostream>

using namespace std;

class CIterator {
public:
    virtual void first() = 0;
    virtual int getCurrentItem() = 0;
    virtual void setCurrentItem(int item) = 0;
    virtual void next() = 0;
    virtual bool isEOL() = 0;
    virtual ~CIterator() {

    }
};

class CArray {
private:
    int* _values;
    int _size;
public:
    CArray(int size) {
        _size = size;
        _values = new int[_size];
    }
    int getCount(){
        return _size;
    }
    int getValue(int index) {
        return _values[index];
    }
    void setValue(int index, int item) {
        _values[index] = item;
    }
    CIterator* createIterator(string);

    virtual ~CArray(){
        delete[] _values;
    }

};

class CRegularArrayIterator : public CIterator {
private:
    CArray* _arr;
    int _current_index;
public:
    CRegularArrayIterator(CArray* arr) {
        _arr = arr;
        _current_index = 0;
    }
    void first() override {
        _current_index = 0;
    }
    int getCurrentItem() override {
        return _arr->getValue(_current_index);
    }
    void setCurrentItem(int item) override {
        _arr->setValue(_current_index, item);
    }
    void next() override {
        _current_index++;
    }
    bool isEOL() override {
        return _current_index == _arr->getCount();
    }
};
class CPositiveOnlyArrayIterator : public CIterator {
private:
    CArray* _arr;
    int _current_index;
public:
    CPositiveOnlyArrayIterator(CArray* arr) {
        _arr = arr;
        _current_index = 0;
    }
    void first() override {
        _current_index = 0;
        while (!isEOL() && getCurrentItem() <= 0) {
            _current_index++;
        }
    }
    int getCurrentItem() override {
        return _arr->getValue(_current_index);
    }
    void setCurrentItem(int item) override {
        _arr->setValue(_current_index, item);
    }
    void next() override {
        if (!isEOL())
            _current_index++;
        while (!isEOL() && getCurrentItem() < 0) {
            _current_index++;
        }
    }
    bool isEOL() override {
        return _current_index == _arr->getCount();
    }
};

CIterator* CArray::createIterator(string type) {
    if (type == "REGULAR")
        return new CRegularArrayIterator(this);
    else if (type == "POSITIVEONLY")
        return new CPositiveOnlyArrayIterator(this);
    else
        throw "Wrong iterator type!";
}

int main()
{
    CArray arr(10);
    for (int i = 0; i < arr.getCount(); i++) {
        arr.setValue(i, rand() - RAND_MAX / 2);
    }

    CIterator* it = arr.createIterator("REGULAR");
    for (it->first(); !it->isEOL(); it->next()) {
        printf("%d ", it->getCurrentItem());
    }
    printf("\n");

    CIterator* it2 = arr.createIterator("POSITIVEONLY");
    for (it2->first(); !it2->isEOL(); it2->next()) {
        printf("%d ", it2->getCurrentItem());
    }
    printf("\n");
}

