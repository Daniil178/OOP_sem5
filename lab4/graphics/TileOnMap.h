#ifndef OOP_SEM5_TILEONMAP_H
#define OOP_SEM5_TILEONMAP_H

#include "TileCoordinates.h"
#include "../application/Game.h"
#include <set>

namespace RPG {

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

void draw(sf::RenderWindow& window, sf::Texture& texture, sf::Text& text, RPG::Level& level) {
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
