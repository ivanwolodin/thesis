#pragma once

#include "constants.h"


inline void no_slip_bottom(std::vector<std::vector<std::vector<double>>>& func) {
    for (int i = 0; i <= Nx - 1; i++) {
        func[i][0][2] = func[i][0][4];
        func[i][0][5] = func[i][0][7];
        func[i][0][6] = func[i][0][8];
    }
}


inline void no_slip_left(std::vector<std::vector<std::vector<double>>>& func) {
    for (int j = 0; j <= Ny - 1; j++) {
        func[0][j][8] = func[0][j][6];
        func[0][j][1] = func[0][j][3];
        func[0][j][5] = func[0][j][7];
    }
}


inline void no_slip_right(std::vector<std::vector<std::vector<double>>>& func) {
    for (int j = 0; j <= Ny - 1; j++) {
        func[Nx - 1][j][3] = func[Nx - 1][j][1];
        func[Nx - 1][j][7] = func[Nx - 1][j][5];
        func[Nx - 1][j][6] = func[Nx - 1][j][8];
    }
}


inline void no_slip_upper(std::vector<std::vector<std::vector<double>>>& func) {
    for (int i = 0; i <= Nx - 1; i++) {
        func[i][Ny - 1][4] = func[i][Ny - 1][2];
        func[i][Ny - 1][7] = func[i][Ny - 1][5];
        func[i][Ny - 1][8] = func[i][Ny - 1][6];
    }
}


inline void free_slip_left(std::vector<std::vector<std::vector<double>>>& func) {
    for (int j = 0; j <= Ny - 1; j++) {
        func[0][j][8] = func[0][j][7];
        func[0][j][1] = func[0][j][3];
        func[0][j][5] = func[0][j][6];
    }
}


inline void free_slip_right(std::vector<std::vector<std::vector<double>>>& func) {
    for (int j = 0; j <= Ny - 1; j++) {
        func[Nx - 1][j][3] = func[Nx - 1][j][1];
        func[Nx - 1][j][7] = func[Nx - 1][j][8];
        func[Nx - 1][j][6] = func[Nx - 1][j][5];
    }
}



// Обработка нижней стенки (ИСКЛЮЧАЯ углы)
inline void no_slip_bottom_no_corners(std::vector<std::vector<std::vector<double>>>& func) {
    // Цикл от 1 до Nx-2 (пропускаем 0 и Nx-1)
    for (int i = 1; i < Nx - 1; i++) {
        func[i][0][2] = func[i][0][4];
        func[i][0][5] = func[i][0][7];
        func[i][0][6] = func[i][0][8];
    }
}

// Обработка верхней стенки (ИСКЛЮЧАЯ углы)
inline void no_slip_upper_no_corners(std::vector<std::vector<std::vector<double>>>& func) {
    for (int i = 1; i < Nx - 1; i++) {
        func[i][Ny - 1][4] = func[i][Ny - 1][2];
        func[i][Ny - 1][7] = func[i][Ny - 1][5];
        func[i][Ny - 1][8] = func[i][Ny - 1][6];
    }
}

// Обработка левой стенки (ИСКЛЮЧАЯ углы)
inline void no_slip_left_no_corners(std::vector<std::vector<std::vector<double>>>& func) {
    for (int j = 1; j < Ny - 1; j++) {
        func[0][j][1] = func[0][j][3];
        func[0][j][5] = func[0][j][7];
        func[0][j][8] = func[0][j][6];
    }
}

// Обработка правой стенки (ИСКЛЮЧАЯ углы)
inline void no_slip_right_no_corners(std::vector<std::vector<std::vector<double>>>& func) {
    for (int j = 1; j < Ny - 1; j++) {
        func[Nx - 1][j][3] = func[Nx - 1][j][1];
        func[Nx - 1][j][7] = func[Nx - 1][j][5];
        func[Nx - 1][j][6] = func[Nx - 1][j][8];
    }
}

// Специальная функция для 4-х углов
inline void handle_corners(std::vector<std::vector<std::vector<double>>>& func) {
    // Левый нижний (0,0) - отражаем все, что летит В угол
    func[0][0][1] = func[0][0][3]; 
    func[0][0][2] = func[0][0][4]; 
    func[0][0][5] = func[0][0][7]; 
    
    // Правый нижний 
    func[Nx-1][0][3] = func[Nx-1][0][1]; 
    func[Nx-1][0][2] = func[Nx-1][0][4];
    func[Nx-1][0][6] = func[Nx-1][0][8]; 

    // Левый верхний
    func[0][Ny-1][1] = func[0][Ny-1][3];
    func[0][Ny-1][4] = func[0][Ny-1][2];
    func[0][Ny-1][8] = func[0][Ny-1][6]; 

    // Правый верхний 
    func[Nx-1][Ny-1][3] = func[Nx-1][Ny-1][1];
    func[Nx-1][Ny-1][4] = func[Nx-1][Ny-1][2]; 
    func[Nx-1][Ny-1][7] = func[Nx-1][Ny-1][5];
}



inline void periodic_left(std::vector<std::vector<std::vector<double>>>& func) {
    for (int j = 0; j <= Ny - 1; j++) {
        func[0][j][8] = func[Nx - 1][j][8];
        func[0][j][1] = func[Nx - 1][j][1];
        func[0][j][5] = func[Nx - 1][j][5];
    }
}


