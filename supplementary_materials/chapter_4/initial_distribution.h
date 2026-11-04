#pragma once

#include <iostream>

#include "boundary_conditions.h"
#include "constants.h"
#include "evolution.h"
#include "io.h"

using std::cout;
using std::endl;


inline void rayleigh_taylor_2(){
    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny; j++) {
            rho[i][j] = rho_g;
            phi[i][j] = 0.0;
        }
    }

    for (int i = 10; i < Nx - 10; i++) {
        for (int j = Ny / 2; j < Ny - 10; j++) {
            rho[i][j] = rho_l;
            phi[i][j] = 1.0;
        }
    }
    
}

inline void rayleigh_taylor(){
    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny / 2; j++) {
            rho[i][j] = rho_g;
            phi[i][j] = 0.0;
        }
    }

    for (int i = 0; i < Nx; i++) {
        for (int j = Ny / 2; j < Ny; j++) {
            rho[i][j] = rho_l;
            phi[i][j] = 1.0;
        }
    }

    // for (int i = 0; i < Nx; i++) {

    //     rho[i][Ny - 1] = rho_g;
    //     phi[i][Ny - 1] = 0.0;

    //     rho[i][Ny - 2] = rho_g;
    //     phi[i][Ny - 2] = 0.0;

    //     rho[i][Ny - 3] = rho_g;
    //     phi[i][Ny - 3] = 0.0;

    //     rho[i][Ny - 4] = rho_g;
    //     phi[i][Ny - 4] = 0.0;
    // }

    // for (int j = 0; j < Ny; j++) {

    //     rho[Nx - 1][j] = rho_g;
    //     phi[Nx - 1][j] = 0.0;

    //     rho[Nx - 2][j] = rho_g;
    //     phi[Nx - 2][j] = 0.0;

    //     rho[Nx - 3][j] = rho_g;
    //     phi[Nx - 3][j] = 0.0;

    //     rho[Nx - 4][j] = rho_g;
    //     phi[Nx - 4][j] = 0.0;


    //     rho[0][j] = rho_g;
    //     phi[0][j] = 0.0;

    //     rho[1][j] = rho_g;
    //     phi[1][j] = 0.0;

    //     rho[2][j] = rho_g;
    //     phi[2][j] = 0.0;

    //     rho[3][j] = rho_g;
    //     phi[3][j] = 0.0;
    // }
}


inline void equilibrium(){
    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny / 2; j++) {
            rho[i][j] = rho_l;
            phi[i][j] = 1.0;
        }
    }

    for (int i = 0; i < Nx; i++) {
        for (int j = Ny / 2; j < Ny; j++) {
            rho[i][j] = rho_g;
            phi[i][j] = 0.0;
        }
    }
    
    
}


inline void nature(){
    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny; j++) {
            rho[i][j] = rho_g;
            phi[i][j] = 0.0;
        }
    }
    
    for (int i = 0; i < Nx; i++) {
        for (int j = 250; j < 450; j++) {
            rho[i][j] = rho_l;
            phi[i][j] = 1.0;
        }
    }
    
    for (int i = 0; i < Nx; i++) {
        for (int j = 1250; j < 1450; j++) {
            rho[i][j] = rho_l;
            phi[i][j] = 1.0;
        }
    }
}


inline void disturbed(){
    const double A = 15.0;                  // очень малая амплитуда (в узлах)
        const double k = 2.0 * M_PI / Nx;       // один период на всю длину

        for (int i = 0; i < Nx; i++) {
            int j_int = static_cast<int>(Ny / 2 + A * sin(k * i));

            for (int j = 0; j < Ny; j++) {
                if (j < j_int) {
                    rho[i][j] = rho_l;
                    phi[i][j] = 1.0;
                } else {
                    rho[i][j] = rho_g;
                    phi[i][j] = 0.0;
                }
            }
        }
}


inline void super_equilibrium(){
    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny; j++) {
            rho[i][j] = rho_g;
            phi[i][j] = 1.0;
        }
    }

    // for (int i = 0; i < Nx; i++) {
    //     for (int j = Ny / 2; j < Ny; j++) {
    //         rho[i][j] = rho_g;
    //         phi[i][j] = 0.0;
    //     }
    // }
}


// inline void bubble(){
//     const double cxx = 0.5 * (Nx - 1);
//         const double cyy = 0.5 * (Ny - 1);
//         const double R  = 0.25 * std::min(Nx, Ny); // радиус пузыря

//         for (int i = 0; i < Nx; i++) {
//             for (int j = 0; j < Ny; j++) {

//                 double ddx = i - cxx;
//                 double ddy = j - cyy;
//                 double r2 = ddx * ddx + ddy * ddy;

//                 if (r2 <= R * R) {
//                     // тяжёлая фаза (пузырь)
//                     rho[i][j] = rho_l;
//                     phi[i][j] = 1.0;
//                 } else {
//                     // лёгкая фаза (окружающая среда)
//                     rho[i][j] = rho_g;
//                     phi[i][j] = 0.0;
//                 }
//             }
//         }
// }


inline void fluid_rise(){
    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny; j++) {
            rho[i][j] = rho_g;
            phi[i][j] = 0.0;
        }
    }
    
    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny / 4; j++) {
            rho[i][j] = rho_l;
            phi[i][j] = 1.0;
        }
    }
}

