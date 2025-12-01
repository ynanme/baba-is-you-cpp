#ifndef _OBSERVER_PATTERN
#define _OBSERVER_PATTERN

#include <vector>

using namespace std;


template<typename Event>
class Observer {

    public:
        virtual void update (Event event) = 0;

};


template<typename Event>
class Subject {

    private:
        vector<Observer<Event> *> observers;

    public:
        void attach (Observer<Event> * observer);
        void detach (Observer<Event> * observer);
        void notify (Event event);

};


#include "observer_pattern.tpp"


#endif
