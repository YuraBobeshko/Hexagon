#pragma once
#include <SFML/Graphics.hpp>
#include "Constans.h"


class Window : public sf::RenderWindow
{
public:
    Window(sf::VideoMode mode, const sf::String& title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings())
        : sf::RenderWindow(mode, title, style, settings)
    {
        // Тело конструктора класса MyRenderWindow
    }

    // Добавьте сюда свои методы и переменные, если нужно
};

