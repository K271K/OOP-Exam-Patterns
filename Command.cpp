#include <iostream>
#include <conio.h>
#include <map>
#include <stack>

using namespace std;

class Point {
private:
    int _x, _y;
public:
    Point(int x, int y) : _x(x), _y(y) {

    }
    void move(int dx, int dy) {
        _x += dx;
        _y += dy;
    }
    void report() {
        printf("Point is: %d, %d\n", _x, _y);
    }
    virtual ~Point() {

    }
};

class Command {
public:
    Command() {

    }
    virtual void execute(Point* selection) = 0;
    virtual void unexecute() = 0;
    virtual Command* clone() = 0;
    virtual ~Command() {};
};

class MoveCommand : public Command {
private:
    Point* _selection;
    int _dx;
    int _dy;
public:
    MoveCommand(int dx, int dy) {
        printf("MoveCommand::MoveCommand(%d, %d)\n", dx, dy);
        _dx = dx;
        _dy = dy;
        _selection = nullptr;
    }
    void execute(Point* selection) override {
        printf("MoveCommand::execute(Point *selection)\n");
        _selection = selection;
        if (_selection != nullptr)
            _selection->move(_dx, _dy);
    }
    void unexecute() override {
        printf("MoveCommand::unexecite()\n");
        if (_selection != nullptr) 
            _selection->move(-_dx, -_dy);      
    }
    Command* clone() override {
        printf("MoveCommand::clone()\n");
        return new MoveCommand(_dx, _dy);
    }
    ~MoveCommand() {
        printf("MoveCommand::~MoveCommand()\n");
    }
};

int main()
{
    map<char, Command*> commands;
    commands['a'] = new MoveCommand(-10, 0);
    commands['d'] = new MoveCommand(10, 0);
    commands['w'] = new MoveCommand(0, -10);
    commands['s'] = new MoveCommand(0, 10);

    Point* selection = new Point(0, 0);
    selection->report();

    stack<Command*> history;

    char key;
    do {
        key = _getch();
        Command* command = commands[key];
        if (command != nullptr) {
            Command* newcommand = command->clone();
            newcommand->execute(selection);
            history.push(newcommand);
        }
        if (key == 'z' && !history.empty()) {
            Command* lastcommand = history.top();
            lastcommand->unexecute();
            delete lastcommand;
            history.pop();
        }
        selection->report();

    } while (key != 27);

    while (!history.empty()) {
        delete history.top();
        history.pop();
    }

    delete commands['a'];
    delete commands['d'];
    delete commands['w'];
    delete commands['s'];

    delete selection;

    system("pause");
}

