
#include <map>
#include <vector>

#include "board.h"
#include "constants.h"

using std::map;
using std::vector;
using key = sf::Keyboard::Key;


const Vector2f Board::offset = sf::Vector2f(300, 100);


Board::Board(int x, int y): size(x, y) {

    int thickness = 2;

    // set rectangle sizes

    u.setSize(sf::Vector2f(size.x * BLOCK_SIZE, 0));
    d.setSize(sf::Vector2f(size.x * BLOCK_SIZE, 0));

    l.setSize(sf::Vector2f(0, size.y * BLOCK_SIZE));
    r.setSize(sf::Vector2f(0, size.y * BLOCK_SIZE));

    // set outline color/thickness

    u.setOutlineColor(sf::Color::White);
    d.setOutlineColor(sf::Color::White);
    l.setOutlineColor(sf::Color::White);
    r.setOutlineColor(sf::Color::White);

    u.setOutlineThickness(thickness);
    d.setOutlineThickness(thickness);
    l.setOutlineThickness(thickness);
    r.setOutlineThickness(thickness);

    // set positioning

    u.setPosition(offset + sf::Vector2f(0, -thickness));
    d.setPosition(offset + sf::Vector2f(0, thickness + size.y * BLOCK_SIZE));
    l.setPosition(offset + sf::Vector2f(-thickness, 0));
    r.setPosition(offset + sf::Vector2f(thickness + size.x * BLOCK_SIZE, 0));
}


void inline Board::draw(RenderTarget& target, RenderStates states) const {

    target.draw(u, states);
    target.draw(d, states);
    target.draw(l, states);
    target.draw(r, states);

    for(auto v: controlled_blocks)
        target.draw(*v, states);

    for(auto v: blocks)
        target.draw(*v, states);
}


void Board::spawnBlock(int x, int y, bool as_origin) {

    Block* block = new Block(offset, sf::Vector2i(x, y));
    controlled_blocks.push_back(block);

    if(as_origin)
        origin_block = block;
}

void Board::spawnBlock(int x, int y) { spawnBlock(x, y, false); }


void Board::rotateBlocks(Rotation rot) {

    // no-op if no origin block exists
    if(origin_block == nullptr) return;

    Vector2i axis = origin_block->getPosition();

    int sin, cos;

    switch(rot) {
    case ROT_90:
        sin = 1; cos = 0; break;

    case ROT_180:
        sin = 0; cos = -1; break;

    case ROT_270:
        sin = -1; cos = 0; break;
    }

    map<Block*, Vector2i> translations;

    // calculate rotation

    for(auto block: controlled_blocks) {

        Vector2i pos = block->getPosition();

        if(pos == axis) continue;

        Vector2i vec = pos - axis; // get position WRT origin

        int x = (vec.x * cos - vec.y * sin) + axis.x;
        int y = (vec.x * sin + vec.y * cos) + axis.y;

        translations.insert({block, Vector2i(x, y)});
    }

    // check collisions

    for(auto pair: translations) {
        if(not checkPosition(pair.second.x, pair.second.y))
            return; // stop rotation
    }

    // do translations

    for(auto pair: translations)
        (pair.first)->setPosition(pair.second.x, pair.second.y);
}


bool inline Board::checkPosition(int x, int y) {

    if(x < 0 or x >= size.x) return false;
    if(y < 0 or y >= size.y) return false;

    // check block collisions

    return true;
}


bool Board::checkMovement(int x, int y) {

    for(auto block: controlled_blocks) {

        Vector2i pos = block->getPosition() + Vector2i(x, y);

        if(not checkPosition(pos.x, pos.y))
            return false;
    }
    return true;
}

void Board::moveBlocks(int x, int y) {

    if(x == 0 and y == 0) return;

    if(checkMovement(x, y)) {
        for(auto block: controlled_blocks)
            block->move(x, y);
    }
}


void Board::slideBlocks(Direction dir) {

    Vector2i last_pos = Vector2i(0, 0);
    Vector2i new_pos = last_pos;
    Vector2i adj;

    switch(dir) {
        case UP:
            adj = Vector2i(0, -1); break;
        case DOWN:
            adj = Vector2i(0, +1); break;
        case LEFT:
            adj = Vector2i(-1, 0); break;
        case RIGHT:
            adj = Vector2i(+1, 0); break;
    }

    while(true) {
        new_pos += adj;

        if(not checkMovement(new_pos.x, new_pos.y)) {
            moveBlocks(last_pos.x, last_pos.y);
            break;
        }

        last_pos = new_pos;
    }
}

void Board::lockBlocks() {

    for(auto block: controlled_blocks) {
        block->setColor(sf::Color(200, 200, 200, 255));
    }

    // move all controlled blocks to static blocks vector
    blocks.insert(blocks.end(),
                  std::make_move_iterator(controlled_blocks.begin()),
                  std::make_move_iterator(controlled_blocks.end()));

    controlled_blocks.clear();

	spawnBlock(0, 0);
	spawnBlock(0, 1, true);
	spawnBlock(1, 1);
}

void Board::onKeyPressed(sf::Keyboard::Key code) {

    switch(code) {
    case key::I:
        rotateBlocks(ROT_90);
        break;

    case key::U:
        rotateBlocks(ROT_270);
        break;

    case key::D: // RIGHT
        if(sf::Keyboard::isKeyPressed(key::Space)) {
            slideBlocks(RIGHT);
        } else {
            moveBlocks(+1, 0);
        }
        break;

    case key::A: // LEFT
        if(sf::Keyboard::isKeyPressed(key::Space)) {
            slideBlocks(LEFT);
        } else {
            moveBlocks(-1, 0);
        }
        break;

    case key::W: // UP
        if(sf::Keyboard::isKeyPressed(key::Space)) {
            slideBlocks(UP);
        } else {
            moveBlocks(0, -1);
        }
        break;

    case key::S: // DOWN
        if(sf::Keyboard::isKeyPressed(key::Space)) {
            slideBlocks(DOWN);
        } else {
            moveBlocks(0, +1);
        }
        break;

    case key::LShift:
        lockBlocks();
    }

}

