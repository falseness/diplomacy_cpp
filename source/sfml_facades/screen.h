#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#ifndef DIPLOMACY_CPP_SCREEN_H
#define DIPLOMACY_CPP_SCREEN_H

class Screen {
    /*
    Пользователь можешь изменить window_, тогда всё сломается.
    Поэтому используется паттерн Фасад.
    */
    sf::RenderWindow* window_;
public:
    size_t width_;
    size_t height_;
    Screen(sf::RenderWindow* window);
    ~Screen();
    void Clear();
    void Draw(const sf::Shape& shape);
    void Display();
    bool IsOpen() const;
    void Close();
};

#endif //DIPLOMACY_CPP_SCREEN_H
