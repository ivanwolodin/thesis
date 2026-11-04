#pragma once

#include "constants.h"


inline void save_previous_velocity() {
    for (int x = 0; x < Nx; x++) {
        for (int y = 0; y < Ny; y++) {
            for (int i = 0; i < 2; i++) {
                u_previous[x][y][i] = u[x][y][i];
            }
        }
    }
}


inline bool check_velocity_convergence() {
    double max_diff = 0.0;
    for (int x = 0; x < Nx; x++) {
        for (int y = 0; y < Ny; y++) {
            for (int i = 0; i < 2; i++) {
                double diff = abs(u[x][y][i] - u_previous[x][y][i]);
                if (diff > max_diff) max_diff = diff;
            }
        }
    }
    return max_diff < numerical_accuracy;
}
