#ifndef APPLICATION_HPP_INCLUDED
#define APPLICATION_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include <deque>
#include "BigInteger.h"

class Application {
  public:
    Application();
    void start();

  private:
    sf::RenderWindow window_;
    sf::Font font_;
    sf::Clock clock_;
    long long spent_;
    short char_size_;
    sf::Text detail_;
    bool exit_,
         new_content_,
         passed_;
    BigInteger number_;

    void initialize();
    void initText(sf::Text &text);
    void loop();
    void handleEvents();
    void fulfillLogic();
    void renderContent();

    void onResize();
    void onClose();

    void toBase(char base);
    std::string toBaseString(char base);
    void result();
};

#endif // APPLICATION_HPP_INCLUDED
