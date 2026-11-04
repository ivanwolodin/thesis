#pragma once

#include "constants.h"
#include "boundary_conditions.h"
#include "health_check.h"
#include "io.h"
#include "streaming.h"
#include "convergence.h"


const double first_term_expansion = 1.0 / sound_speed_squared;
const double second_term_expansion = 1.0 / (2 * sound_speed_squared * sound_speed_squared);
const double third_term_expansion = 1.0 / (2 * sound_speed_squared);

// const double time_step_divided_by_tau_f = dt / tau_f;
// const double time_term_f = 1 - time_step_divided_by_tau_f;

const double time_step_divided_by_tau_g = dt / tau_g;
const double time_term_g = 1 - time_step_divided_by_tau_g;

const double time_step_divided_by_tau_h = dt / tau_h;
const double time_term_h = 1 - time_step_divided_by_tau_h;


inline void compute_tau() {
    for (int i = 0; i < Nx; i++) {
        for (int j = 0; j < Ny; j++) {
            tau[i][j] = (tau_f_liquid - tau_f_gas) * phi[i][j] + tau_f_gas;
        }
    }
}


inline void compute_s_o_u() {
    double velocity_squared = 0.0;
    double local_velocity = 0.0;

    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            velocity_squared = u[i][j][0] * u[i][j][0] + u[i][j][1] * u[i][j][1];
            for (int k = 0; k < Nc; k++) {
                local_velocity = u[i][j][0] * cx[k] + u[i][j][1] * cy[k];
                s_o_u[i][j][k] = w[k] * (first_term_expansion * local_velocity +
                                        second_term_expansion * local_velocity * local_velocity -
                                        third_term_expansion * velocity_squared);
            }
        }
    }
}


inline void compute_feq() {
    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            feq[i][j][0] = (pressure[i][j] / sound_speed_squared) * (w[0] - 1.0) + rho[i][j] * s_o_u[i][j][0];
            for (int k = 1; k < Nc; k++) {
                feq[i][j][k] = (pressure[i][j] / sound_speed_squared) * w[k] + rho[i][j] * s_o_u[i][j][k];
            }
        }
    }
}


inline void collision_f() {
    double time_step_divided_by_tau_f = 0.0;
    double time_term_f = 0.0;
    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            
            double time_step_divided_by_tau_f = dt / tau[i][j];
            time_term_f = 1 - time_step_divided_by_tau_f;
            for (int k = 0; k < Nc; k++) {
                f[i][j][k] = f[i][j][k] * time_term_f + feq[i][j][k] * time_step_divided_by_tau_f + dt * source_term_f[i][j][k];
            }
        }
    }
}


inline void collision_h() {
    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            for (int k = 0; k < Nc; k++) {
                // h[i][j][k] = ((rho[i][j] * c_p - 1.0) * h_pre_streaming[i][j][k] +
                //     h[i][j][k] * time_term_h + heq[i][j][k] * time_step_divided_by_tau_h +
                //     dt * source_term_h[i][j][k]) / (rho[i][j] * c_p);
                h[i][j][k] = h[i][j][k] * time_term_h + heq[i][j][k] * time_step_divided_by_tau_h +
                    dt * source_term_h[i][j][k];
            }
        }
    }
}



inline void collision_g() {
    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            for (int k = 0; k < Nc; k++) {
                g[i][j][k] = g[i][j][k] * time_term_g + geq[i][j][k] * time_step_divided_by_tau_g + dt * source_term_g[i][j][k];
            }
        }
    }
}


inline void compute_geq() {
    double local_velocity = 0.0;
    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            local_velocity = 0.0;
            for (int k = 0; k < Nc; k++) {
                local_velocity = u[i][j][0] * cx[k] + u[i][j][1] * cy[k];
                geq[i][j][k] = w[k] * phi[i][j] * (1.0 + first_term_expansion * local_velocity);
            }
        }
    }
}


