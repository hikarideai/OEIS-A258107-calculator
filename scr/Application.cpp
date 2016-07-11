#include "Application.hpp"
#include <fstream>
#include <string>
#include <iostream>

long long toInt(std::string s) {
    long long sum = 0;

    for(size_t i=0; i<s.length(); i++)
        sum = (sum*10) + (s[i] - '0');

    return sum;
}

Application::Application() {

}

void Application::start() {
    initialize();
    loop();
}

void Application::initialize() {
    //Variables
    exit_ = false;
    new_content_ = true;
    char_size_ = 12,
    passed_ = false;

    //Graphics
    window_.create(sf::VideoMode(200, 100), "Base2 like number computer");

    if (!font_.loadFromFile("TerminusTTFWindows-4.40.1.ttf")) {
        //return 1;
    }

    initText(detail_);

    //Load saved state
    std::fstream save;
    save.open("stateSave", save.in);

    if (save.good()) {
        std::string last_number;
        save >> spent_ >> last_number;
        number_.setNumber(last_number);
    } else {
        spent_ = 0;
        number_ = 5;
    }
}

void Application::initText(sf::Text& text) {
    text.setFont(font_);
    text.setString("");
    text.setCharacterSize(char_size_);
    text.setColor(sf::Color::Black);
    text.setStyle(sf::Text::Regular);
}

void Application::loop() {
    try {
        sf::Time time = sf::seconds(spent_);
        long long spent;
        while (!exit_) {
            handleEvents();
            fulfillLogic();

            spent = (time + clock_.getElapsedTime()).asSeconds();
            if (spent_ < spent) {
                spent_ = spent;
                new_content_ = true;
            }

            renderContent();
        }
    } catch (char const *err) {
        std::fstream errorLog;
        errorLog.open("crash.log", errorLog.out);
        errorLog << "BigInteger exception: " << err;
        errorLog.close();
    }

    //When you want to quit, save application's state
    std::fstream save;
    save.open("stateSave", save.out);

    save << spent_ << "\n" << number_.getNumber();

    save.close();

    //And shut down
    window_.close();
}

void Application::handleEvents() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            exit_ = true;
    }
}

void Application::fulfillLogic() {
    passed_ = true;
    //TODO: Make base bound more flexible
    for(char i = 3; i <= 6; i++) {
        if (passed_)
            toBase(i);
    }

    if (passed_) {
        result();
        exit_ = true;
    }

    number_++;
}

void Application::result() {
    std::fstream f;
    f.open("result.txt", f.out);
    f << number_.getNumber();
    f.close();
}

void Application::renderContent() {
    if (new_content_) {
        std::string text_to_apply;
        std::string num = number_.getNumber();
        num.push_back('\n');
        //TODO: Make number clipping work
        //num.resize(15);
        text_to_apply = "Executing " + to_string(spent_) + " seconds\n";
        text_to_apply += "Digits count: " + to_string(num.length()) + "\n";
        text_to_apply += "Base10: " + num;
        //May slow down computing
        //text_to_apply += "Base3: " + toBaseString(3);
        //text_to_apply += "Base4: " + toBaseString(4);
        //text_to_apply += "Base5: " + toBaseString(5);
        //text_to_apply += "Base6: " + toBaseString(6);
        detail_.setString(text_to_apply.c_str());

        window_.clear(sf::Color(255, 255, 255, 255));
        window_.draw(detail_);
        window_.display();
        new_content_ = false;
    }
}

void Application::toBase(char base) {
    BigInteger temp = number_;
    while (temp != 0) {
        if (temp % base > 1) {
            passed_ = false;
            return;
        }
        temp /= base;
    }
}

std::string Application::toBaseString(char base) {
    BigInteger temp = number_;
    std::string num;
    //Idea
    //base 2: 01 10 01 10
    //base 3: 102 021 210
    int max = std::max(base * 4, 30-(30%base));
    for (int i = 0; i < max; i++) {
        if (temp == 0) break;

        if (i%base == 0) num.push_back(' ');
        num.push_back(toInt((temp % base).getNumber()) + '0');
        temp /= base;
    }

    num.push_back('\n');
    return num;
}
