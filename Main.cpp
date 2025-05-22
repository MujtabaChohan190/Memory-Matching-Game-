#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <ctime>
#include <vector>
#include <windows.h> // for Sleep()
#include <algorithm> // for std::random_shuffle

// --------------------- Card Class ---------------------
class Card
{
private:
    sf::RectangleShape shape;
    sf::Texture *frontTexture;
    sf::Texture *backTexture;
    sf::Texture *hoverTexture;
    bool isMatched;
    bool isFlipped;
    int id; // Used for matching

public:
    Card(float x, float y, float size, int id, sf::Texture *front, sf::Texture *back, sf::Texture *hover)
        : id(id), frontTexture(front), backTexture(back), hoverTexture(hover), isMatched(false), isFlipped(false)
    {
        shape.setSize(sf::Vector2f(size, size));
        shape.setPosition(x, y);
        shape.setTexture(back);
    }

    void flip()
    {
        isFlipped = !isFlipped;
        shape.setTexture(isFlipped ? frontTexture : backTexture);
    }

    void reveal()
    {
        isFlipped = true;
        shape.setTexture(frontTexture);
    }

    void hide()
    {
        isFlipped = false;
        shape.setTexture(backTexture);
    }

    void markMatched()
    {
        isMatched = true;
    }

    bool isHovered(sf::RenderWindow &window)
    {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        return shape.getGlobalBounds().contains(mousePos);
    }

    void hover()
    {
        if (!isMatched && !isFlipped)
            shape.setTexture(hoverTexture);
    }

    void unhover()
    {
        if (!isMatched && !isFlipped)
            shape.setTexture(backTexture);
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(shape);
    }

    bool matched() const { return isMatched; }
    bool flipped() const { return isFlipped; }
    int getId() const { return id; }
};