inline void compute_source_term_h() {
    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            for (int k = 0; k < Nc; k++) {
                source_term_h[i][j][k] = - w[k] * (rho[i][j] * c_p * (u[i][j][0] * grad_temperature[i][j][0] + u[i][j][1] * grad_temperature[i][j][1]));
            }
        }
    }
}


inline void compute_temperature(){
    double temp_var_t = 0.0;
    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            temp_var_t = 0.0;
            for (int k = 0; k < Nc; k++) {
                temp_var_t += (h[i][j][k]);
            }
            temperature[i][j] = temp_var_t;
        }
    }
}


inline void compute_heq() {
    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            for (int k = 0; k < Nc; k++) {
                heq[i][j][k] = w[k] * temperature[i][j];
            }
        }
    }
}


inline void compute_source_term_f(int& time_step) 
{
    double osc_term = Ampl * omega * omega * std::cos(omega * time_step);

    double const_temp = 0.0;
    double G_y = 0.0;
    double G_x = 0.0;
    double rho_diff = rho_l - rho_g;
    // const_temp = (1.0 - 0.5 / tau_f) / sound_speed_squared;
    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            G_y = rho[i][j] * (gravity_y + 0*osc_term);
            G_x = rho[i][j] * (osc_term);
            const_temp = (1.0 - 0.5 / tau[i][j]) / sound_speed_squared;
            for (int k = 0; k < Nc; k++) {
                source_term_f[i][j][k] = const_temp * w[k] * (
                    mu_phi[i][j] * (cx[k] * grad_phi[i][j][0] * G_x + cy[k] * grad_phi[i][j][1] + cy[k] * G_y) +
                    rho_diff * (
                        (u[i][j][0] * cx[k] + u[i][j][1] * cy[k]) * (cx[k] * grad_phi[i][j][0] + cy[k] * grad_phi[i][j][1])
                    )
                );
            }
        }
    }
}



// inline void compute_source_term_f() {
//     for (int i = 0; i < Nx; i++) {
//         for (int j = 0; j < Ny; j++) {

//             for (int k = 0; k < Nc; k++) {

//                 double cu = cx[k] * u[i][j][0] + cy[k] * u[i][j][1];
//                 double Fu = cx[k] * total_force[i][j][0]
//                           + cy[k] * total_force[i][j][1];

//                 source_term_f[i][j][k] =
//                     (1.0 - 0.5 / tau_f) * w[k] *
//                     (
//                         (cx[k] * total_force[i][j][0]
//                        + cy[k] * total_force[i][j][1]) / sound_speed_squared
//                         +
//                         cu * Fu / (sound_speed_squared * sound_speed_squared)
//                     );
//             }
//         }
//     }
// }



inline void compute_rho() {
    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            rho[i][j] = phi[i][j] * (rho_l - rho_g) + rho_g;
        }
    }
}


inline void compute_phi(){
    double temp_var_phi = 0.0;
    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            temp_var_phi = 0.0;
            for (int k = 0; k < Nc; k++) {
                temp_var_phi += (g[i][j][k]);
            }
            phi[i][j] = temp_var_phi;
        }
    }
}


inline void save_u_phi(){
    for (int x = 0; x < Nx; ++x) {
        for (int y = 0; y < Ny; ++y) {
            u_phi_previous[x][y][0] = u[x][y][0] * phi[x][y];
            u_phi_previous[x][y][1] = u[x][y][1] * phi[x][y];
        }
    }
}


inline void compute_d_dt_u_phi(){
    for (int x = 0; x < Nx; ++x) {
        for (int y = 0; y < Ny; ++y) {
            u_phi[x][y][0] = u[x][y][0] * phi[x][y];
            u_phi[x][y][1] = u[x][y][1] * phi[x][y];
        }
    }
    for (int x = 0; x < Nx; ++x) {
        for (int y = 0; y < Ny; ++y) {

            d_dt_u_phi[x][y][0] =
                (u_phi[x][y][0] - u_phi_previous[x][y][0]) / dt;

            d_dt_u_phi[x][y][1] =
                (u_phi[x][y][1] - u_phi_previous[x][y][1]) / dt;
        }
    }
}


