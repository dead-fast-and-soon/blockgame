
/**
 * @brief The outline that shows the play area of the game.
 *
 */

#include <vector>
#include "entity.h"
#include "block.h"

using std::vector;

using sf::Vector2i;
using sf::RenderTarget;
using sf::RenderStates;


class Board: public Entity {
private:

    static const sf::Vector2f offset;

    Vector2i size; // size of the board
    sf::RectangleShape u, d, l, r; // outline shapes

    Block* origin_block = nullptr; // block to rotate around

    vector<Block*> controlled_blocks; // blocks controlled by the player
    vector<Block*> blocks; // static blocks

public:

    enum Rotation { ROT_90, ROT_180, ROT_270 };

    enum Direction { UP, DOWN, LEFT, RIGHT };

    Board(int w, int h);

    ~Board() {
        // delete all pointers in blocks
        for(auto v: blocks)
            delete v;
        blocks.clear();
    }

    /**
     * @brief Spawn a block at the specified coordinates
     *
     * @param x
     * @param y
     */
    void spawnBlock(int x, int y, bool as_origin);

    void spawnBlock(int x, int y);

    /**
     * @brief Lock all controlled blocks
     *
     */
    void lockBlocks();

    void moveBlocks(int x, int y);

    void slideBlocks(Direction dir);

    void rotateBlocks(Rotation rot);

    /**
     * @brief Returns true if a block can be placed at the
     *        specified coordinates.
     *
     * @param x
     * @param y
     */
    bool checkPosition(int x, int y);

    bool checkMovement(int x, int y);

    void draw(RenderTarget& target, RenderStates states) const override;

    void onKeyPressed(sf::Keyboard::Key code) override;
};
