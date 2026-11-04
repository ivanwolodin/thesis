#include <iostream>

#include "constants.h"
#include "evolution.h"
#include "initial_distribution.h"
#include "io.h"


int main() {
    greetings();
    
    // setup_initial();
    
    setup_simulation(0);
    dump_simulation_params();
    output_field(0, "tau");
    output_field(0, "rho");
    for (int step_time = 0; step_time < steps_number + 1; step_time++) {
        std::cout << "Time step " << step_time << std::endl;
        if (step_time <= 200000){
            Ampl = 0;
        }
        else{
            Ampl = 100;
        }
        take_step(step_time);
        save_results(step_time);
        check_health();
    }
    
    bye();
    
    return 0;
}