inline void compute_normal_vector(){
    double module_grad = 0.0;
    for (int x = 1; x < Nx - 1; ++x) {
        for (int y = 1; y < Ny - 1; ++y) {
            module_grad = sqrt(grad_phi[x][y][0] * grad_phi[x][y][0] + grad_phi[x][y][1] * grad_phi[x][y][1]);
            if (module_grad != 0){
                normal[x][y][0] = grad_phi[x][y][0] / module_grad;
                normal[x][y][1] = grad_phi[x][y][1] / module_grad;
            }
            else {
                normal[x][y][0] = 0.0;
                normal[x][y][1] = 0.0;
            }
        }
    }
}


inline void compute_source_term_g() {
    double const_temp = 0.0;
    double temp_lambda = 0.0;
    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            const_temp = (1.0 - 0.5 / tau_g) / sound_speed_squared;
            temp_lambda = (4.0 * phi[i][j] * (1.0 - phi[i][j])) / interface_thickness;
            for (int k = 0; k < Nc; k++) {
                source_term_g[i][j][k] = const_temp * w[k] * (
                     cx[k] * d_dt_u_phi[i][j][0] +
                     cy[k] * d_dt_u_phi[i][j][1] +
                     cx[k] * sound_speed_squared * temp_lambda * normal[i][j][0] +
                     cy[k] * sound_speed_squared * temp_lambda * normal[i][j][1]
                );
            }
        }
    }
}


inline void compute_mu_phi() {
    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            mu_phi[i][j] = 4.0 * beta * phi[i][j] * (phi[i][j] - 1.0) * (phi[i][j] - 0.5) - k * laplacian_phi[i][j];
        }
    }
}


inline void compute_surface_force_isothemal() {
    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            surface_force[i][j][0] = mu_phi[i][j] * grad_phi[i][j][0];
            surface_force[i][j][1] = mu_phi[i][j] * grad_phi[i][j][1];
        }
    }
}


inline void compute_surface_force() {
    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            // surface_force[i][j][0] = mu_phi[i][j] * grad_phi[i][j][0];
            // surface_force[i][j][1] = mu_phi[i][j] * grad_phi[i][j][1];

            surface_force[i][j][0] = ((3.0 * sqrt(2) * interface_thickness) / 4.0) * (
                (grad_phi[i][j][0] * grad_phi[i][j][0] + grad_phi[i][j][1] * grad_phi[i][j][1]) * grad_sigma[i][j][0] -
                grad_phi[i][j][0] * (grad_phi[i][j][0] * grad_sigma[i][j][0] + grad_phi[i][j][1] * grad_sigma[i][j][1]) +
                (sigma[i][j] / (interface_thickness * interface_thickness)) * mu_phi[i][j] * grad_phi[i][j][0]
            );

            surface_force[i][j][1] = ((3.0 * sqrt(2) * interface_thickness) / 4.0) * (
                (grad_phi[i][j][0] * grad_phi[i][j][0] + grad_phi[i][j][1] * grad_phi[i][j][1]) * grad_sigma[i][j][1] -
                (grad_phi[i][j][0] * grad_sigma[i][j][0] + grad_phi[i][j][1] * grad_sigma[i][j][1]) * grad_phi[i][j][1] +
                (sigma[i][j] / (interface_thickness * interface_thickness)) * mu_phi[i][j] * grad_phi[i][j][1]
            );
        }
    }
}


