#ifndef OBSERVER_H
#define OBSERVER_H

#include <memory>
#include <string>
#include <vector>
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& message) = 0;
};

class ConsoleObserver : public Observer {
public:
    void update(const std::string& message) override;
};

class FileObserver : public Observer {
private:
    std::string filename;
    
public:
    FileObserver(const std::string& filename = "log.txt");
    void update(const std::string& message) override;
};

class Observable {
private:
    std::vector<std::shared_ptr<Observer>> observers;
    
public:
    void addObserver(std::shared_ptr<Observer> observer);
    void removeObserver(std::shared_ptr<Observer> observer);
    void notifyObservers(const std::string& message);
};

#endif