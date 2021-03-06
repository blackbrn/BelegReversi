#include "controllerField.h"
#include <iostream>
#include <ostream>
#include <istream>
#include <stdio.h>
#include <string>

controllerField::controllerField(int fieldSize)
{
    player[0] = new modelPlayer("Jan", 0);
    player[1] = new modelPlayer("Baran", 0);
    activePlayer = 1;
    otherPlayer = 2;
    gamingField = new modelField(fieldSize);
    gamingField->setFieldValue(gamingField->getFieldSize()/2 - 1,gamingField->getFieldSize()/2 - 1, activePlayer);
    gamingField->setFieldValue(gamingField->getFieldSize()/2,gamingField->getFieldSize()/2, activePlayer);
    gamingField->setFieldValue(gamingField->getFieldSize()/2,gamingField->getFieldSize()/2 - 1, otherPlayer);
    gamingField->setFieldValue(gamingField->getFieldSize()/2 - 1,gamingField->getFieldSize()/2, otherPlayer);
    player[0]->setPlayerStoneCount(2);
    player[1]->setPlayerStoneCount(2);
    std::cout << player[0]->getPlayerName() + " hat Steine: " + std::to_string(player[0]->getPlayerStoneCount()) << std::endl;
    std::cout << player[1]->getPlayerName() + " hat Steine: " + std::to_string(player[1]->getPlayerStoneCount()) << std::endl;
}

void controllerField::startGame()
{
        if (searchPossibleTurns())
        {
            std::cout<<"Mogliche Zuge gefunden"<<std::endl;
        }
        else
        {
            std::cout<<"Keine moglichen Zuge gefunden"<<std::endl;
        }

        gamingField->showFieldDebug();

}

void controllerField::turn(int i, int j)
{
    gamingField->setFieldValue(i, j , activePlayer);
    player[activePlayer - 1]->setPlayerStoneCount((player[activePlayer - 1]->getPlayerStoneCount()) + 1);
}

void controllerField::changeActivePlayer()
{
    int tmpPlayer = otherPlayer;
    otherPlayer = activePlayer;
    activePlayer = tmpPlayer;
}

bool controllerField::isPossibleTurn(int i, int j)
{
            if (i != gamingField->getFieldSize() - 1 && gamingField->getFieldValue(i + 1, j) == otherPlayer)
            {
                int iIterator = i + 1;
                while (iIterator < gamingField->getFieldSize() - 1 && gamingField->getFieldValue(iIterator, j) == otherPlayer)
                {
                    iIterator++;
                }
                if (gamingField->getFieldValue(iIterator, j) == activePlayer) return true;
            }
            if (i != gamingField->getFieldSize() - 1 && j != gamingField->getFieldSize() - 1 && gamingField->getFieldValue(i + 1, j + 1) == otherPlayer)
            {
                int iIterator = i + 1;
                int jIterator = j + 1;
                while (iIterator < gamingField->getFieldSize() - 1 && jIterator < gamingField->getFieldSize() - 1 && gamingField->getFieldValue(iIterator, jIterator) == otherPlayer)
                {
                    iIterator++;
                    jIterator++;
                }
                if (gamingField->getFieldValue(iIterator, jIterator) == activePlayer) return true;
            }
            if (i != gamingField->getFieldSize() - 1 && j != gamingField->getFieldSize() - 1 && gamingField->getFieldValue(i, j + 1) == otherPlayer)
            {
                int jIterator = j + 1;
                while (jIterator < gamingField->getFieldSize() - 1 && gamingField->getFieldValue(i, jIterator) == otherPlayer)
                {
                    jIterator++;
                }
                if (gamingField->getFieldValue(i, jIterator) == activePlayer) return true;
            }
            if (i != 0 && j != gamingField->getFieldSize() - 1 && gamingField->getFieldValue(i - 1, j + 1) == otherPlayer)
            {
                int iIterator = i - 1;
                int jIterator = j + 1;
                while (iIterator > 0 && jIterator < gamingField->getFieldSize() - 1 && gamingField->getFieldValue(iIterator, jIterator) == otherPlayer)
                {
                    iIterator--;
                    jIterator++;
                }
                if (gamingField->getFieldValue(iIterator, jIterator) == activePlayer) return true;
            }
            if (i != 0 && gamingField->getFieldValue(i - 1, j) == otherPlayer)
            {
                int iIterator = i - 1;
                while (iIterator > 0 && gamingField->getFieldValue(iIterator, j) == otherPlayer)
                {
                    iIterator--;
                }
                if (gamingField->getFieldValue(iIterator, j) == activePlayer) return true;
            }
            if (i != 0 && j != 0 && gamingField->getFieldValue(i - 1, j - 1) == otherPlayer)
            {
                int iIterator = i - 1;
                int jIterator = j - 1;
                while (iIterator > 0 && jIterator > 0 && gamingField->getFieldValue(iIterator, jIterator) == otherPlayer)
                {
                    iIterator--;
                    jIterator--;
                }
                if (gamingField->getFieldValue(iIterator, jIterator) == activePlayer) return true;
            }
            if (j != 0 && gamingField->getFieldValue(i, j - 1) == otherPlayer)
            {
                int jIterator = j - 1;
                while (jIterator > 0 && gamingField->getFieldValue(i, jIterator) == otherPlayer)
                {
                     jIterator--;
                }
                if (gamingField->getFieldValue(i, jIterator) == activePlayer) return true;
            }
            if (i != gamingField->getFieldSize() - 1 && j != 0 && gamingField->getFieldValue(i + 1, j - 1) == otherPlayer)
            {
                int iIterator = i + 1;
                int jIterator = j - 1;
                while (iIterator < gamingField->getFieldSize() - 1 && jIterator > 0 && gamingField->getFieldValue(iIterator, jIterator) == otherPlayer)
                {
                    iIterator++;
                    jIterator--;
                }
                if (gamingField->getFieldValue(iIterator, jIterator) == activePlayer) return true;
            }
            return false;
}

