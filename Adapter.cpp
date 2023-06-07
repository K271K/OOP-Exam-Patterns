#include <iostream>

using namespace std;

class IArray {
public:
    virtual int getCount() = 0;
    virtual int getValue(int index) = 0;
};

class CArray : public IArray {
private:
    int* _values;
    int _size;
public:
    CArray(int size) {
        _size = size;
        _values = new int[_size];
        for (int i = 0; i < _size; i++)
            _values[i] = rand() % 100;
    }
    int getCount() override {
        return _size;
    }
    int getValue(int index) override {
        return _values[index];
    }
    virtual ~CArray() {
        delete[] _values;
    }
};

class IList {
public:
    virtual void first() = 0;
    virtual int currentValue() = 0;
    virtual void next() = 0;
    virtual bool isEOL() = 0;
};

void foo(IList* list) {
    for (list->first(); !list->isEOL(); list->next())
        printf("%d ", list->currentValue());
    printf("\n");

    list->first();
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", list->currentValue());
        list->next();
    }
    printf("\n");
}

//class CListAdapter : public IList, private CArray {
//private:
//    int _current_index;
//public:
//    CListAdapter(int size) : CArray(size) {
//        _current_index = 0;
//    }
//    void first() override {
//        _current_index = 0;
//    }
//    int currentValue() override {
//        return getValue(_current_index);
//    }
//    void next() override {
//        _current_index++;
//    }
//    bool isEOL() override{
//        return _current_index == getCount();
//    }
//};

class CListAdapter : public IList {
private:
    int _current_index;
    CArray* _arr;
public:
    CListAdapter(CArray* arr) {
        _arr = arr;
    }
    void first() override {
        _current_index = 0;
    }
    int currentValue() override {
        return _arr->getValue(_current_index);
    }
    void next() override {
        _current_index++;
    }
    bool isEOL() override {
        return _current_index == _arr->getCount();
    }
    virtual ~CListAdapter() {

    }
};

int main()
{
    CArray a(10);
    CListAdapter list(&a);
    foo(&list);
}

