#ifndef PROJECT_STAGE2_INCLUDE_PLAYER_H_
#define PROJECT_STAGE2_INCLUDE_PLAYER_H_

#include <string>

#define MOVE_SUCCESS 1
#define PLAYER_HP 100
#define BASE_DMG 1
#define MAX_ARM 20

#define MOVE 11

#include <vector>

#include "enemy.h"
#include "map.h"

struct suit {
    bool armor;
    bool helmet;
    bool shield;
    bool pants;
    bool t_shirt;
};

bool is_enemy(size_t &character);
void print_found(size_t clothes);
void print_mob(size_t type);
bool print_clothes(std ::string user_act);
std::string is_clothes(size_t &val, bool &flag);


class Player : public Map {
 private:
    size_t pos_x;
    size_t pos_y;

    size_t hp;
    size_t dmg;
    size_t arm;
    size_t arm_wgt;

    bool change_pos;

    std::vector <bool> clothes;
    std::stringstream form_msg(actions &acts, bool &battle);
    std::string gear_message(size_t map_type);

 public:
    Player()
    : pos_x(0), pos_y(0), hp(PLAYER_HP), dmg(BASE_DMG), arm(0), arm_wgt(0), change_pos(0) {
      clothes.resize(5);
    }
    explicit Player(Map &map)
    : Map(map), pos_x(0), pos_y(0), hp(PLAYER_HP), dmg(BASE_DMG), arm(0), arm_wgt(0), change_pos(0) {
      clothes.resize(5);
    }
    int action();

    size_t get_hp();
    size_t get_dmg();

    int set_guard(Clothes &armor);
    int set_move(std::string str, actions data);
    int set_arm(std::string str);

    void add_arm(Clothes thing);
    void dec_arm(Clothes thing);

    void damage(size_t power);
    void move_left();
    void move_right();
    void move_up();
    void move_down();

    bool check_clothes(size_t pos);

    void print_pos();
};

#endif  // PROJECT_STAGE2_INCLUDE_PLAYER_H_