inline void compute_grads_phi(){
    double phi_ip = 0;
    for (int x = 1; x < Nx - 1; ++x) {
        for (int y = 1; y < Ny - 1; ++y) {

            grad_phi[x][y][0] = 0.0;
            grad_phi[x][y][1] = 0.0;
            laplacian_phi[x][y] = 0.0;

            for (int i = 1; i < Nc; ++i) {
                int xp = x + cx[i];
                int yp = y + cy[i];

                phi_ip = phi[xp][yp];

                grad_phi[x][y][0] += w[i] * cx[i] * phi_ip;
                grad_phi[x][y][1] += w[i] * cy[i] * phi_ip;

                laplacian_phi[x][y] +=
                    2.0 * w[i] * (phi_ip - phi[x][y]);
            }

            // Нормировка
            grad_phi[x][y][0] /= (sound_speed_squared * dt);
            grad_phi[x][y][1] /= (sound_speed_squared * dt);

            laplacian_phi[x][y] /= (sound_speed_squared * dt * dt);
        }
    }

    // ================================================================
    // Classic way
    // ================================================================
    // const double dy = 1.0;
    // for (int i = 1; i < Nx - 1; i++) {
    //     for (int j = 1; j < Ny - 1; j++) {
    //         grad_phi[i][j][0] = (
    //                                     2 * (phi[i + 1][j + 1] - phi[i - 1][j + 1]) +
    //                                     8 * (phi[i + 1][j] - phi[i - 1][j]) +
    //                                     2 * (phi[i + 1][j - 1] - phi[i - 1][j - 1])
    //                             ) / (12 * dx);

    //         grad_phi[i][j][1] = (
    //                                     2 * (phi[i + 1][j + 1] - phi[i + 1][j - 1]) +
    //                                     8 * (phi[i][j + 1] - phi[i][j - 1]) +
    //                                     2 * (phi[i - 1][j + 1] - phi[i - 1][j - 1])
    //                             ) / (12 * dy);
    //     }
    // }

    // for (int i = 1; i < Nx - 1; i++) {
    //     for (int j = 1; j < Ny - 1; j++) {
    //         laplacian_phi[i][j] = (
    //                     4 * (phi[i + 1][j] + phi[i - 1][j] + phi[i][j + 1] + phi[i][j - 1]) +
    //                             phi[i + 1][j + 1] + phi[i + 1][j - 1] + phi[i - 1][j + 1] + phi[i - 1][j - 1] -
    //                             20 * phi[i][j]
    //                 ) / (6 * dx * dx);
    //     }
    // }

    // // Обработка левой (i=0) и правой (i=Nx-1) границ для grad_phi[i][j][0] (по X)
    // for (int j = 0; j < Ny; j++) {
    //     // Левый край (forward difference)
    //     grad_phi[0][j][0] = (-3 * phi[0][j] + 4 * phi[1][j] - phi[2][j]) / (2 * dx);
    //     // Правый край (backward difference)
    //     grad_phi[Nx - 1][j][0] = (3 * phi[Nx - 1][j] - 4 * phi[Nx - 2][j] + phi[Nx - 3][j]) / (2 * dx);
    // }

    // // Обработка нижней (j=0) и верхней (j=Ny-1) границ для grad_phi[i][j][1] (по Y)
    // for (int i = 0; i < Nx; i++) {
    //     // Нижний край
    //     grad_phi[i][0][1] = (-3 * phi[i][0] + 4 * phi[i][1] - phi[i][2]) / (2 * dy);
    //     // Верхний край
    //     grad_phi[i][Ny - 1][1] = (3 * phi[i][Ny - 1] - 4 * phi[i][Ny - 2] + phi[i][Ny - 3]) / (2 * dy);
    // }

    // for (int i = 0; i < Nx; i++) {
    //     for (int j = 0; j < Ny; j++) {
    //         // Пропускаем внутренние точки, так как они уже посчитаны
    //         if (i > 0 && i < Nx - 1 && j > 0 && j < Ny - 1) continue;

    //         double d2phi_dx2, d2phi_dy2;

    //         // Вторая производная по X
    //         if (i == 0) // Левая граница: используем forward 2nd order
    //             d2phi_dx2 = (2 * phi[0][j] - 5 * phi[1][j] + 4 * phi[2][j] - phi[3][j]) / (dx * dx);
    //         else if (i == Nx - 1) // Правая граница
    //             d2phi_dx2 = (2 * phi[i][j] - 5 * phi[i-1][j] + 4 * phi[i-2][j] - phi[i-3][j]) / (dx * dx);
    //         else // Внутренняя по X, но граничная по Y
    //             d2phi_dx2 = (phi[i+1][j] - 2 * phi[i][j] + phi[i-1][j]) / (dx * dx);

    //         // Вторая производная по Y
    //         if (j == 0) // Нижняя граница
    //             d2phi_dy2 = (2 * phi[i][0] - 5 * phi[i][1] + 4 * phi[i][2] - phi[i][3]) / (dy * dy);
    //         else if (j == Ny - 1) // Верхняя граница
    //             d2phi_dy2 = (2 * phi[i][j] - 5 * phi[i][j-1] + 4 * phi[i][j-2] - phi[i][j-3]) / (dy * dy);
    //         else // Внутренняя по Y, но граничная по X
    //             d2phi_dy2 = (phi[i][j+1] - 2 * phi[i][j] + phi[i][j-1]) / (dy * dy);

    //         laplacian_phi[i][j] = d2phi_dx2 + d2phi_dy2;
    //     }
    // }
}


