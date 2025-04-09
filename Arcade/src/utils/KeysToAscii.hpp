/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** KeysToAscii.hpp
*/

#ifndef KEYSTOASCII_HPP
    #define KEYSTOASCII_HPP
#include <ANAL/Events.hpp>

namespace analUtils {

    static char analKeyToAscii(const ANAL::Keys key)
    {
        switch (key)
        {
            case ANAL::Keys::KEY_A:
                return 'A';
                break;
            case ANAL::Keys::KEY_B:
                return 'B';
                break;
            case ANAL::Keys::KEY_C:
                return 'C';
                break;
            case ANAL::Keys::KEY_D:
                return 'D';
                break;
            case ANAL::Keys::KEY_E:
                return 'E';
                break;
            case ANAL::Keys::KEY_F:
                return 'F';
                break;
            case ANAL::Keys::KEY_G:
                return 'G';
                break;
            case ANAL::Keys::KEY_H:
                return 'H';
                break;
            case ANAL::Keys::KEY_I:
                return 'I';
                break;
            case ANAL::Keys::KEY_J:
                return 'J';
                break;
            case ANAL::Keys::KEY_K:
                return 'K';
                break;
            case ANAL::Keys::KEY_L:
                return 'L';
                break;
            case ANAL::Keys::KEY_M:
                return 'M';
                break;
            case ANAL::Keys::KEY_N:
                return 'N';
                break;
            case ANAL::Keys::KEY_O:
                return 'O';
                break;
            case ANAL::Keys::KEY_P:
                return 'P';
                break;
            case ANAL::Keys::KEY_Q:
                return 'Q';
                break;
            case ANAL::Keys::KEY_R:
                return 'R';
                break;
            case ANAL::Keys::KEY_S:
                return 'S';
                break;
            case ANAL::Keys::KEY_T:
                return 'T';
                break;
            case ANAL::Keys::KEY_U:
                return 'U';
                break;
            case ANAL::Keys::KEY_V:
                return 'V';
                break;
            case ANAL::Keys::KEY_W:
                return 'W';
                break;
            case ANAL::Keys::KEY_X:
                return 'X';
                break;
            case ANAL::Keys::KEY_Y:
                return 'Y';
                break;
            case ANAL::Keys::KEY_Z:
                return 'Z';
                break;
            case ANAL::Keys::KEY_0:
                return '0';
                break;
            case ANAL::Keys::KEY_1:
                return '1';
                break;
            case ANAL::Keys::KEY_2:
                return '2';
                break;
            case ANAL::Keys::KEY_3:
                return '3';
                break;
            case ANAL::Keys::KEY_4:
                return '4';
                break;
            case ANAL::Keys::KEY_5:
                return '5';
                break;
            case ANAL::Keys::KEY_6:
                return '6';
                break;
            case ANAL::Keys::KEY_7:
                return '7';
                break;
            case ANAL::Keys::KEY_8:
                return '8';
                break;
            case ANAL::Keys::KEY_9:
                return '9';
                break;
            default:
                return '?';
        }
    }
} // namespace analUtils

#endif //KEYSTOASCII_HPP
