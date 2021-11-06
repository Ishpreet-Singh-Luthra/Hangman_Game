#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <queue>
using namespace std;

class GameManager
{
    private:
        const int MAX_TRIES;
        string word;
        string words[10];
        string words1[10];
        string words2[10];
        string words3[10];
        string name_of_player;

    private:
        int Fill_letters (char, string&);
        void High_Scores_Updation(int current_score);

    public:
        GameManager();
        void Player_name_getter();
        void displayRules();
        void Game_start();
        void print_Title();
        void High_Scores_printed();
};

#endif