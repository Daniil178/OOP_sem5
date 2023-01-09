#include "TileOnMap.h"
#include <sstream>
#include "help_func.h"

// Процедура Line of Sight.
std::set<RPG::coordinate>& TileOnMap::LoS(RPG::Map& map_, std::set<RPG::coordinate>& visible_cells, int x1, int y1, int x2, int y2, int height) {
    int dx, dy, sdx, sdy, dx_abs, dy_abs, x, y, px, py;

    dx = x2 - x1;
    dy = y2 - y1;
    dx_abs = abs(dx);
    dy_abs = abs(dy);
    sdx = RPG::Sgn(dx);
    sdy = RPG::Sgn(dy);
    x = dy_abs / 2;
    y = dx_abs / 2;
    px = x1;
    py = y1;
    if (dx_abs >= dy_abs) {
        for (int i = 0; i < dx_abs; ++i) {
            y += dy_abs;
            if (y >= dx_abs) {
                y -= dx_abs;
                py += sdy;
            }
            px += sdx;
            visible_cells.insert(std::make_pair(height - py - 1, px)); //рисуем тайл на экране
            //если здесь стена или плитка, остановка...
            if (map_[std::make_pair(height - py - 1, px)]->is_visible() == false) {
                return visible_cells;
            }
        }
    }
    else {
        for (int i = 0; i < dy_abs; ++i) {
            x += dx_abs;
            if (x > dy_abs) {
                x -= dy_abs;
                px += sdx;
            }
            py += sdy;
            visible_cells.insert(std::make_pair(height - py - 1, px)); //рисуем тайл на экране
            //если здесь стена или плитка, остановка...
            if (map_[std::make_pair(height - py - 1, px)]->is_visible() == false) {
                return visible_cells;
            }
        }
    }
    return visible_cells;
}

TileOnMap::TileOnMap(const sf::Texture &textures, const sf::Text& text, const sf::Vector2i &tile_size, float scale)
                                                                                                :
                                                                                                textures(textures),
                                                                                                text_(text),
                                                                                                tile_size(tile_size),
                                                                                                scale(scale)
                                                                                                {}

void TileOnMap::load(RPG::Level &level) {
    RPG::GenerateTables();
    RPG::Map& map_ = level.map_;
    auto operatives = level.operatives;
    auto enemies = level.enemies;

    const int height = level.get_size().first;
    const int width = level.get_size().second;

    RPG::coordinate c;
    std::set<RPG::coordinate> draw_cell;
    for (auto& oper : operatives) {
        int x = oper->get_position().first;
        int y = oper->get_position().second;
        for (int i = 0; i < 120; ++i) {
            c = RPG::CastRay(x, y, oper->get_params().view_radius, i * 3, height, width);
            LoS(map_, draw_cell, y, height - x - 1, c.first, c.second, height);
        }
    }
    for (auto& cell_coord : draw_cell) {
        sf::Sprite cell_sprite = sf::Sprite(textures);
        RPG::coordinate sprite_coord = cell_tile_coords.at(map_[cell_coord]->get_type());
        cell_sprite.setTextureRect({sprite_coord.first, sprite_coord.second, tile_size.x, tile_size.y});
        cell_sprite.setPosition(cell_coord.second * tile_size.y * scale, cell_coord.first * tile_size.x * scale);
        cell_sprite.setScale(scale, scale);
        sprite_map.push_back(cell_sprite);

        //vertices[cell_coord.first * width + cell_coord.second] = cell_sprite;
    }

    RPG::coordinate sprite_coord;
    for (auto& oper : operatives) {
        sf::Text text(text_);
        std::ostringstream status;
        status << "HP: " << oper->get_params().current_health << " / " << oper->get_params().max_health << "\n"
        << "Time: " << oper->get_params().current_time << " / " << oper->get_params().max_time << "\n"
        << "Ammo: " << oper->get_current_weapon()->get_ammo_num() << " / " << oper->get_current_weapon()->get_params().bas_params.max_ammo << std::endl;
        text.setString(status.str());
        text.setPosition(oper->get_position().second * tile_size.y * scale,
                         oper->get_position().first * tile_size.x * scale);
        texts.push_back(text);
        sf::Sprite oper_sprite = sf::Sprite(textures);
        sprite_coord = unit_tile_coords.at(RPG::OPERATIVE);
        oper_sprite.setTextureRect({sprite_coord.first, sprite_coord.second, tile_size.x, tile_size.y});
        oper_sprite.setPosition(oper->get_position().second * tile_size.y * scale,
                                oper->get_position().first * tile_size.x * scale);
        oper_sprite.setScale(scale, scale);
        sprite_units.push_back(oper_sprite);
    }

    for (auto& enemy : enemies) {
        bool flag_see = false;
        for (auto& cell_coord : draw_cell) {
            if (cell_coord == enemy->get_position()) {
                flag_see = true;
                break;
            }
        }
        if (flag_see == false) {
            continue;
        }

        sf::Sprite enemy_sprite(textures);
        sf::Text text(text_);
        std::ostringstream status;
        status << "HP: " << enemy->get_params().current_health << " / " << enemy->get_params().max_health;
        text.setString(status.str());
        text.setPosition(enemy->get_position().second * tile_size.y * scale,
                         enemy->get_position().first * tile_size.x * scale);
        texts.push_back(text);

        sprite_coord = unit_tile_coords.at(enemy->get_type());
        enemy_sprite.setTextureRect({sprite_coord.first, sprite_coord.second, tile_size.x, tile_size.y});
        enemy_sprite.setPosition(enemy->get_position().second * tile_size.y * scale,
                                 enemy->get_position().first * tile_size.x * scale);
        enemy_sprite.setScale(scale, scale);
        sprite_units.push_back(enemy_sprite);
    }

}

void TileOnMap::drawCells(sf::RenderWindow &window) const {
    for (auto& cell_sprite : sprite_map) {
        window.draw(cell_sprite);
    }
}

void TileOnMap::drawUnits(sf::RenderWindow &window) const {
    for (const auto& unit: sprite_units) {
        window.draw(unit);
    }
}

void TileOnMap::drawTexts(sf::RenderWindow &window) const {
    for (const auto& message: texts)
        window.draw(message);
}