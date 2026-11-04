# Supplementary Materials for the Dissertation

This repository contains the LaTeX source code of the dissertation, bibliography, figures, supplementary materials, and numerical codes used to obtain the results presented in the dissertation.

## Repository Structure

```text
.
├── figures/
├── supplementary_materials/
├── gost2008-1.bst
├── thesis_thin_films.bib
└── thesis_viv.tex
```

### Main Files and Directories

- `thesis_viv.tex` — main LaTeX source file of the dissertation.
- `thesis_thin_films.bib` — bibliography database.
- `gost2008-1.bst` — BibTeX bibliography style.
- `figures/` — figures used in the dissertation.
- `supplementary_materials/` — supplementary numerical codes, scripts, and computational results.

## Supplementary Materials

The supplementary materials are organized according to the dissertation chapters.

```text
supplementary_materials/
├── chapter_2/
│   ├── WNA_coeff.pdf
│   ├── dimensless_params.py
│   ├── linear_stability_plotter/
│   ├── m_vs_omega_plotter.py
│   ├── pulsatile_solution.pdf
│   ├── py_pde_stiff_solver/
│   └── weakly_nonlinear_analysis.pdf
│
├── chapter_3/
│   ├── governing_params_estimations.py
│   ├── linear_stability_plotter.py
│   ├── magnetic_field_distribution.pdf
│   ├── pulsating_fields_solutions.pdf
│   └── pulsating_fields_solutions_[WRONG_B_TERM_SIGN].pdf
│
└── chapter_4/
    ├── boundary_conditions.h
    ├── constants.h
    ├── convergence.h
    ├── evolution.h
    ├── health_check.h
    ├── initial_distribution.h
    ├── io.h
    ├── main.cpp
    ├── run.sh
    ├── streaming.h
    └── utility_plotters/
```

### Chapter 2 — Vibrated Thin Films

Contains numerical scripts and computational results related to the theoretical analysis of thin-film dynamics under vertical vibrations.

- `dimensless_params.py` — estimation and evaluation of dimensionless parameters.
- `linear_stability_plotter/` — scripts for linear stability analysis and visualization.
- `m_vs_omega_plotter.py` — plotting of the dependence of the instability mode on the vibration frequency.
- `py_pde_stiff_solver/` — numerical solver based on the `py-pde` framework.
- `WNA_coeff.pdf` — weakly nonlinear analysis coefficients.
- `pulsatile_solution.pdf` — pulsatile solution.
- `weakly_nonlinear_analysis.pdf` — results of the weakly nonlinear analysis.

### Chapter 3 — Vibrated Ferrofluid Films

Contains scripts and computational results related to the dynamics of ferrofluid films under vertical vibrations and an external magnetic field.

- `governing_params_estimations.py` — estimation of governing dimensionless parameters.
- `linear_stability_plotter.py` — linear stability analysis and visualization.
- `magnetic_field_distribution.pdf` — magnetic field distribution.
- `pulsating_fields_solutions.pdf` — pulsating-field solutions.
- `pulsating_fields_solutions_[WRONG_B_TERM_SIGN].pdf` — intermediate computational result retained for reference; it contains an incorrect sign in the magnetic-field term and is not used in the dissertation.

### Chapter 4 — Lattice Boltzmann Simulations

Contains the C++ implementation of the lattice Boltzmann method (LBM) used for direct numerical simulations of interfacial dynamics under vertical vibrations.

The implementation is organized into separate header files:

- `main.cpp` — main simulation entry point.
- `constants.h` — model parameters and numerical constants.
- `initial_distribution.h` — initialization of distribution functions.
- `evolution.h` — evolution of the distribution functions.
- `streaming.h` — streaming step.
- `boundary_conditions.h` — boundary conditions.
- `convergence.h` — convergence-related procedures.
- `health_check.h` — numerical diagnostics and consistency checks.
- `io.h` — input/output operations.
- `utility_plotters/` — auxiliary plotting and post-processing scripts.
- `run.sh` — simulation execution script.
