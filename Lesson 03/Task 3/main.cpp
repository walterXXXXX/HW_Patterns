#include <iostream>
#include <memory>
#include <exception>
#include <string>
#include <fstream>

class LogMessage {
public:
    enum class Type {
        WARNING,
        ERROR,
        FATAL_ERROR,
        UNKNOWN,
    };

    virtual ~LogMessage() = default;
    virtual Type type() const = 0;
    virtual const std::string& message() const = 0;
};

class WarningMessage : public LogMessage {
public:
    Type type() const override { 
        return Type::WARNING; 
    }
    const std::string& message() const override {
        static std::string s = "<warning message>";
        return s;
    }
};

class ErrorMessage : public LogMessage {
public:
    Type type() const override {
        return Type::ERROR;
    }
    const std::string& message() const override {
        static std::string s = "<error message>";
        return s;
    }
};

class FatalErrorMessage : public LogMessage {
public:
    Type type() const override {
        return Type::FATAL_ERROR;
    }
    const std::string& message() const override {
        static std::string s = "<fatal error message>";
        return s;
    }
};

class UnknownMessage : public LogMessage {
public:
    Type type() const override {
        return Type::UNKNOWN;
    }
    const std::string& message() const override {
        static std::string s = "<unknown message>";
        return s;
    }
};

class LogHandler {
public:
    explicit LogHandler(std::unique_ptr<LogHandler> next) : next_(std::move(next)) {}
    virtual ~LogHandler() = default;

    void recieveMessage(const LogMessage& msg) {
        if (handleMessage(msg))
            return;
        if (!next_)
            throw std::runtime_error("Ошибка! Отсутствует обработчик сообщения");
        next_->recieveMessage(msg);
    }

private:
    std::unique_ptr<LogHandler> next_;
    virtual bool handleMessage(const LogMessage& msg) = 0;
};

class WarningMessageHandler : public LogHandler {
public:
    using LogHandler::LogHandler;
private:
    bool handleMessage(const LogMessage& msg) override {
        if (msg.type() != LogMessage::Type::WARNING)
            return false;
        std::cout << "Warning message: " << msg.message() << std::endl;
        return true;
    }
};

class ErrorMessageHandler : public LogHandler {
public:
//    using LogHandler::LogHandler;
    ErrorMessageHandler(std::unique_ptr<LogHandler> next, const std::string fileName) : LogHandler(std::move(next)), fileName_(fileName) {}
private:
    bool handleMessage(const LogMessage& msg) override {
        if (msg.type() != LogMessage::Type::ERROR)
            return false;
        //std::cout << "Error message: " << msg.message() << std::endl;
        std::ofstream file;
        file.open(fileName_, std::ios::app);
        if (!file.is_open())
            throw std::runtime_error("Ошибка открытия log файла для записи" + msg.message() + "\n");
        file << "Error message: " << msg.message() << std::endl;
        return true;
    }
    std::string fileName_;
};

class FatalErrorMessageHandler : public LogHandler {
public:
    using LogHandler::LogHandler;
private:
    bool handleMessage(const LogMessage& msg) override {
        if (msg.type() != LogMessage::Type::FATAL_ERROR)
            return false;
        throw std::runtime_error("Exception: " + msg.message() + "\n");
        return true;
    }
};

class UnknownMessageHandler : public LogHandler {
public:
    using LogHandler::LogHandler;
private:
    bool handleMessage(const LogMessage& msg) override {
        if (msg.type() != LogMessage::Type::UNKNOWN)
            return false;
        throw std::runtime_error("Exception: " + msg.message() + "\n");
        return true;
    }
};

int main() { 
    auto unknownMH = std::make_unique<UnknownMessageHandler>(nullptr);
    auto warningMH = std::make_unique<WarningMessageHandler>(std::move(unknownMH));
    auto errorMH = std::make_unique<ErrorMessageHandler>(std::move(warningMH), "output.txt");
    auto logMH = std::make_unique<FatalErrorMessageHandler>(std::move(errorMH));

    try {
 //       logMH->recieveMessage(FatalErrorMessage());
        logMH->recieveMessage(ErrorMessage());
        logMH->recieveMessage(WarningMessage());
        logMH->recieveMessage(UnknownMessage());
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}