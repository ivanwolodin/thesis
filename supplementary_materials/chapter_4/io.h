#pragma once

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>

#include "constants.h"


using std::string;
using std::endl;
using std::cout;
using std::to_string;
using std::ofstream;
using std::ifstream;
using std::ios;


inline void greetings() {
    std::cout << "Isothermal Phase-Field SRT LBM" << std::endl;
    std::cout << "Simulation started." << std::endl;
}


inline void bye() {
    std::cout << "Simulation is over. Goodbye!" << std::endl;
}


inline void dump_simulation_params()
{
    std::ofstream filestr;
    std::string fileName = "params.txt";

    filestr.open(fileName);
    if (!filestr.is_open()) {
        std::cout << "Error! Could not open file: " << fileName << std::endl;
        return;
    }

    filestr << "=== Simulation parameters ===\n\n";

    // Grid
    filestr << "Grid parameters:\n";
    filestr << "Nx = " << Nx << "\n";
    filestr << "Ny = " << Ny << "\n";
    filestr << "Nc = " << Nc << "\n\n";
    
    //     const double Ampl = 0.05;      // Амплитуда
    // const double omega = 0.001;    
    filestr << "Ampl = " << Ampl << "\n\n";
    filestr << "omega = " << omega << "\n\n";
    // Time & space
    filestr << "dt = " << dt << "\n";
    filestr << "dx = " << dx << "\n";
    filestr << "steps_number = " << steps_number << "\n\n";

    // Physical constants
    filestr << "Physical parameters:\n";
    filestr << "gravity = " << gravity << "\n";
    filestr << "sound_speed_squared = " << sound_speed_squared << "\n\n";

    // Densities
    filestr << "Densities:\n";
    filestr << "rho_l = " << rho_l << "\n";
    filestr << "rho_g = " << rho_g << "\n\n";

    // Relaxation times and transport coefficients
    filestr << "LBM parameters:\n";
    filestr << "tau_f_liquid = " << tau_f_liquid << "\n";
    filestr << "viscosity_liquid = " << viscosity_liquid << "\n";
    filestr << "tau_f_gas = " << tau_f_gas << "\n";
    filestr << "viscosity_gas = " << viscosity_gas << "\n";
    filestr << "tau_g = " << tau_g << "\n";
    filestr << "mobility = " << mobility << "\n\n";
    filestr << "tau_h = " << tau_h << "\n";
    filestr << "heat_capacity = " << heat_capacity << "\n\n";

    // Surface tension / phase-field
    filestr << "Phase-field parameters:\n";
    filestr << "surface_tension_coef = " << surface_tension_coef << "\n";
    filestr << "interface_thickness = " << interface_thickness << "\n";
    filestr << "k = " << k << "\n";
    filestr << "beta = " << beta << "\n\n";
    
    filestr << "Weber_number = " << Weber_number << "\n";
    filestr << "Bond_number = " << Bond_number << "\n\n";
    
    filestr << "ration_gravity_to_amplitude_omegaSquared = " << ration_gravity_to_amplitude_omegaSquared << "\n\n";

    filestr << "kapitza_velocity = " << kapitza_velocity << "\n";
    filestr << "critical_velocity = " << critical_velocity << "\n\n";

    filestr << "=== End of parameters ===\n";

    filestr.close();
}



