#include <SFML/Graphics.hpp>

const int WIDTH = 10;
const int HEIGHT = 20;

int field[WIDTH][HEIGHT] = { 0 };

int figures[7][4] =
{
    1,3,5,7, // I
    2,4,5,7, // S
    3,5,4,6, // Z
    3,5,4,7, // T
    2,3,5,7, // L
    3,5,7,6, // J
    2,3,4,5, // O

};

struct Point
{
    int x, y;
} a[4], b[4];

int main()
{
    sf::RenderWindow window(sf::VideoMode(320, 480), "name");

    sf::Texture texture;

    texture.loadFromFile("textures/tiles.png");

    sf::Sprite sprite(texture);

    sprite.setTextureRect(sf::IntRect(0, 0, 18, 18));

    int dx = 0;

    while(window.isOpen())
    {
        sf::Event event;
        
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Left) dx = -1;
            else if(event.key.code == sf::Keyboard::Right) dx = 1;
        }

        for(int i = 0; i < 4; i++) a[i].x += dx;

        int n = 3;

        if(a[0].x == 0)
        {
            for(int i = 0; i < 4; i++)
            {   
                a[i].x = figures[n][i] % 2;
                a[i].y = figures[n][i] / 2;
            }
        }
        dx = 0;

        window.clear(sf::Color::White);

        for(int i = 0; i < 4; i++)
        {
            sprite.setPosition(a[i].x * 18, a[i].y * 18);
            window.draw(sprite);
        }
        
        window.display();
    }
    return 0;
}