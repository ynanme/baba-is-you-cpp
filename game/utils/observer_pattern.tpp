#include <algorithm>

using namespace std;


template<typename Event>
void Subject<Event> :: attach (Observer<Event> * observer) {
    observers.push_back(observer);
}

template<typename Event>
void Subject<Event> :: detach (Observer<Event> * observer) {
    observers.erase(
        remove(observers.begin(), observers.end(), observer),
        observers.end()
    );
}

template<typename Event>
void Subject<Event> :: notify (Event event) {
    for (Observer<Event> * observer: observers) {
        observer->update(event);
    }
}