inline void output_field(int step_time, string which_field) {
    ofstream filestr;

    string fileName = "res/" + which_field + "_" + to_string(step_time) + ".txt";

    filestr.open(fileName);
//    if (filestr == NULL) cout << "error! didn't open the file!" << endl;

    for (int x = 0; x <= Nx - 1; x++) {
        for (int y = 0; y <= Ny - 1; y++) {
            
            if (which_field == "streamline") {
                filestr << x << " " << y << " " << streamline[x][y] << endl;
            }
            
            if (which_field == "v") {
                filestr << x << " " << y << " " << u[x][y][1] << endl;
            }

            if (which_field == "u") {
                filestr << x << " " << y << " " << u[x][y][0] << endl;
            }

            if (which_field == "rho") {
                filestr << x << " " << y << " " << rho[x][y] << endl;
            }
            
            if (which_field == "tau") {
                filestr << x << " " << y << " " << tau[x][y] << endl;
            }
            
            if (which_field == "temperature") {
                filestr << x << " " << y << " " << temperature[x][y] << endl;
            }
            
            if (which_field == "phi") {
                filestr << x << " " << y << " " << phi[x][y] << endl;
            }
            
            if (which_field == "grad_phi_x") {
                filestr << x << " " << y << " " << grad_phi[x][y][0] << endl;
            }
            
            if (which_field == "grad_phi_y") {
                filestr << x << " " << y << " " << grad_phi[x][y][1] << endl;
            }
            
            if (which_field == "pressure") {
                filestr << x << " " << y << " " << pressure[x][y] << endl;
            }
            
            if (which_field == "surface_force_x") {
                filestr << x << " " << y << " " << surface_force[x][y][0] << endl;
            }
            
            if (which_field == "surface_force_y") {
                filestr << x << " " << y << " " << surface_force[x][y][1] << endl;
            }
            
            
            if (which_field == "d_dt_u_phi_x") {
                filestr << x << " " << y << " " << d_dt_u_phi[x][y][0] << endl;
            }
            
            if (which_field == "d_dt_u_phi_y") {
                filestr << x << " " << y << " " << d_dt_u_phi[x][y][1] << endl;
            }
            
            if (which_field == "total_force_x") {
                filestr << x << " " << y << " " << total_force[x][y][0] << endl;
            }
            
            if (which_field == "total_force_y") {
                filestr << x << " " << y << " " << total_force[x][y][1] << endl;
            }
            
            if (which_field == "body_force_x") {
                filestr << x << " " << y << " " << body_force[x][y][0] << endl;
            }
            
            if (which_field == "body_force_y") {
                filestr << x << " " << y << " " << body_force[x][y][1] << endl;
            }
            
            if (which_field == "f") {
                for (int k = 0; k < Nc; k++){
                    filestr << x << " " << y << " " << f[x][y][k] << endl;
                }
            }
            
            if (which_field == "feq") {
                for (int k = 0; k < Nc; k++){
                    filestr << x << " " << y << " " << feq[x][y][k] << endl;
                }
            }
            
            if (which_field == "g") {
                for (int k = 0; k < Nc; k++){
                    filestr << x << " " << y << " " << g[x][y][k] << endl;
                }
            }
            
            if (which_field == "geq") {
                for (int k = 0; k < Nc; k++){
                    filestr << x << " " << y << " " << geq[x][y][k] << endl;
                }
            }
            
            if (which_field == "h") {
                for (int k = 0; k < Nc; k++){
                    filestr << x << " " << y << " " << h[x][y][k] << endl;
                }
            }
            
            if (which_field == "heq") {
                for (int k = 0; k < Nc; k++){
                    filestr << x << " " << y << " " << heq[x][y][k] << endl;
                }
            }
            
            if (which_field == "s_o_u") {
                for (int k = 0; k < Nc; k++){
                    filestr << x << " " << y << " " << s_o_u[x][y][k] << endl;
                }
            }
            
            if (which_field == "source_term_f") {
                for (int k = 0; k < Nc; k++){
                    filestr << x << " " << y << " " << source_term_f[x][y][k] << endl;
                }
            }
            
            if (which_field == "source_term_g") {
                for (int k = 0; k < Nc; k++){
                    filestr << x << " " << y << " " << source_term_g[x][y][k] << endl;
                }
            }
            
            if (which_field == "source_term_h") {
                for (int k = 0; k < Nc; k++){
                    filestr << x << " " << y << " " << source_term_h[x][y][k] << endl;
                }
            }

        }
        filestr << endl;
    }

    filestr.close();
    if (filestr.is_open()) cout << "The file has not been closed!" << endl;
}


inline void output_evolution(string field, double value) {
    ofstream filestr;
    string fileName = "res/" + field + "_evolution.txt";

    filestr.open(fileName, ios::app);
    
    filestr << value << endl;

    filestr.close();
    if (filestr.is_open()) cout << "The file has not been closed!" << endl;
}


inline void total_mass_evolution(){
    double sum_mass = 0.0;
    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            sum_mass += rho[i][j];
        }
    }
    output_evolution("mass", sum_mass);
    
    std::cout << "Total mass: " << sum_mass << std::endl << std::endl;
}


inline void rho_intersection(int step_time, string which_field){
    ofstream filestr;

    string fileName = "res/" + which_field + "_" + to_string(step_time) + ".txt";

    filestr.open(fileName);

    for (int j = 0; j <= Ny - 1; j++) {
        filestr <<  rho[Nx / 2][j] << endl;
    }
    filestr.close();
}


