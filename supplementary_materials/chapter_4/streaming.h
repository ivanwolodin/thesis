#pragma once
#include "constants.h"

inline void streaming(std::vector<std::vector<std::vector<double>>>& func) {
    for (int x = Nx - 1; x >= 1; x--) {
        for (int y = Ny - 1; y >= 0; y--) {
            func[x][y][1] = func[x - 1][y][1];
        }
    }
    
    for (int x = Nx - 1; x >= 0; x--) {
        for (int y = Ny - 1; y >= 1; y--) {
            func[x][y][2] = func[x][y - 1][2];
        }
    }
    
    for (int x = 0; x <= Nx - 2; x++) {
        for (int y = 0; y <= Ny - 1; y++) {
            func[x][y][3] = func[x + 1][y][3];
        }
    }
    
    for (int x = 0; x <= Nx - 1; x++) {
        for (int y = 0; y <= Ny - 2; y++) {
            func[x][y][4] = func[x][y + 1][4];
        }
    }
    
    for (int x = Nx - 1; x >= 1; x--) {
        for (int y = Ny - 1; y >= 1; y--) {
            func[x][y][5] = func[x - 1][y - 1][5];
        }
    }
    
    for (int x = 0; x <= Nx - 2; x++) {
        for (int y = Ny - 1; y >= 1; y--) {
            func[x][y][6] = func[x + 1][y - 1][6];
        }
    }
    
    for (int x = 0; x <= Nx - 2; x++) {
        for (int y = 0; y <= Ny - 2; y++) {
            func[x][y][7] = func[x + 1][y + 1][7];
        }
    }

    for (int x = Nx - 1; x >= 1; x--) {
        for (int y = 0; y <= Ny - 2; y++) {
            func[x][y][8] = func[x - 1][y + 1][8];
        }
    }
}


inline void pre_streaming(
    const std::vector<std::vector<std::vector<double>>>& func,
    std::vector<std::vector<std::vector<double>>>& func_res
){
    for (int x = Nx - 1; x >= 1; x--) {
        for (int y = Ny - 1; y >= 0; y--) {
            func_res[x][y][1] = func[x - 1][y][1];
        }
    }
    
    for (int x = Nx - 1; x >= 0; x--) {
        for (int y = Ny - 1; y >= 1; y--) {
            func_res[x][y][2] = func[x][y - 1][2];
        }
    }
    
    for (int x = 0; x <= Nx - 2; x++) {
        for (int y = 0; y <= Ny - 1; y++) {
            func_res[x][y][3] = func[x + 1][y][3];
        }
    }
    
    for (int x = 0; x <= Nx - 1; x++) {
        for (int y = 0; y <= Ny - 2; y++) {
            func_res[x][y][4] = func[x][y + 1][4];
        }
    }
    
    for (int x = Nx - 1; x >= 1; x--) {
        for (int y = Ny - 1; y >= 1; y--) {
            func_res[x][y][5] = func[x - 1][y - 1][5];
        }
    }
    
    for (int x = 0; x <= Nx - 2; x++) {
        for (int y = Ny - 1; y >= 1; y--) {
            func_res[x][y][6] = func[x + 1][y - 1][6];
        }
    }
    
    for (int x = 0; x <= Nx - 2; x++) {
        for (int y = 0; y <= Ny - 2; y++) {
            func_res[x][y][7] = func[x + 1][y + 1][7];
        }
    }

    for (int x = Nx - 1; x >= 1; x--) {
        for (int y = 0; y <= Ny - 2; y++) {
            func_res[x][y][8] = func[x - 1][y + 1][8];
        }
    }
}