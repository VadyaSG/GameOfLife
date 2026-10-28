#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h> 
void inicialisation(char**& startArr, int& rows, int& columns, char life, char dead);
bool comparison(char** startArr, char** nextArr, int rows, int columns, char dead, int gen, int& isLife);
void generationSwitch(char** startArr, char** nextArr, int rows, int columns);
void rules(char** startArr, char** nextArr, int rows, int columns, char life, char dead);
void universe(char** startArr, int rows, int columns, char life, int& gen, int& isLife);
void deleteArray(char** arr, int rows);

int main() {
    char life{ '*' };
    char dead{ '-' };
    int rows{};
    int columns{};
    char** startArr = nullptr;
    char** nextArr = nullptr;
    inicialisation(startArr, rows, columns, life, dead);
    nextArr = new char* [rows];
    for (int i = 0; i < rows; ++i)
    {
        nextArr[i] = new char[columns] {};
    }
    for (int iRow{}; iRow < rows; ++iRow)
    {
        for (int iCol{}; iCol < columns; ++iCol)
        {

            nextArr[iRow][iCol] = dead;
        }
    }

    int gen{};
    int isLife{};


    while (comparison(startArr, nextArr, rows, columns, dead, gen, isLife))
    {

        universe(startArr, rows, columns, life, gen, isLife);
        rules(startArr, nextArr, rows, columns, life, dead);
        int g{};
        for (int iRow{}; iRow < rows; ++iRow)
        {
            for (int iCol{}; iCol < columns; ++iCol)
            {
                if (startArr[iRow][iCol] == nextArr[iRow][iCol])
                {
                    g++;
                }
            }
        }
        int life2{};
        if (g == rows * columns)
        {
            for (int iRow{}; iRow < rows; ++iRow)
            {
                for (int iCol{}; iCol < columns; ++iCol)
                {
                    if (startArr[iRow][iCol] == life)
                    {
                        ++life2;
                    }
                    std::cout << startArr[iRow][iCol] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "Generation: " << gen + 1 << " Alive cells: " << life2 << " The world is Stagnated, Game Over " << std::endl;
            break;
        }
        generationSwitch(startArr, nextArr, rows, columns);


        Sleep(1000);
        system("cls");
    }


    deleteArray(startArr, rows);
    deleteArray(nextArr, rows);

    return 0;
}

void inicialisation(char**& startArr, int& rows, int& columns, char life, char dead)
{
    std::ifstream worldData("worldStartData.txt");
    if (worldData.fail()) {
        std::cerr << "ERROR: Failed to open worldStartData.txt" << std::endl;
        exit(1);
    }

    worldData >> rows >> columns;


    startArr = new char* [rows];
    for (int i = 0; i < rows; ++i)
    {
        startArr[i] = new char[columns] {};
    }

    int x{}, y{};
    while (worldData >> x >> y)
    {
        if (x >= 0 && x < rows && y >= 0 && y < columns)
        {
            startArr[x][y] = life;

        }

    }
    for (int iRow{}; iRow < rows; ++iRow)
    {
        for (int iCol{}; iCol < columns; ++iCol)
        {
            if (startArr[iRow][iCol] != life)
            {
                startArr[iRow][iCol] = dead;
            }
        }
    }
    worldData.close();
}

bool comparison(char** startArr, char** nextArr, int rows, int columns, char dead, int gen, int& isLife)
{

    int g{};
    int isDead{};
    for (int iRow = 0; iRow < rows; ++iRow)
    {
        for (int iCol = 0; iCol < columns; ++iCol)
        {
            if (nextArr[iRow][iCol] == startArr[iRow][iCol])
            {

                g++;
            }

            if (startArr[iRow][iCol] == dead)
            {
                isDead++;
            }
        }
    }




    if (isDead == rows * columns)
    {
        for (int iRow = 0; iRow < rows; ++iRow)
        {
            for (int iCol = 0; iCol < columns; ++iCol)
            {
                std::cout << startArr[iRow][iCol] << " ";

            }
            std::cout << std::endl;
        }
        std::cout << "Generation: " << gen + 1 << " Alive cells: 0 All are dead. Game over." << std::endl;
        return false;
    }





    return true;

}

void rules(char** startArr, char** nextArr, int rows, int columns, char life, char dead) {
    int countAround;

    for (int iRow = 0; iRow < rows; ++iRow) {
        for (int iCol = 0; iCol < columns; ++iCol) {
            countAround = 0;


            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    if (dx == 0 && dy == 0) continue;
                    int newRow = iRow + dx;
                    int newCol = iCol + dy;
                    if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < columns) {
                        if (startArr[newRow][newCol] == life) countAround++;
                    }
                }
            }


            if (startArr[iRow][iCol] == life) {
                if (countAround < 2 || countAround > 3) {
                    nextArr[iRow][iCol] = dead;
                }
                else {
                    nextArr[iRow][iCol] = startArr[iRow][iCol];
                }
            }
            else {
                if (countAround == 3) {
                    nextArr[iRow][iCol] = life;
                }
            }
        }
    }
}

void generationSwitch(char** startArr, char** nextArr, int rows, int columns) {
    for (int iRow = 0; iRow < rows; ++iRow) {
        for (int iCol = 0; iCol < columns; ++iCol) {
            startArr[iRow][iCol] = nextArr[iRow][iCol];
        }
    }
}

void universe(char** startArr, int rows, int columns, char life, int& gen, int& isLife) {

    ++gen;

    for (int iRow = 0; iRow < rows; ++iRow)
    {
        for (int iCol = 0; iCol < columns; ++iCol)
        {
            std::cout << startArr[iRow][iCol] << " ";
            if (startArr[iRow][iCol] == life)
            {
                isLife++;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Generation: " << gen << " Alive Cells: " << isLife << std::endl;
    isLife = 0;
}

void deleteArray(char** arr, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] arr[i];
    }
    delete[] arr;
}