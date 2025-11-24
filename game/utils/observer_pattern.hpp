#ifndef _OBSERVER_PATTERN
#define _OBSERVER_PATTERN

#include <vector>

using namespace std;


class Observer {

    public:
        virtual void update () = 0;

};


class Subject {

    private:
        vector<Observer *> observers;

    public:
        void attach (Observer * observer);
        void detach (Observer * observer);
        void notify ();

};


#endif