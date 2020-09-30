#ifndef ENTITY_H_
#define ENTITY_H_

class Entity {
    public:
        Entity(int, int, char);
        char GetAvatar();
        int GetX();
        int GetY();
        void SetPos(int, int);
        void Move(int, int);
        short GetColorPair();

    protected:
        int x_,y_;
        char avatar_;
        short color_pair_;
};
#endif
