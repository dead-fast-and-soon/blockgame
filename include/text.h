
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#define DEFAULT_FONT "FiraCode-VF.ttf"

using namespace std;


class Text: public sf::Drawable {
private:

    // TODO better way of managing fonts to avoid duplicate loading
    sf::Font font;
    sf::Text text;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {

        target.draw(text, states);
    }

public:

    /**
     * @brief Construct a new Text object
     *
     * @param text the text to display
     * @param fontname the filename of the font to use
     */
    Text(string text="", string fontname=DEFAULT_FONT) {
        this->font.loadFromFile(fontname);
        this->text.setFont(font);
    }

    void setText(string text) {
        this->text.setString(text);
    }

    void setSize(unsigned int size) {
        this->text.setCharacterSize(size);
    }
};