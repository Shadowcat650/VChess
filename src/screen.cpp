//
// Created by ShadowCat650 on 4/5/23.
//

#include "screen.h"


U8 screen::getObjectClicked(position postionClicked) {
    for (object o : objects) {
        if (_pointInBox(postionClicked, o.origin, o.width, o.height)) {
            return o.id;
        }
    }
    return 255;
}

void screen::createObject(U8 id, position position, int width, int height) {
    if (isValidId(id)) {
        objects.push_back({id, position, width, height});
    } else {
        cout << "ERROR can't create objects with duplicate ids";
    }
}

void screen::destroyObject(U8 id) {
    vector<object> newObjects;
    for (object o : objects) {
        if (o.id != id) {
            newObjects.push_back(o);
        }
    }
    objects = newObjects;
}

bool screen::isValidId(U8 id) {
    for (object o : objects) {
        if (o.id == id) {
            return false;
        }
    }
    return true;
}

bool screen::_pointInBox(position point, position boxOrigin, int boxWidth, int boxHeight) {
    position bottomRight = {boxOrigin.x + boxWidth, boxOrigin.y + boxHeight};
    return (point.x >= boxOrigin.x && point.x <= bottomRight.x && point.y >= boxOrigin.y && point.y <= bottomRight.y);
}