inline void bubble(){
    double cx1 = Nx / 2.0;
    double cy1 = Ny / 2.0;
    double radius = radius_bubble;
    double W = 4.0; // ширина переходного слоя в ячейках

    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny; j++) {
            double dx = i - cx1;
            double dy = j - cy1;
            double dist = sqrt(dx*dx + dy*dy);

            phi[i][j] = 0.5 * (1.0 - tanh((dist - radius) / W));
            rho[i][j] = rho_g + (rho_l - rho_g) * phi[i][j];
        }
    }
}


inline void cylinder_drop(){
    // for (int i = 0; i < Nx / 3; i++) {
    //     for (int j = 0; j < Ny; j++) {
    //         // rho[i][j] = rho_g;
    //         // phi[i][j] = 0.0;
            
    //         rho[i][j] = rho_l;
    //         phi[i][j] = 1.0;
    //     }
    // }
    
    // for (int i = Nx / 3; i < 2 * (Nx / 3); i++) {
    //     for (int j = 0; j < Ny ; j++) {
    //         // rho[i][j] = rho_l;
    //         // phi[i][j] = 1.0;
    //         rho[i][j] = rho_g;
    //         phi[i][j] = 0.0;
    //     }
    // }

    // for (int i = 2 * (Nx / 3); i < Nx; i++) {
    //     for (int j = 0; j < Ny; j++) {
    //         // rho[i][j] = rho_g;
    //         // phi[i][j] = 0.0;
    //         rho[i][j] = rho_l;
    //         phi[i][j] = 1.0;
    //     }
    // }
    // 
    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny ; j++) {
            // rho[i][j] = rho_l;
            // phi[i][j] = 1.0;
            rho[i][j] = rho_g;
            phi[i][j] = 0.0;
        }
    }
    for (int i = 400; i <=650; i++) {
        for (int j = 0; j < Ny ; j++) {
            rho[i][j] = rho_l;
            phi[i][j] = 1.0;
            // rho[i][j] = rho_g;
            // phi[i][j] = 0.0;
        }
    }
}



inline void setup_simulation(int step_time) {
    if (step_time != 0) {
        cout << "--- Attempting to load fields from step " << step_time << " ---" << endl;
        read_all_fields(step_time);
        cout << "--- Load process finished ---" << endl;
    }
    else {
        cylinder_drop();
        // rayleigh_taylor();
        // equilibrium();
        // super_equilibrium();
        // bubble();
        // disturbed();
        // 
        // nature();
        // fluid_rise();
        for (int i = 0; i < Nx; i++) {
            for (int j = 0; j < Ny; j++) {
                tau[i][j] = (tau_f_liquid - tau_f_gas) * phi[i][j] + tau_f_gas;
            }
        }
        for (int i = 0; i < Nx; i++) {
            for (int j = 0; j < Ny; j++) {
                u[i][j][0] = 0.0;
                u[i][j][1] = 0.0;

                temperature[i][j] = 0.0;
                
                body_force[i][j][0] = 0.0;
                body_force[i][j][1] = gravity_y * rho[i][j];
                
                total_force[i][j][0] = 0.0;
                total_force[i][j][1] = gravity_y * rho[i][j];
                normal[i][j][0] = 0.0;
                normal[i][j][1] = 0.0;

                sigma[i][j] = surface_tension_coef;
                grad_sigma[i][j][0] = 0.0;
                grad_sigma[i][j][1] = 0.0;
                mu_phi[i][j] = 0.0;
                // pressure[i][j] = rho[i][j] * rho[i][j] * sound_speed_squared;
                for (int k = 0; k < Nc; k++) {
                    source_term_f[i][j][k] = 0.0;
                    source_term_g[i][j][k] = 0.0;
                    s_o_u[i][j][k] = 0.0;

                }
            }
        }
        int step = 0;
        compute_grads_phi();
        // compute_mu_phi();
        compute_surface_force_isothemal();
        compute_total_force();
        compute_normal_vector();

        compute_source_term_g();
        compute_geq();
        collision_g();
        streaming(g);
        boundary_conditions_order_parameter(g);

        compute_source_term_f(step);
        compute_velocity();
        compute_s_o_u();

        compute_pressure();

        compute_feq();
        collision_f();
        streaming(f);
        boundary_conditions_velocity(f);

    }
}

inline void setup_initial() {

    const double W  = interface_thickness;
    const double y0 = 0.5 * Ny;
    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny; j++) {
            double y = j + 0.5;
            phi[i][j] = 0.5 * (1.0 - tanh((y - y0) / W));
        }
    }
    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny; j++) {
            rho[i][j] = rho_g + phi[i][j] * (rho_l - rho_g);
        }
    }

    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny; j++) {
            u[i][j][0] = 0.0;
            u[i][j][1] = 0.0;
        }
    }

    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny; j++) {
            for (int k = 0; k < Nc; k++) {
                g[i][j][k] = w[k] * phi[i][j];
            }
        }
    }

    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny; j++) {
            double p = sound_speed_squared * rho[i][j];
            f[i][j][0] =
                rho[i][j] - (1.0 - w[0]) * p / sound_speed_squared;

            for (int k = 1; k < Nc; k++) {
                f[i][j][k] = w[k] * p / sound_speed_squared;
            }
        }
    }
}