inline void total_pressure_evolution(){
    double sum_pressure = 0.0;
    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            sum_pressure += pressure[i][j];
        }
    }
    output_evolution("pressure", sum_pressure);
    
    // std::cout << "Total pressure: " << sum_pressure << std::endl;
}


inline void dump_all_fields(int step_time) {
    output_field(step_time, "u");
    output_field(step_time, "v");
    output_field(step_time, "rho");
    output_field(step_time, "temperature");
    output_field(step_time, "phi");
    output_field(step_time, "pressure");
    output_field(step_time, "surface_force_x");
    output_field(step_time, "surface_force_y");
    output_field(step_time, "total_force_x");
    output_field(step_time, "total_force_y");
    output_field(step_time, "body_force_x");
    output_field(step_time, "body_force_y");
    output_field(step_time, "f");
    output_field(step_time, "feq");
    output_field(step_time, "h");
    output_field(step_time, "heq");
    output_field(step_time, "g");
    output_field(step_time, "geq");
    output_field(step_time, "s_o_u");
    output_field(step_time, "s_o_u");
    output_field(step_time, "source_term_f");
    output_field(step_time, "source_term_g");
    output_field(step_time, "source_term_h");
    
}


inline void read_field(int step_time, string which_field) {
    ifstream filestr;
    string fileName = "res/" + which_field + "_" + to_string(step_time) + ".txt";

    filestr.open(fileName);
    if (!filestr.is_open()) {
        cout << "Error! Could not open file: " << fileName << endl;
        return;
    }

    int x, y;
    double value;
    
    if (which_field == "f" || which_field == "feq") {
        for (int i = 0; i < Nx; i++) {
            for (int j = 0; j < Ny; j++) {
                for (int k = 0; k < Nc; k++) {
                    if (filestr >> x >> y >> value) {
                        if (which_field == "f") f[x][y][k] = value;
                        else if (which_field == "feq") feq[x][y][k] = value;
                        else if (which_field == "s_o_u") s_o_u[x][y][k] = value;
                    }
                }
            }
        }
    } 
    else {
        for (int i = 0; i < Nx; i++) {
            for (int j = 0; j < Ny; j++) {
                if (filestr >> x >> y >> value) {
                    if (which_field == "u") u[x][y][0] = value;
                    else if (which_field == "v") u[x][y][1] = value;
                    else if (which_field == "temperature") temperature[x][y] = value;
                    else if (which_field == "rho") rho[x][y] = value;
                    else if (which_field == "phi") phi[x][y] = value;
                    else if (which_field == "pressure") pressure[x][y] = value;
                    else if (which_field == "total_force_x") total_force[x][y][0] = value;
                    else if (which_field == "total_force_y") total_force[x][y][1] = value;
                }
            }
        }
    }

    filestr.close();
    cout << "Successfully loaded: " << fileName << endl;
}


inline void read_all_fields(int step_time) {
    read_field(step_time, "u");
    read_field(step_time, "temperature");
    read_field(step_time, "v");
    read_field(step_time, "rho");
    read_field(step_time, "f_external_x");
    read_field(step_time, "f_external_y");
    read_field(step_time, "f");
    read_field(step_time, "feq");
    read_field(step_time, "s_o_u");
}


inline void output_velocity(int step_time){
    output_field(step_time, "u");
    output_field(step_time, "v");
    output_field(step_time, "pressure");
}


inline void output_point_v_below(string field){
    ofstream filestr;
    string fileName = "res/" + field + "v_below.txt";

    filestr.open(fileName, ios::app);
    
    filestr << u[Nx/2][Ny/4][1] << endl;

    filestr.close();
    if (filestr.is_open()) cout << "The file has not been closed!" << endl;
}


inline void output_point_u_below(string field){
    ofstream filestr;
    string fileName = "res/" + field + "u_below.txt";

    filestr.open(fileName, ios::app);
    
    filestr << u[Nx/2][Ny/4][0] << endl;

    filestr.close();
    if (filestr.is_open()) cout << "The file has not been closed!" << endl;
}


inline void output_point_v_up(string field){
    ofstream filestr;
    string fileName = "res/" + field + "v.txt";

    filestr.open(fileName, ios::app);
    
    filestr << u[Nx/2][3 * (Ny / 4)][1] << endl;

    filestr.close();
    if (filestr.is_open()) cout << "The file has not been closed!" << endl;
}


