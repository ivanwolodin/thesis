#pragma once

#include <fstream>
#include <string>
#include <cmath>
#include <iostream>

#include "constants.h"

using std::string;
using std::ofstream;

using std::cout;
using std::endl;


inline void output_flag_file() {
    ofstream filestr;
    string fileName = "CORRUPTED.txt";
    filestr.open(fileName);
    filestr.close();
}


inline void check_health(){
    double sum = 0.0;
    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            sum += pressure[i][j];
        }
    }
    
    sum = 0.0;
    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            sum += temperature[i][j];
        }
    }
    
    sum = 0.0;
    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            sum += rho[i][j];
        }
    }
    
    if (!std::isfinite(sum)) { 
        output_flag_file();
        exit(EXIT_FAILURE);
    }
    
    // sum = 0.0;
    // for (int i = 0; i <= Nx - 1; i++) {
    //     for (int j = 0; j <= Ny - 1; j++) {
    //         sum += rho[i][j];
    //     }
    // }
    // if (!std::isfinite(sum)) { 
    //     output_flag_file();
    //     exit(EXIT_FAILURE);
    // }

}
