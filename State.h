#ifndef STATE
#define STATE

#include <iostream>

using namespace std;

class State {
    public:
        virtual ~State() = default;
        virtual void performDuty() = 0;
};

class Available : public State {
    private:
        string standByLocation;

    public:
        Available(string standByLocation);
        void performDuty() override;
};

class Dispatched : public State {
    private:
        string destination;

    public:
        Dispatched(string destination);
        void performDuty() override;
};

class Operating : public State {
    private:
        string task;

    public:
        Operating(string task);
        void performDuty() override;
};

class Recovering : public State {
    private:
        int duration;

    public:
        Recovering(int duration);
        void performDuty() override;
};

#endif