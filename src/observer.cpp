#include "observer.h"
#include <iostream>
#include <fstream>
#include <algorithm>

void ConsoleObserver::update(const std::string& message) {
    std::cout << "[LOG] " << message << std::endl;
}

FileObserver::FileObserver(const std::string& filename) 
    : filename(filename) {}

void FileObserver::update(const std::string& message) {
    std::ofstream file(filename, std::ios_base::app);
    if (file.is_open()) {
        file << message << std::endl;
        file.close();
    }
}

void Observable::addObserver(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

void Observable::removeObserver(std::shared_ptr<Observer> observer) {
    observers.erase(
        std::remove_if(observers.begin(), observers.end(),
            [observer](const std::shared_ptr<Observer>& obs) {
                return obs == observer;
            }),
        observers.end()
    );
}

void Observable::notifyObservers(const std::string& message) {
    for (auto& observer : observers) {
        if (observer) {
            observer->update(message);
        }
    }
}