inline void compute_grad(
    const std::vector<std::vector<double>>& func,
    std::vector<std::vector<std::vector<double>>>& func_res
){
    const double dyy = 1.0;
    const double dxx = 1.0;
    for (int i = 1; i < Nx - 1; i++) {
        for (int j = 1; j < Ny - 1; j++) {
            func_res[i][j][0] = (
                                        2 * (func[i + 1][j + 1] - func[i - 1][j + 1]) +
                                        8 * (func[i + 1][j] - func[i - 1][j]) +
                                        2 * (func[i + 1][j - 1] - func[i - 1][j - 1])
                                ) / (12 * dxx);

            func_res[i][j][1] = (
                                        2 * (func[i + 1][j + 1] - func[i + 1][j - 1]) +
                                        8 * (func[i][j + 1] - func[i][j - 1]) +
                                        2 * (func[i - 1][j + 1] - func[i - 1][j - 1])
                                ) / (12 * dyy);
        }
    }
}


inline void compute_grad_temperature(){
    double time_temp = 1.0 / (tau_h * sound_speed_squared * dt);
    double temporary_var_for_t_x = 0.0;
    double temporary_var_for_t_y = 0.0;
    double h_dif = 0.0;
    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            temporary_var_for_t_x = 0.0;
            temporary_var_for_t_y = 0.0;
            for (int k = 0; k < Nc; k++) {
                h_dif = h[i][j][k] - heq[i][j][k];

                temporary_var_for_t_x += (cx[k] * h_dif);
                temporary_var_for_t_y += (cy[k] * h_dif);
            }
            grad_temperature[i][j][0] =(temporary_var_for_t_x / time_temp);
            grad_temperature[i][j][1] =(temporary_var_for_t_y / time_temp);
        }
    }
}


inline void compute_surface_tension(){
    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            sigma[i][j] = sigma_at_reference_temperature + 0*d_sigma_d_temperature * (temperature[i][j] - reference_temperature);
        }
    }
}


inline void compute_body_force(int& time_step){
    double osc_term = Ampl * omega * omega * std::cos(omega * time_step);

    const double beta_t = 1.0;
    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            // it is unclear how to define G.
            // In the Phase-field-based lattice Boltzmann model for simulating thermocapillary flows, PRE 2023
            // It is only stated that "G is the additional body force, "

            // body_force[i][j][0] = gravity_x * vibrational_force[i][j][0];
            body_force[i][j][0] = rho[i][j] * osc_term;
            body_force[i][j][1] = rho[i][j] * (
                gravity_y +
                osc_term*0 
                // gravity_y * beta_t * (temperature[i][j] - reference_temperature)
            );
        }
    }
}