void controllerField::flipStones(int i, int j)
{
    //flip down
    if (i != gamingField->getFieldSize() - 1 && gamingField->getFieldValue(i + 1, j) == otherPlayer)
    {
        int iIterator = i + 1;
        while (iIterator < gamingField->getFieldSize() - 1 && gamingField->getFieldValue(iIterator, j) == otherPlayer)
        {
            iIterator++;
        }
        if (gamingField->getFieldValue(iIterator, j) == activePlayer)
        {
            for (int y = i + 1; y < iIterator; y++)
            {
                gamingField->setFieldValue(y, j, activePlayer);
                stoneCount(activePlayer);
            }
        }
    }
    //flip down-right
    if (i != gamingField->getFieldSize() - 1 && j != gamingField->getFieldSize() - 1 && gamingField->getFieldValue(i + 1, j + 1) == otherPlayer)
    {
        int iIterator = i + 1;
        int jIterator = j + 1;
        while (iIterator < gamingField->getFieldSize() - 1 && jIterator < gamingField->getFieldSize() - 1 && gamingField->getFieldValue(iIterator, jIterator) == otherPlayer)
        {
            iIterator++;
            jIterator++;
        }
        if (gamingField->getFieldValue(iIterator, jIterator) == activePlayer)
        {
            int y = i + 1;
            int x = j + 1;
            while (y < iIterator && x < jIterator)
            {
                gamingField->setFieldValue(y, x, activePlayer);
                stoneCount(activePlayer);
                y++;
                x++;
            }
        }
    }
    //flip right
    if (i != gamingField->getFieldSize() - 1 && j != gamingField->getFieldSize() - 1 && gamingField->getFieldValue(i, j + 1) == otherPlayer)
    {
        int jIterator = j + 1;
        while (jIterator < gamingField->getFieldSize() - 1 && gamingField->getFieldValue(i, jIterator) == otherPlayer)
        {
            jIterator++;
        }
        if (gamingField->getFieldValue(i, jIterator) == activePlayer)
        {
            for (int x = j + 1; x < jIterator; x++)
            {
                gamingField->setFieldValue(i, x, activePlayer);
                stoneCount(activePlayer);
            }
        }
    }
    //flip up-right
    if (i != 0 && j != gamingField->getFieldSize() - 1 && gamingField->getFieldValue(i - 1, j + 1) == otherPlayer)
    {
        int iIterator = i - 1;
        int jIterator = j + 1;
        while (iIterator > 0 && jIterator < gamingField->getFieldSize() - 1 && gamingField->getFieldValue(iIterator, jIterator) == otherPlayer)
        {
            iIterator--;
            jIterator++;
        }
        if (gamingField->getFieldValue(iIterator, jIterator) == activePlayer)
        {
            int y = i - 1;
            int x = j + 1;
            while (y > iIterator && x < jIterator)
            {
                gamingField->setFieldValue(y, x, activePlayer);
                stoneCount(activePlayer);
                y--;
                x++;
            }
        }
    }
    //flip up
    if (i != 0 && gamingField->getFieldValue(i - 1, j) == otherPlayer)
    {
        int iIterator = i - 1;
        while (iIterator > 0 && gamingField->getFieldValue(iIterator, j) == otherPlayer)
        {
            iIterator--;
        }
        if (gamingField->getFieldValue(iIterator, j) == activePlayer)
        {
            for (int y = i - 1; y > iIterator; y--)
            {
                gamingField->setFieldValue(y, j, activePlayer);
                stoneCount(activePlayer);
            }
        }
    }
    //flip up-left
    if (i != 0 && j != 0 && gamingField->getFieldValue(i - 1, j - 1) == otherPlayer)
    {
        int iIterator = i - 1;
        int jIterator = j - 1;
        while (iIterator > 0 && jIterator > 0 && gamingField->getFieldValue(iIterator, jIterator) == otherPlayer)
        {
            iIterator--;
            jIterator--;
        }
        if (gamingField->getFieldValue(iIterator, jIterator) == activePlayer)
        {
            int y = i - 1;
            int x = j - 1;
            while (y > iIterator && x > jIterator)
            {
                gamingField->setFieldValue(y, x, activePlayer);
                stoneCount(activePlayer);
                y--;
                x--;
            }
        }
    }
    //flip left
    if (j != 0 && gamingField->getFieldValue(i, j - 1) == otherPlayer)
    {
        int jIterator = j - 1;
        while (jIterator > 0 && gamingField->getFieldValue(i, jIterator) == otherPlayer)
        {
            jIterator--;
        }
        if (gamingField->getFieldValue(i, jIterator) == activePlayer)
        {
            for (int x = j - 1; x > jIterator; x--)
            {
                gamingField->setFieldValue(i, x, activePlayer);
                stoneCount(activePlayer);
            }
        }
    }
    //flip down-left
    if (i != gamingField->getFieldSize() - 1 && j != 0 && gamingField->getFieldValue(i + 1, j - 1) == otherPlayer)
    {
        int iIterator = i + 1;
        int jIterator = j - 1;
        while (iIterator < gamingField->getFieldSize() - 1 && jIterator > 0 && gamingField->getFieldValue(iIterator, jIterator) == otherPlayer)
        {
            iIterator++;
            jIterator--;
        }
        if (gamingField->getFieldValue(iIterator, jIterator) == activePlayer)
        {
            int y = i + 1;
            int x = j - 1;
            while (y < iIterator && x > jIterator)
            {
                gamingField->setFieldValue(y, x, activePlayer);
                stoneCount(activePlayer);
                y++;
                x--;
            }
        }
    }
}

