#ifndef OOP_SEM5_TILEONMAP_H
#define OOP_SEM5_TILEONMAP_H

#include "TileCoordinates.h"
#include "../application/Game.h"
#include <set>

class TileOnMap {
public:
    TileOnMap(const sf::Texture& textures, const sf::Text& text, const sf::Vector2i& tile_size, float scale = 4.f);

    void load(RPG::Level& level);

    void drawCells(sf::RenderWindow& window) const;
    void drawUnits(sf::RenderWindow& window) const;
    void drawTexts(sf::RenderWindow& window) const;


private:
    float scale;
    static std::set<RPG::coordinate>& LoS(RPG::Map& map_, std::set<RPG::coordinate>& visible_cells, int x1, int y1, int x2, int y2, int height);
    const sf::Texture& textures;
    const sf::Text& text_;
    std::vector<sf::Sprite> sprite_map;
    std::vector<sf::Sprite> sprite_units;
    std::vector<sf::Text> texts;
    sf::Vector2i tile_size;
    std::vector<sf::Vertex> vertices;

};
#endif //OOP_SEM5_TILEONMAP_H
