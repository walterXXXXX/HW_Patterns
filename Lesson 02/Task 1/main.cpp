#include <string>
#include <iostream>
#include <memory>
#include <algorithm>

class Text {
public:
    Text(std::ostream& output) : output_(output) {}
    virtual void render(const std::string& data) const {
        output_ << data;
    }
    std::ostream& output_;
};


class DecoratedText : public Text {
public:
    explicit DecoratedText(std::shared_ptr<Text> text) : Text(text->output_), text_(text) {}
protected:
    std::shared_ptr<Text> text_;
};

class ItalicText : public DecoratedText {
public:
    explicit ItalicText(std::shared_ptr<Text> text) : DecoratedText(text) {}
    void render(const std::string& data)  const {
        output_ << "<i>";
        text_->render(data);
        output_ << "</i>";
    }
};

class BoldText : public DecoratedText {
public:
    explicit BoldText(std::shared_ptr<Text> text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        output_ << "<b>";
        text_->render(data);
        output_ << "</b>";
    }
};

class Paragraph : public DecoratedText {
public:
    explicit Paragraph(std::shared_ptr<Text> text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        output_ << "<p>";
        text_->render(data);
        output_ << "</p>";
    }
};

class Reversed : public DecoratedText {
public:
    explicit Reversed(std::shared_ptr<Text> text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::string reverseData = data;
        std::reverse(reverseData.begin(), reverseData.end());
        text_->render(reverseData);
    }
};

class Link : public DecoratedText {
public:
    explicit Link(std::shared_ptr<Text> text) : DecoratedText(text) {}
    void render(const std::string& data1, const std::string& data2) const {
        output_ << "<a href=";
        text_->render(data1);
        output_ << ">";
        text_->render(data2);
        output_ << "<a/>";
    }
};

int main() { 
    std::shared_ptr<Text> text_block; 
    std::ostream& output = std::cout;

    text_block = std::make_shared<ItalicText>(std::make_shared<BoldText>(std::make_shared<Text>(output)));
    text_block->render("Hello world");
    output << std::endl;

    text_block = std::make_shared<Paragraph>(std::make_shared<Text>(output));
    text_block->render("Hello world");
    output << std::endl;
   
    text_block = std::make_shared<Reversed>(std::make_shared<Text>(output));
    text_block->render("Hello world");
    output << std::endl;

    auto link_block = std::make_shared<Link>(std::make_shared<Text>(output));
    link_block->render("netology.ru", "Hello world");
    output << std::endl;
}