#include "State.h"


Available::Available(string standByLocation) : standByLocation(standByLocation) {}

void Available::performDuty() {
    cout << "stands by at " << standByLocation << ".\n";
}

Dispatched::Dispatched(string destination) : destination(destination) {}

void Dispatched::performDuty() {
    cout << "travels to " << destination << ".\n";
}

Operating::Operating(string task) : task(task) {}

void Operating::performDuty() {
    cout << "responds to emergency. Task: " << task << ".\n";
}

Recovering::Recovering(int duration) : duration(duration) {}

void Recovering::performDuty() {
    cout << "recovers for " << duration << " units of time.\n";
}
