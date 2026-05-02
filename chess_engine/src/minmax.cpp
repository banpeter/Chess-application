//
// Created by peter on 2026. 04. 26..
//
#include <iostream>

int value(std::string name) {

    if (name == "pawn") {
        return 2;
    }
    else if (name == "knight") {
        return 3;
    }
    else if (name == "bishop") {
        return 4;
    }
    else if (name == "rook") {
        return 5;
    }
    else if (name == "queen") {
        return 10;
    }
    else if (name == "king") {
        return 7;
    }

    return 0;



}