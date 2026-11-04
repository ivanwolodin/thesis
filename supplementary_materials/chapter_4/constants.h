#pragma once

#include <vector>
#include <cmath>
#include <stdlib.h>

using std::vector;


const int Nx = 1000;
const int Ny = 200;
const int Nc = 9;

const double dt = 1.0;
const double dx = 1.0;

vector<vector<vector<double> > > f(Nx, vector<vector<double> >(Ny, vector<double>(Nc)));
vector<vector<vector<double> > > feq(Nx, vector<vector<double> >(Ny, vector<double>(Nc)));
vector<vector<vector<double> > > s_o_u(Nx, vector<vector<double> >(Ny, vector<double>(Nc)));

vector<vector<vector<double> > > u(Nx, vector<vector<double> >(Ny, vector<double>(2)));

vector<vector<vector<double> > > g(Nx, vector<vector<double> >(Ny, vector<double>(Nc)));
vector<vector<vector<double> > > geq(Nx, vector<vector<double> >(Ny, vector<double>(Nc)));

vector<vector<double> > streamline(Nx, vector<double>(Ny));

vector<vector<double> > phi(Nx, vector<double>(Ny));

vector<vector<double> > rho(Nx, vector<double>(Ny));
vector<vector<double> > pressure(Nx, vector<double>(Ny));

vector<vector<double> > tau(Nx, vector<double>(Ny));

vector<vector<vector<double> > > h(Nx, vector<vector<double> >(Ny, vector<double>(Nc)));
vector<vector<vector<double> > > h_pre_streaming(Nx, vector<vector<double> >(Ny, vector<double>(Nc)));
vector<vector<vector<double> > > heq(Nx, vector<vector<double> >(Ny, vector<double>(Nc)));

vector<vector<double> > temperature(Nx, vector<double>(Ny));
vector<vector<vector<double> > > grad_temperature(Nx, vector<vector<double> >(Ny, vector<double>(2)));

vector<vector<double> > sigma(Nx, vector<double>(Ny));
vector<vector<vector<double> > > grad_sigma(Nx, vector<vector<double> >(Ny, vector<double>(2)));

vector<vector<double> > mu_phi(Nx, vector<double>(Ny));
vector<vector<double> > laplacian_phi(Nx, vector<double>(Ny));

vector<vector<vector<double> > > normal(Nx, vector<vector<double> >(Ny, vector<double>(2)));
vector<vector<vector<double> > > body_force(Nx, vector<vector<double> >(Ny, vector<double>(2)));
vector<vector<vector<double> > > total_force(Nx, vector<vector<double> >(Ny, vector<double>(2)));
vector<vector<vector<double> > > grad_phi(Nx, vector<vector<double> >(Ny, vector<double>(2)));

vector<vector<vector<double> > > vibrational_force(Nx, vector<vector<double> >(Ny, vector<double>(2)));

vector<vector<vector<double> > > source_term_f(Nx, vector<vector<double> >(Ny, vector<double>(Nc)));
vector<vector<vector<double> > > source_term_g(Nx, vector<vector<double> >(Ny, vector<double>(Nc)));
vector<vector<vector<double> > > source_term_h(Nx, vector<vector<double> >(Ny, vector<double>(Nc)));

vector<vector<vector<double> > > surface_force(Nx, vector<vector<double> >(Ny, vector<double>(2)));

vector<vector<vector<double> > > d_dt_u_phi(Nx, vector<vector<double> >(Ny, vector<double>(2)));
vector<vector<vector<double> > > u_phi(Nx, vector<vector<double> >(Ny, vector<double>(2)));
vector<vector<vector<double> > > u_phi_previous(Nx, vector<vector<double> >(Ny, vector<double>(2)));

const double gravity = 0*1e-6;

const double gravity_x = 0.0;
const double gravity_y = - gravity;


const double cx[9] = {0, 1, 0, -1, 0, 1, -1, -1, 1};
const double cy[9] = {0, 0, 1, 0, -1, 1, 1, -1, -1};

const double w[9] = {
        16 / 36.0,
        4 / 36.0,
        4 / 36.0,
        4 / 36.0,
        4 / 36.0,
        1 / 36.0,
        1 / 36.0,
        1 / 36.0,
        1 / 36.0
};


const int steps_number = 1000000;
const double sound_speed_squared = (1.0 / 3.0) * ((dx * dx) / dt);

// const double rho_l = 1.5;
// const double rho_g = 1;

const double rho_l = 100;
const double rho_g = 1.0;


const double tau_f_liquid = 1;// 5.479999999999999;
const double viscosity_liquid = (tau_f_liquid - 0.5) * sound_speed_squared;

const double tau_f_gas = 1;
const double viscosity_gas = (tau_f_gas - 0.5) * sound_speed_squared;


const double tau_g = 1.0;
const double mobility = (tau_g - 0.5) * sound_speed_squared;

const double tau_h = 100000000.0;
const double heat_capacity = (tau_h - 0.5) * sound_speed_squared;

const double surface_tension_coef = 0.05;
const double d_sigma_d_temperature = -2.5 * 0.0001;
const double reference_temperature = 0.0;
const double sigma_at_reference_temperature = surface_tension_coef;

const int interface_thickness = 5;

const double k = (3.0 / 2.0) * (surface_tension_coef * interface_thickness);
const double beta = (12.0 * surface_tension_coef) / interface_thickness;

const double c_p = 1.0;

vector<vector<vector<double> > > u_previous(Nx, vector<vector<double> >(Ny, vector<double>(2)));
const double numerical_accuracy = 1e-6;

const double omega = 0.0001;//3.0e-03;
double Ampl = 1*100;//500;

const double Bond_number = ((rho_l - rho_g) * gravity * Nx * Nx) / surface_tension_coef;
const double Weber_number = ((rho_l - rho_g) * (Ampl * omega) * (Ampl * omega) * Nx) / surface_tension_coef;

const double kapitza_velocity = Ampl * omega;
const double critical_velocity = sqrt((gravity * Nx) / M_PI);

const double ration_gravity_to_amplitude_omegaSquared = omega * omega * Ampl / gravity;


const double radius_bubble = 109;

double y_cm_prev;
double step_prev;



double xCm = 0.0;
double yCm = 0.0;