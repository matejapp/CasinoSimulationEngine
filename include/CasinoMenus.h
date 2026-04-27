#pragma once

class Casino;
class Player;

class CasinoMenus
{
public:
    static void showCasinoMenu(const Player &player, const Casino &casino);
    static void showBlackjackMenu(const Player &player, const Casino &casino);
    static void showRouletteMenu(const Player &player, const Casino &casino);
};