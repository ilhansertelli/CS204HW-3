//
// Created by ILHAN on 2.04.2023.
//
#include "CharStack.h"

#ifndef TAKEHOME3_BOARD_H
#define TAKEHOME3_BOARD_H

struct slot {
    slot * next;
    slot * prev;
    CharStack slotStack;

    slot() {}

};

class Board {

public:
    Board();
    bool noMove(const char & player, const int & step);
    bool targetSlotFull(const int & index);
    int evaluateGame();
    int validMove(const char & player, const int & index, const int & step, const int & direct);
   void destroySlot(const int & index);
    void createSlotBegin(const char & ch, const int & num);
    void createSlotEnd(const char & ch, const int & num);
    void createEmptySlotEnd();
    void clearBoard();
    void movePiece(const int & index, const int & target); // Parameters will be implemented
    void printBoard();

private:
    slot * head;
    slot * tail;
    int xCnt;
    int oCnt;

};

#endif //TAKEHOME3_BOARD_H
