#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    //  Создаём окно 800x600 с заголовком "2048"
    sf::RenderWindow window(sf::VideoMode(800, 600), "2048");

    // Создаём квадрат (прямоугольник 100x100)
    sf::RectangleShape square(sf::Vector2f(100.f, 100.f));
    square.setFillColor(sf::Color::Red);        // красный цвет
    square.setPosition(350.f, 250.f);            // позиция в центре

    // Главный цикл (пока окно открыто)
    while (window.isOpen()) {
        // Обработка событий
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Очистка окна
        window.clear(sf::Color::Black);

        // Рисуем квадрат
        window.draw(square);

        // Показываем нарисованное
        window.display();
    }

    return 0;
}