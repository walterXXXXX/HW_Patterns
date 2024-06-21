#include <iostream>
#include <vector>
#include <memory>
#include <fstream>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {} 
    virtual void onFatalError(const std::string& message) {}
};

class WarningObserver : public Observer {
public:
    void onWarning(const std::string& message) override {
        std::cout << message << std::endl;
    }
};

class ErrorObserver : public Observer {
public:
    ErrorObserver(std::string& fileName) : fileName_(fileName) {}
    void onError(const std::string& message) override {
        std::ofstream file;
        file.open(fileName_, std::ios::app);
        if (file.is_open())
            file << message << std::endl;
        else
            throw std::runtime_error("Ошибка открытия файла");
        file.close();
    }
private:
    std::string fileName_;
};

class FatalErrorObserver : public Observer {
public:
    FatalErrorObserver(std::string& fileName) : fileName_(fileName) {}

    void onFatalError(const std::string& message) override {
        std::cout << message << std::endl;
        std::ofstream file;
        file.open(fileName_, std::ios::app);
        if (file.is_open())
            file << message << std::endl;
        else
            throw std::runtime_error("Ошибка открытия файла");
        file.close();
    }
private:
    std::string fileName_;
};

class Observed {
public:
    void addObserver(std::weak_ptr<Observer> observer) {
        observers.push_back(observer);
    }
    void warning(const std::string& message) const {
        for (auto observer : observers)
            if (auto strong_ptr = observer.lock())
                strong_ptr->onWarning(message);      
    }
    void error(const std::string& message) const {
        for (auto observer : observers)
            if (auto strong_ptr = observer.lock())
                strong_ptr->onError(message);
    }
    void fatalError(const std::string& message) const {
        for (auto observer : observers)
            if (auto strong_ptr = observer.lock())
                strong_ptr->onFatalError(message);
    }


private:
    std::vector<std::weak_ptr<Observer>> observers;
};

int main() { 
    std::string logFileName = "log.txt";
    WarningObserver warningObserver;
    ErrorObserver errorObserver(logFileName);
    FatalErrorObserver fatalErrorObserver(logFileName);

    warningObserver.onWarning("Warning message");
    errorObserver.onError("Error message");
    fatalErrorObserver.onFatalError("Fatal error message");

    return 0;
}