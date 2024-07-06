#include <fstream>
#include <memory>

class Data {
public:
    Data(std::string data)
        : data_(std::move(data)) {}

    std::string get() {
        return data_;
    }
private:
    std::string data_;
};

class Printable {
public:
    Printable(std::shared_ptr<Data> data) : data_(data) {};
    virtual ~Printable() = default;

    virtual std::string print() const = 0;

protected:
    std::shared_ptr<Data> data_;
};

class PrintAsHTML : public Printable {
    using Printable::Printable;
    std::string print() const override {
        return "<html>" + data_->get() + "<html/>";
    }
};

class PrintAsText : public Printable {
    using Printable::Printable;
    std::string print() const override {
        return data_->get();
    }
};

class PrintAsJSON : public Printable {
    using Printable::Printable;
    std::string print() const override {
        return "{ \"data\": \"" + data_->get() + "\"}";
    }
};

void saveTo(std::ofstream& file, const Printable& printable) {
    file << printable.print();
}

void saveToAsHTML(std::ofstream& file, std::shared_ptr<Data> data) {
    saveTo(file, PrintAsHTML(data));
}

void saveToAsJSON(std::ofstream& file, std::shared_ptr<Data> data) {
    saveTo(file, PrintAsText(data));
}

void saveToAsText(std::ofstream& file, std::shared_ptr<Data> data) {
    saveTo(file, PrintAsJSON(data));
}