inline void compute_total_force() {
    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            total_force[i][j][0] = surface_force[i][j][0] + body_force[i][j][0];
            total_force[i][j][1] = surface_force[i][j][1] + body_force[i][j][1];
        }
    }
}


inline void compute_velocity(){
    double temporary_var_for_u = 0.0;
    double temporary_var_for_v = 0.0;

    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            temporary_var_for_u = 0.0;
            temporary_var_for_v = 0.0;

            for (int k = 0; k < Nc; k++) {
                temporary_var_for_u += (f[i][j][k] * cx[k]);
                temporary_var_for_v += (f[i][j][k] * cy[k]);
            }
            u[i][j][0] = (temporary_var_for_u + 1.0 * dt * total_force[i][j][0]) / rho[i][j];
            u[i][j][1] = (temporary_var_for_v + 1.0 * dt * total_force[i][j][1]) / rho[i][j];

        }
    }
}


inline void compute_pressure(){
    double temporary_var_for_p = 0.0;
    for (int i = 0; i <= Nx - 1; i++) {
        for (int j = 0; j <= Ny - 1; j++) {
            temporary_var_for_p = 0.0;
            for (int k = 1; k < Nc; k++) {
                temporary_var_for_p += (f[i][j][k]);
            }
            pressure[i][j] = (sound_speed_squared / (1.0 - w[0])) * (temporary_var_for_p + 0.5 * dt * (rho_l - rho_g)
                * (u[i][j][0] * grad_phi[i][j][0] + u[i][j][1] * grad_phi[i][j][1]) + rho[i][j] * s_o_u[i][j][0]);
        }
    }
}

inline void boundary_conditions_velocity(std::vector<std::vector<std::vector<double>>>& func) {
    no_slip_bottom(func);
    no_slip_upper(func);
    // free_slip_left(func);
    // free_slip_right(func);
    periodic_left(func);
    periodic_right(func);
    // no_slip_left(func);
    // no_slip_right(func);
    // handle_corners(func); // Вызываем отдельно в конце
}


inline void boundary_conditions_order_parameter(std::vector<std::vector<std::vector<double>>>& func) {
    no_slip_bottom(func);
    no_slip_upper(func);
    // set_adiabatic_left(func);
    // set_adiabatic_right(func);
    
    periodic_left(func);
    periodic_right(func);
    // no_slip_left(func);
    // no_slip_right(func);
    // handle_corners(func);
}


inline void order_parameter_evolution(){
    compute_geq();
    collision_g();
    streaming(g);
    boundary_conditions_order_parameter(g);
}


inline void momentum_evolution(){
    compute_feq();
    collision_f();
    streaming(f);
    boundary_conditions_velocity(f);
}


inline void streamline_calculations(){
        streamline[0][0] = 0.0;
    
        // по оси x: d(psi) = -v * dx
        for (int x = 1; x < Nx; x++) {
            double v_prev = u[x - 1][0][1];
            double v_curr = u[x][0][1];
            streamline[x][0] = streamline[x - 1][0] - 0.5 * (v_prev + v_curr);
        }
    
        // вверх по оси y для каждого столбца x: d(psi) = u * dy
        for (int x = 0; x < Nx; x++) {
            for (int y = 1; y < Ny; y++) {
                double u_prev = u[x][y - 1][0];
                double u_curr = u[x][y][0];
                streamline[x][y] = streamline[x][y - 1] + 0.5 * (u_prev + u_curr);
            }
        }
}



inline void take_step(int& time_step) {
    compute_phi();         
    compute_rho();      
 
    compute_tau();

    compute_grads_phi();   
    compute_normal_vector();

    compute_mu_phi();
    
    compute_surface_force_isothemal();
    
    compute_body_force(time_step);
    compute_total_force();      

    compute_velocity();   
    
    compute_d_dt_u_phi();
    save_u_phi();
    
    compute_source_term_f(time_step);
    compute_source_term_g();

    compute_s_o_u();
    compute_pressure();

    momentum_evolution();
    order_parameter_evolution();

    
    
    // streamline_calculations();
}
