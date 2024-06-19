#include <string>
#include <iostream>
#include <memory>
#include <algorithm>

// через "delete text_block;" мы сможем удалить только объект ItalicText, а BoldText и Text получается "утекут";
// чтобы избежать утечки памяти, предлагаю заменить сырые указатели на shared_ptr;
// unique_ptr не применяю, т.к. декоратор не должен забрать себе исходный объект в единоличное владение

class Text {
public:
    virtual void render(const std::string& data) const {
        std::cout << data;
    }
};


class DecoratedText : public Text {
public:
//    explicit DecoratedText(Text* text) : text_(text) {}
//    Text* text_;
    explicit DecoratedText(std::shared_ptr<Text> text) : text_(text) {}
    std::shared_ptr<Text> text_;
};

class ItalicText : public DecoratedText {
public:
//    explicit ItalicText(Text* text) : DecoratedText(text) {}
    explicit ItalicText(std::shared_ptr<Text> text) : DecoratedText(text) {}
    void render(const std::string& data)  const {
        std::cout << "<i>";
        text_->render(data);
        std::cout << "</i>";
    }
};

class BoldText : public DecoratedText {
public:
//    explicit BoldText(Text* text) : DecoratedText(text) {}
    explicit BoldText(std::shared_ptr<Text> text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<b>";
        text_->render(data);
        std::cout << "</b>";
    }
};


class Paragraph : public DecoratedText {
public:
    explicit Paragraph(std::shared_ptr<Text> text) : DecoratedText(text) {}
    void render(const std::string& data) const {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
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
        std::cout << "<a href=";
        text_->render(data1);
        std::cout << ">";
        text_->render(data2);
        std::cout << "<a/>";
    }
};

int main() { 
    // auto text_block = new ItalicText(new BoldText(new Text()));
    std::shared_ptr<Text> text_block; 
    
    text_block = std::make_shared<ItalicText>(std::make_shared<BoldText>(std::make_shared<Text>()));
    text_block->render("Hello world");
    std::cout << std::endl;

    text_block = std::make_shared<Paragraph>(std::make_shared<Text>());
    text_block->render("Hello world");
    std::cout << std::endl;
   
    text_block = std::make_shared<Reversed>(std::make_shared<Text>());
    text_block->render("Hello world");
    std::cout << std::endl;

    auto link_block = std::make_shared<Link>(std::make_shared<Text>());
    link_block->render("netology.ru", "Hello world");
    std::cout << std::endl;
}