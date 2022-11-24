#ifndef RPG_OBJECT_H
#define RPG_OBJECT_H


namespace RPG {

enum TYPE_OBJECT {
    Item = 0,
    Unit
};

class RPG_Object {
public:
    virtual int get_damage(int);
};

} // RPG

#endif //RPG_OBJECT_H
