#include "dungeon.h"
#include <iostream>
#include <algorithm>

using std::fill;
using std::cout;
using std::endl;

Dungeon::Dungeon() : grid(kHeight, vector<char>(kWidth, kEmpty)), hero_x_(1), hero_y_(1) {
    Initialize();
    // Placement du héros dans la grille
    grid[hero_x_][hero_y_] = kHero;
}

void Dungeon::Initialize() {
    PlaceWalls();
    PlaceMonsters();
}

void Dungeon::PlaceWalls() {
    fill(grid[0].begin(), grid[0].end(), kWall);                       // Mur du haut
    fill(grid[kHeight - 1].begin(), grid[kHeight - 1].end(), kWall);   // Mur du bas
    for (int i = 0; i < kHeight; ++i) {
        grid[i][0] = kWall;                                            // Mur gauche
        grid[i][kWidth - 1] = kWall;                                   // Mur droit
    }
}

void Dungeon::PlaceMonsters() {
    grid[3][3] = kGolem;
    grid[5][5] = kSpectre;
    grid[7][7] = kFaucheur;
}

void Dungeon::Display() const {
    for (int row = 0; row < kHeight; ++row) {
        for (int col = 0; col < kWidth; ++col) {
            char cell = grid[row][col];
            // Affiche le caractère avec un espace pour plus de clarté
            cout << cell << ' ';
        }
        cout << endl;
    }
}

// Marquer les cases de déplacement valides autour du héros
void Dungeon::MarkValidMoves(int hero_x, int hero_y) {
    const int range = 2;
    for (int dx = -range; dx <= range; ++dx) {
        for (int dy = -range; dy <= range; ++dy) {
            int new_x = hero_x + dx;
            int new_y = hero_y + dy;
            if (new_x >= 0 && new_x < kHeight && new_y >= 0 && new_y < kWidth && grid[new_x][new_y] == kEmpty) {
                grid[new_x][new_y] = kValidMove;
            }
        }
    }
}
