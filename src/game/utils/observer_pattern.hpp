#ifndef _OBSERVER_PATTERN
#define _OBSERVER_PATTERN

#include <vector>

using namespace std;


template<typename Event>
class Observer {

    public:
        virtual void update (const Event & event) = 0;
        virtual ~Observer() = default;

};


template<typename Event>
class Subject {

    private:
        vector<Observer<Event> *> observers;

    public:
        void attach (Observer<Event> * observer);
        void detach (Observer<Event> * observer);
        void notify (const Event & event);

};


#include "game/utils/observer_pattern.tpp"


#endif
