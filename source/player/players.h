#include <vector>
#include <source/player/player.h>

class Players {
    std::vector<Player> players_;
    size_t whoose_turn_;
public:
    [[nodiscard]] size_t get_whoose_turn() const;
    void NextTurn();
    Players(std::vector<Color>&& players_colors, size_t whoose_turn);
    Player& operator[](size_t);
    const Player& operator[](size_t) const;
};
