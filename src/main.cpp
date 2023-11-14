#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

class Shape {
public:
  std::string name;
  float wx, wy;
  float vx;
  float vy;
  float len, wid;

  std::shared_ptr<sf::Shape> shape;
  std::shared_ptr<sf::Text> text;

  Shape(std::string name, float wx, float wy, float vx, float vy, float len,
        float wid, std::shared_ptr<sf::Shape> shape)
      : name(name), wx(wx), wy(wy), vx(vx), vy(vy), len(len), wid(wid),
        shape(shape) {}

  void updatePosition() {
    checkForCollision();
    shape->setPosition(shape->getPosition().x + vx,
                       shape->getPosition().y + vy);
    updateFontPosition();
  }

  void checkForCollision() {
    if (shape->getPosition().x + len >= wx || shape->getPosition().x <= 0) {
      vx *= -1;
    }

    if (shape->getPosition().y + wid >= wy || shape->getPosition().y <= 0) {
      vy *= -1;
    }
  }

  void settxt(std::shared_ptr<sf::Text> txt) { text = txt; }

  void updateFontPosition() {
    text->setPosition(shape->getPosition().x, shape->getPosition().y + wid / 2);
  }
};

int main() {
  float Wx, Wy;
  std::string name;

  std::string fontPath;
  int fontSize, R, G, B;

  std::ifstream in("/home/sahil/bouncing-shapes/config.txt");

  std::vector<std::shared_ptr<Shape>> arr;

  while (in >> name) {

    if (name == "Window") {

      in >> Wx >> Wy;

    } else if (name == "Circle") {

      std::string name;
      float x, y, vx, vy, radius;
      int r, g, b;
      in >> name >> x >> y >> vx >> vy >> r >> g >> b >> radius;

      std::shared_ptr<sf::CircleShape> circ =
          std::make_shared<sf::CircleShape>(radius);
      circ->setFillColor(sf::Color(r, g, b));
      circ->setPosition(x, y);
      std::shared_ptr<Shape> object = std::make_shared<Shape>(
          name, Wx, Wy, vx, vy, radius * 2, radius * 2, circ);
      arr.push_back(object);

    } else if (name == "Rectangle") {

      std::string name;
      float x, y, vx, vy, W, H;
      int r, g, b;
      in >> name >> x >> y >> vx >> vy >> r >> g >> b >> W >> H;

      std::shared_ptr<sf::RectangleShape> rect =
          std::make_shared<sf::RectangleShape>(sf::Vector2f(W, H));
      rect->setFillColor(sf::Color(r, g, b));
      rect->setPosition(x, y);
      std::shared_ptr<Shape> object =
          std::make_shared<Shape>(name, Wx, Wy, vx, vy, W, H, rect);
      arr.push_back(object);

    } else if (name == "Font") {
      in >> fontPath >> fontSize >> R >> G >> B;
    }
  }

  sf::RenderWindow window(sf::VideoMode(Wx, Wy), "My Window");
  // window.setFramerateLimit(60);

  sf::Font font;
  if (!font.loadFromFile(fontPath)) {
    std::cout << "not able to load font" << std::endl;
  }

  for (std::shared_ptr<Shape> x : arr) {
    std::shared_ptr<sf::Text> txt = std::make_shared<sf::Text>();
    txt->setFont(font);
    txt->setString(x->name);
    txt->setFillColor(sf::Color(R, G, B));
    txt->setCharacterSize(fontSize);
    txt->setOrigin(0, (float)txt->getCharacterSize() / 2);
    txt->setPosition(x->shape->getPosition().x,
                     x->shape->getPosition().y + (x->wid) / 2);
    x->settxt(txt);
  }

  while (window.isOpen()) {

    sf::Event event;

    while (window.pollEvent(event)) {

      if (event.type == sf::Event::Closed) {

        window.close();
      }
    }

    window.clear();
    for (std::shared_ptr<Shape> shape : arr) {

      shape->updatePosition();
      window.draw(*(shape->shape));
      window.draw(*(shape->text));
    }
    window.display();
  }
}
