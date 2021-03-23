#include <source/sfml_facades/screen.h>

Screen::Screen(sf::RenderWindow* window) :
            width_(sf::VideoMode::getDesktopMode().width),
            height_(sf::VideoMode::getDesktopMode().height),
            window_(window) {
    window_->create(sf::VideoMode(width_, height_), "SFML works!");
    background_color_ = sf::Color(80, 80, 80);
}
Screen::~Screen() {
    delete window_;
}
void Screen::Clear() {
    window_->clear(background_color_);
}
void Screen::Draw(const sf::Shape& shape) {
    window_->draw(shape);
}
void Screen::Display() {
    window_->display();
}
bool Screen::IsOpen() const {
    return window_->isOpen();
}
void Screen::Close() {
    window_->close();
}
