// ==========================================================================
//
// File      : tic_tac_due.hpp
// Copyright : kenny.vandoorn@student.hu.nl, 2021
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#pragma once
#include "ssd1331.hpp"
#include <array>

// this file contains Doxygen lines
/// @file

/// \brief
/// Postion
/// \details
/// This class keeps track of everything regarding positions in the grid,
/// and is also responsible for the translation of button chars to grid coordinates.
class position
{
private:
    hwlib::xy pos;
    hwlib::window &w;
    char button_char;
    int pos_owner;

public:
    position(const hwlib::xy pos, hwlib::window &w, const char button_char, int pos_owner = 0)
        : pos(pos), w(w), button_char(button_char), pos_owner(pos_owner)
    {}

    /// Getter for position owner of a coordinate.
    int get_pos_owner()
    {
        return pos_owner;
    }

    /// Draws a circle red/blue on a specific coordinate depending on the pos_owner.
    void draw()
    {
        if (pos_owner == 1)
        {
            auto circle = hwlib::circle(pos, 6, hwlib::red);
            circle.draw(w);
        }
        else if (pos_owner == 2)
        {
            auto circle = hwlib::circle(pos, 6, hwlib::blue);
            circle.draw(w);
        }
    }

    //
    bool check(const char &character, const int player)
    {
        if (character == button_char && pos_owner == 0)
        {
            pos_owner = player;
            return true;
        }
        return false;
    }
}; // class position


/// \brief
/// tic_tac_due
/// \details
/// This class is responsible for initializing, and starting the game of tic-tac-due.
/// It starts the game, and keeps track of player turns.
class tic_tac_due
{
private:

    hwlib::keypad<16> &keypad1;
    hwlib::keypad<16> &keypad2;
    hwlib::window &w;

public:
    tic_tac_due(hwlib::keypad<16> &keypad1, hwlib::keypad<16> &keypad2, hwlib::window &w)
        : keypad1(keypad1), keypad2(keypad2), w(w)
    {
        /// Draw and flush the grid 
        auto line_1 = hwlib::line(hwlib::xy(32, 0), hwlib::xy(32, 64), hwlib::white); line_1.draw(w);
        auto line_2 = hwlib::line(hwlib::xy(64, 0), hwlib::xy(64, 64), hwlib::white); line_2.draw(w);
        auto line_3 = hwlib::line(hwlib::xy(0, 21), hwlib::xy(94, 21), hwlib::white); line_3.draw(w);
        auto line_4 = hwlib::line(hwlib::xy(0, 42), hwlib::xy(94, 42), hwlib::white); line_4.draw(w);
        w.flush();
    }

    /// Define each postion in the grid
    position pos1 = position(hwlib::xy(79, 8), w, '1');
    position pos2 = position(hwlib::xy(47, 8), w, '2');
    position pos3 = position(hwlib::xy(15, 8), w, '3');
    position pos4 = position(hwlib::xy(79, 31), w, '4');
    position pos5 = position(hwlib::xy(47, 31), w, '5');
    position pos6 = position(hwlib::xy(15, 31), w, '6');
    position pos7 = position(hwlib::xy(79, 53), w, '7');
    position pos8 = position(hwlib::xy(47, 53), w, '8');
    position pos9 = position(hwlib::xy(15, 53), w, '9');

    /// Array for positions
    std::array<position *, 9> positions = {&pos1, &pos2, &pos3, &pos4, &pos5, &pos6, &pos7, &pos8, &pos9};

    /// Starts the game and keeps track of turn count.
    void start_game()
    {
        int player_turn = 1;
        int turn_count = 0;

        while (turn_count != 9)
        {
            if (player_turn == 1)
            {
                turn(keypad1, 1);
                player_turn = 2;
            }
            if (player_turn == 2)
                {
                    turn(keypad2, 2);
                    player_turn = 1;
                }
            turn_count++;
        }
    }

    /// Keeps track of player turns and valid character presses.
    void turn(hwlib::keypad<16> &keypad, int player)
    {
        char choice;
        bool valid_choice = false;

        while (!valid_choice)
        {
            while (!choice)
            {
                if (keypad.pressed() != '\0')
                {
                    choice = keypad.pressed();
                }
            }
            for (auto &p : positions)
            {
                if (p->check(choice, player))
                {
                    p->draw();
                    valid_choice = true;
                }
            }
            if (!valid_choice)
            {
                choice = char();
                hwlib::cout << "Please try again!" << hwlib::endl;
                hwlib::wait_ms(200);
                continue;
            }
            w.flush();
        }
    }
}; // class tic_tac_due
