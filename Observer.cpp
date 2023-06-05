#include <iostream>
#include <vector>

using namespace std;

class CObject;

class CObserver {
public: 
    virtual void onSubjectChanged(CObject* who) = 0;
    virtual ~CObserver(){}
};

class CObject {
private:
    vector<CObserver*> _observers;
public:
    void addObserver(CObserver* o) {
        _observers.push_back(o);
    }
    void notifyEveryone() {
        for (const auto& o : _observers)
            o->onSubjectChanged(this);
    }
    virtual ~CObject() {

    }
};

class CAnimal : public CObject {
public:
    string name;
    string lastsound;
    CAnimal(string aname) {
        name = aname;
        lastsound = "";
    }
    void say(string sound) {
        lastsound = sound;
        printf("\nAnimal %s : '%s'\n", name.c_str(), sound.c_str());
        notifyEveryone();
    }
};

class CChild : public CObserver {
public:
    string name;
    CChild(string cname) {
        name = cname;
    }
    void onSubjectChanged(CObject* who) {
        printf("CChild %s : '%s had just said : %s'\n", name.c_str(), ((CAnimal*)who)->name.c_str(), ((CAnimal*)who)->lastsound.c_str());
    }
};

int main()
{
    CAnimal cat("Zorra");
    CAnimal dog("Sharik");
    CAnimal unknown("Cheburashka");

    CChild Ravil("Ravil");
    CChild Emil("Emil");
    CChild Lesha("Lesha");

    cat.addObserver(&Ravil);
    cat.addObserver(&Emil);
    dog.addObserver(&Lesha); 

    cat.say("mew-mew!");
    dog.say("wow-wow!");
    cat.say("I am a cat!");
    dog.say("I am a dog!");
    unknown.say("nobody cares about me");
}