inline void output_point_u_up(string field){
    ofstream filestr;
    string fileName = "res/" + field + "u.txt";

    filestr.open(fileName, ios::app);
    
    filestr << u[Nx/2][80][0] << endl;

    filestr.close();
    if (filestr.is_open()) cout << "The file has not been closed!" << endl;
}


inline void output_point_rho_down(string field){
    ofstream filestr;
    string fileName = "res/" + field + "rho_down.txt";

    filestr.open(fileName, ios::app);
    
    filestr << rho[Nx/2][Ny/4] << endl;

    filestr.close();
    if (filestr.is_open()) cout << "The file has not been closed!" << endl;
}


inline void output_point_rho_up(string field){
    ofstream filestr;
    string fileName = "res/" + field + "rho_up.txt";

    filestr.open(fileName, ios::app);
    
    filestr << rho[Nx/2][3*(Ny/4)] << endl;

    filestr.close();
    if (filestr.is_open()) cout << "The file has not been closed!" << endl;
}



inline double centerOfMass_Y() {
    double sum_phi  = 0.0;
    double sum_phiy = 0.0;
    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny; j++) {
            sum_phi  += phi[i][j];
            sum_phiy += phi[i][j] * j;
        }
    }
    return (sum_phi > 1e-12) ? (sum_phiy / sum_phi) : 0.0;
}


inline void get_center_mass(){
    double totalMass = 0.0;
    xCm = 0.0;
    yCm = 0.0;
    for (int i = 0; i < Nx; ++i){
        for (int j = 0; j < Ny; ++j)
        {
            double m = rho[i][j]; 
            totalMass += m;
            xCm += m * i;    
            yCm += m * j;    
        }
    }
    xCm /= totalMass;
    yCm /= totalMass;
}


inline void output_center_mass(){
    get_center_mass();
    ofstream filestr;
    string fileName = "res/cm.txt";

    filestr.open(fileName, ios::app);
    
    filestr << xCm <<"  "<< yCm << endl;

    filestr.close();
    if (filestr.is_open()) cout << "The file has not been closed!" << endl;
}


void measureVelocity(int step) {
    double y_cm = centerOfMass_Y();
    double U_LBM;
    if (y_cm_prev >= 0.0) {
        double dt_steps = step - step_prev;
        U_LBM    = (y_cm - y_cm_prev) / dt_steps;  // [lu/ts]

        // Перевод в физические единицы
        double U_phys = U_LBM;  // [м/с]

        std::cout << "step=" << step
                  << "  center_mass="  << y_cm
                  << "  U_LBM=" << U_LBM   << " lu/ts"
                  << std::endl;
    }

    y_cm_prev = y_cm;
    step_prev = step;
    output_evolution("bubble_velocit", U_LBM);
}


inline void save_results(int step_time){
    // output_center_mass();
    // total_mass_evolution();
    
    // output_point_rho_down("down_");
    // output_point_rho_up("up_");
    // total_pressure_evolution();
    
    // output_point_u_below("below_");
    // output_point_u_up("up_");
    // output_point_v_up("up_");
    // output_point_v_below("below_");
    // measureVelocity(step_time);
    // if(step_time % 1000   == 0){
        // output_field(step_time, "rho");
        // output_field(step_time, "streamline");
        // output_field(step_time, "u");
        // output_field(step_time, "v");
        // rho_intersection(step_time, "intersection");
    // }
    
    // if ( (step_time < 50000    && step_time % 1000   == 0) ||
    //      (step_time >= 50000  && step_time < 200000 && step_time % 10000  == 0) ||
    //      (step_time >= 200000 && step_time % 100000 == 0) )
    // {
    //     // output_velocity(step_time);
    //     // output_center_mass();
    //     // total_mass_evolution();
    //     output_field(step_time, "rho");
    //     // output_field(step_time, "phi");
    //     // output_field(step_time, "temperature");
    //     // output_field(step_time, "surface_force_x");
    //     // output_field(step_time, "surface_force_y");
    //     // output_field(step_time, "total_force_x");
    //     // output_field(step_time, "total_force_y");
    //     // output_field(step_time, "d_dt_u_phi_x");
    //     // output_field(step_time, "d_dt_u_phi_y");
    // }
    // 
    if (step_time % 1000 == 0) {
        output_center_mass();
    }
    if (step_time >= 200000 && step_time % 5000 == 0) {
        output_field(step_time, "rho");
    }

    
    // if (step_time % 1 == 0) {
    //     dump_all_fields(step_time);
    // }
}
