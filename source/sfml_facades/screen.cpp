#include <SFML/Graphics.hpp>

class Screen {
    /*
    Пользователь можешь изменить window_, тогда всё сломается. 
    Поэтому используется паттерн Фасад.
    */
    sf::RenderWindow* window_;
public:
    size_t width_;
    size_t height_;
    Screen(sf::RenderWindow* window) : width_(sf::VideoMode::getDesktopMode().width),
            height_(sf::VideoMode::getDesktopMode().height),
            window_(window) {
        window_->create(sf::VideoMode(width_, height_), "SFML works!");
    }
    ~Screen() {
        delete window_;
    }
    void Clear() {
        window_->clear();
    }
    void Draw(const sf::Shape& shape) {
        window_->draw(shape);
    }
    void Display() {
        window_->display();
    }
    bool IsOpen() const {
        return window_->isOpen();
    }
    void Close() {
        window_->close();
    }
};
