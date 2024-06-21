#include <iostream>
#include <fstream>

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

class LogToConsoleCommand : public LogCommand {
public:
    void print(const std::string& message) override {
        std::cout << message << std::endl;
    }
};

class LogToFileCommand : public LogCommand {
public:
    LogToFileCommand(const std::string& fileName) {
        file.open(fileName, std::ios::app);
        if (!file.is_open()) 
            throw std::runtime_error("Ошибка открытия файла");
    }

    void print(const std::string& message) override {
        if (file.is_open())
            file << message << std::endl;
        else
            throw std::runtime_error("Файл не открыт для записи");
    }

    ~LogToFileCommand() {
        if (file.is_open())
            file.close();
    }

private:
    std::ofstream file;
};

void print(LogCommand& command) {
    std::string message = "Сообщение";
    command.print(message);
}

int main() { 
    setlocale(LC_ALL, "");

    LogToConsoleCommand ltc;
    print(ltc);

    LogToFileCommand ltf("Output.txt");
    print(ltf);

    return 0;
}