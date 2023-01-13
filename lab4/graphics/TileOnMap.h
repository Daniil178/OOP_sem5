#ifndef OOP_SEM5_TILEONMAP_H
#define OOP_SEM5_TILEONMAP_H

#include "TileCoordinates.h"
#include "../application/Game.h"
#include <set>

namespace RPG {

//static const std::string root_path = "/mnt/c/Users/danii";
static const std::string root_path = "/home/usik-dan";
//static const std::string level_path = "/ClionProjects/OOP_sem5/lab4/src/maps/TestMap.txt";
static const std::string level_path = "src/maps/TestMap.txt";
//static const std::string tileset_path = "/ClionProjects/OOP_sem5/lab4/src/textures/tileset.png";
static const std::string tileset_path = "src/textures/tileset.png";
//static const std::string font_path = "/ClionProjects/OOP_sem5/lab4/src/textures/solo5.ttf";
static const std::string font_path = "src/textures/solo5.ttf";
static const std::string window_title = "Operation";
static const uint32_t font_size = 9;
static const float scale = 4.f;
static const sf::Vector2i tile_size(16, 16);

class TileOnMap {
public:
    TileOnMap(const sf::Texture &textures, const sf::Text &text, const sf::Vector2i &tile_size, float scale = 4.f);

    void load(RPG::Level &level);

    void drawCells(sf::RenderWindow &window) const;

    void drawUnits(sf::RenderWindow &window) const;

    void drawTexts(sf::RenderWindow &window) const;

    static std::set<RPG::coordinate>&
    LoS(RPG::Map &map_, std::set<RPG::coordinate> &visible_cells, int x1, int y1, int x2, int y2, int height);

private:
    float scale;

    const sf::Texture &textures;
    const sf::Text &text_;
    std::vector<sf::Sprite> sprite_map;
    std::vector<sf::Sprite> sprite_units;
    std::vector<sf::Text> texts;
    sf::Vector2i tile_size;
    std::vector<sf::Vertex> vertices;

};

static void draw(sf::RenderWindow& window, sf::Texture& texture, sf::Text& text, RPG::Level& level) {
    RPG::TileOnMap tileMap(texture, text, tile_size, scale);
    tileMap.load(level);
    window.clear(sf::Color::Black);
    tileMap.drawCells(window);
    tileMap.drawUnits(window);
    tileMap.drawTexts(window);
    window.display();
}

} // RPG
#endif //OOP_SEM5_TILEONMAP_H