bool controllerField::searchPossibleTurns()
{
    bool foundPossibleTurn = false;
            for (int i = 0; i < gamingField->getFieldSize(); i++)
            {
                for (int j = 0; j < gamingField->getFieldSize(); j++)
                {
                    /* First, set all previous possible fields back to normal */
                    if (gamingField->getFieldValue(i, j) == 3)
                    {
                        gamingField->setFieldValue(i, j , 0);
                    }
                    /* Now, check which fields are possible turns */
                    if (gamingField->getFieldValue(i, j) == 0)
                    {
                        if (isPossibleTurn(i, j))
                        {
                            gamingField->setFieldValue(i, j, 3);
                            foundPossibleTurn = true;
                        }
                    }
                }
            }
            return foundPossibleTurn;
}

void controllerField::startDrawing()
{

}

void controllerField::setFieldSize(int w, int h)
{
    gamingField->setFieldWidth(w);
    gamingField->setFieldHeight(h);
}

int controllerField::getGamingFieldWidth()
{
    return gamingField->getFieldWidth();
}

int controllerField::getGamingFieldHeight()
{
    return gamingField->getFieldWidth();
}

int controllerField::getGamingFieldMatrixSize()
{
    return gamingField->getFieldSize();
}

int controllerField::getGamingFieldElementValue(int i, int j)
{
    return gamingField->getFieldValue(i, j);
}

bool controllerField::evaluateClick(int x, int y)
{
    if (x > 0 && x < gamingField->getFieldWidth() && y > 0 && y < gamingField->getFieldHeight())
    {
        int i = y / (gamingField->getFieldHeight()/gamingField->getFieldSize());
        int j = x / (gamingField->getFieldWidth()/gamingField->getFieldSize());

        if (gamingField->getFieldValue(i, j) == 3)
        {
            (turn(i, j));
            flipStones(i, j);
            std::cout << player[activePlayer - 1]->getPlayerName() + " hat seinen Zug gemacht " << std::endl;
            std::cout << player[0]->getPlayerName() + " hat Steine: " + std::to_string(player[0]->getPlayerStoneCount()) << std::endl;
            std::cout << player[1]->getPlayerName() + " hat Steine: " + std::to_string(player[1]->getPlayerStoneCount()) << std::endl;
            changeActivePlayer();
            searchPossibleTurns();
            return true;
        }
        else
        {
            return false;
        }
    }
}

bool controllerField::checkWin()
{
    //todo
    return true;
}

void controllerField::stoneCount(int color)
{
    player[activePlayer - 1]->setPlayerStoneCount((player[activePlayer - 1]->getPlayerStoneCount()) + 1);
    player[otherPlayer - 1]->setPlayerStoneCount((player[otherPlayer - 1]->getPlayerStoneCount()) - 1);
}
