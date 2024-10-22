//
// Created by ShadowCat650 on 4/5/23.
//

#ifndef VELOCITYCHESS_SCREEN_H
#define VELOCITYCHESS_SCREEN_H
#include "definitions.h"


class screen {
public:
    U8 getObjectClicked(position postionClicked);
    void createObject(U8 id, position position, int width, int height);
    void destroyObject(U8 id);

    bool isValidId(U8 id);
private:
    vector<object> objects;

    bool _pointInBox(position point, position boxOrigin, int boxWidth, int boxHeight);
};


#endif //VELOCITYCHESS_SCREEN_H