inline void periodic_right(std::vector<std::vector<std::vector<double>>>& func) {
    for (int j = 0; j <= Ny - 1; j++) {
        func[Nx - 1][j][6] = func[0][j][6];
        func[Nx - 1][j][3] = func[0][j][3];
        func[Nx - 1][j][7] = func[0][j][7];
    }
}


inline void periodic_upper(std::vector<std::vector<std::vector<double>>>& func) {
    for (int i = 0; i <= Nx - 1; i++) {
        func[i][Ny - 1][4] = func[i][0][4];
        func[i][Ny - 1][7] = func[i][0][7];
        func[i][Ny - 1][8] = func[i][0][8];
    }
}


inline void periodic_bottom(std::vector<std::vector<std::vector<double>>>& func) {
    for (int i = 0; i <= Nx - 1; i++) {
        func[i][0][6] = func[i][Ny - 1][6];
        func[i][0][2] = func[i][Ny - 1][2];
        func[i][0][5] = func[i][Ny - 1][5];
    }
}


inline void lid_driven_top(std::vector<std::vector<std::vector<double>>>& func, double u_wall) {
    for (int i = 1; i <= Nx - 2; i++) {
        rho[i][Ny - 1] = 2 * (func[i][Ny - 1][4] + func[i][Ny - 1][8] + func[i][Ny - 1][7])
                         + func[i][Ny - 1][1] + func[i][Ny - 1][3] + func[i][Ny - 1][0];
    }

    //  krueger et al p. 180
    for (int i = 1; i <= Nx - 2; i++) {
        func[i][Ny - 1][4] = func[i][Ny - 1][2]; // normal velocity is zero

        func[i][Ny - 1][7] = func[i][Ny - 1][5] - (1.0 * rho[i][Ny - 1] * u_wall) / (6.0 * sound_speed_squared) +
                          0.5 * (func[i][Ny - 1][1] - func[i][Ny - 1][3]);

        func[i][Ny - 1][8] = func[i][Ny - 1][6] + (1.0 * rho[i][Ny - 1] * u_wall) / (6.0 * sound_speed_squared) -
                          0.5 * (func[i][Ny - 1][1] - func[i][Ny - 1][3]);
    }
}


inline void set_temperature_left(std::vector<std::vector<std::vector<double>>>& func, double temperature_value){
    double t_wall_left = temperature_value;
    for (int j = 0; j <= Ny - 1; j++) {
        func[0][j][1] = t_wall_left * (w[1] + w[3]) - func[0][j][3];
        func[0][j][5] = t_wall_left * (w[5] + w[7]) - func[0][j][7];
        func[0][j][8] = t_wall_left * (w[8] + w[6]) - func[0][j][6];
    }
}


inline void set_temperature_right(std::vector<std::vector<std::vector<double>>>& func, double temperature_value){
    double t_wall_right = temperature_value;
    for (int j = 0; j <= Ny - 1; j++) {
        func[Nx - 1][j][6] = t_wall_right * (w[6] + w[8]) - func[Nx - 1][j][8];
        func[Nx - 1][j][3] = t_wall_right * (w[3] + w[1]) - func[Nx - 1][j][1];
        func[Nx - 1][j][7] = t_wall_right * (w[7] + w[5]) - func[Nx - 1][j][5];
    }
}


inline void set_temperature_bottom(std::vector<std::vector<std::vector<double>>>& func, double temperature_value){
    double t_wall_bottom = temperature_value;
    for (int i = 0; i <= Nx - 1; i++) {
        func[i][0][6] = t_wall_bottom * (w[6] + w[8]) - func[i][0][8];
        func[i][0][2] = t_wall_bottom * (w[2] + w[4]) - func[i][0][4];
        func[i][0][5] = t_wall_bottom * (w[5] + w[7]) - func[i][0][7];
    }
}


inline void set_temperature_upper(std::vector<std::vector<std::vector<double>>>& func, double temperature_value){
    double t_wall_upper = temperature_value;
    for (int i = 0; i <= Nx - 1; i++) {
        func[i][Ny - 1][4] = t_wall_upper * (w[4] + w[2]) - func[i][Ny - 1][2];
        func[i][Ny - 1][7] = t_wall_upper * (w[7] + w[5]) - func[i][Ny - 1][5];
        func[i][Ny - 1][8] = t_wall_upper * (w[8] + w[6]) - func[i][Ny - 1][6];
    }
}


inline void set_adiabatic_left(std::vector<std::vector<std::vector<double>>>& func){
    for (int j = 0; j <= Ny - 1; j++) {
        for (int k = 0; k < Nc; k++) {
            func[0][j][k] = func[1][j][k];
        }
    }
}


inline void set_adiabatic_right(std::vector<std::vector<std::vector<double>>>& func){
    for (int j = 0; j <= Ny - 1; j++) {
        for (int k = 0; k < Nc; k++) {
            func[Nx - 1][j][k] = func[Nx - 2][j][k];
        }
    }
}


inline void set_adiabatic_bottom(std::vector<std::vector<std::vector<double>>>& func){
    for (int i = 0; i <= Nx - 1; i++) {
        for (int k = 0; k < Nc; k++) {
            func[i][0][k] = func[i][1][k];
        }
    }
}


inline void set_adiabatic_top(std::vector<std::vector<std::vector<double>>>& func){
    for (int i = 0; i <= Nx - 1; i++) {
        for (int k = 0; k < Nc; k++) {
            func[i][Ny - 1][k] = func[i][Ny - 2][k];
        }
    }
}

