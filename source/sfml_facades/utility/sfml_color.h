#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <source/utility/color.h>

#pragma once

// можно было бы создать конструктор копирования, но я не хочу менять классы чужой библиотеки, чтобы случайно ничего
// не сломать
sf::Color create_color(const Color&);
