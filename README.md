# Диссертация и дополнительные материалы

Данный репозиторий содержит исходные материалы диссертации **«ДИНАМИКА ПОВЕРХНОСТИ РАЗДЕЛА В ВЕРТИКАЛЬНОМ ВИБРАЦИОННОМ ПОЛЕ»**: исходный код LaTeX, библиографическую базу данных, иллюстрации, дополнительные аналитические и численные результаты, а также программные реализации численных методов, использованных при проведении исследований.

Репозиторий организован в соответствии со структурой диссертации. Дополнительные материалы, включая исходный код программ и результаты вычислений, сгруппированы по соответствующим главам.

## Содержание диссертации

- **Введение**

- **Глава 1. Обзор литературы**
  - 1.1. Динамика тонких пленок
    - 1.1.1. Гравитационные эффекты: стекание тонких пленок
    - 1.1.2. Термокапиллярная конвекция
    - 1.1.3. Тонкие пленки магнитной жидкости
    - 1.1.4. Вибрационные эффекты в жидких пленках
  - 1.2. Метод решеточных уравнений Больцмана
    - 1.2.1. LBM для задач со свободной границей раздела

- **Глава 2. Термокапиллярная конвекция тонкого слоя жидкости под воздействием вертикальных вибраций**
  - 2.1. Система уравнений термокапиллярной конвекции под действием вибраций
  - 2.2. Метод решения
  - 2.3. Пульсационное течение
  - 2.4. Осредненное течение
  - 2.5. Осредненные уравнения динамики межфазной границы и температуры
  - 2.6. Анализ устойчивости пленки в линейной постановке
  - 2.7. Численное моделирование осредненной системы
    - 2.7.1. Влияние амплитуды и волнового числа начального возмущения
    - 2.7.2. Карты устойчивости для различных чисел Марангони и в условиях микрогравитации и невесомости
  - 2.8. Слабонелинейный анализ
  - 2.9. Выводы по главе

- **Глава 3. Динамика тонкого слоя магнитной жидкости в стационарном магнитном поле под воздействием вертикальных вибраций**
  - 3.1. Система уравнений феррожидкости со свободной границей под действием вибраций
  - 3.2. Метод решения
  - 3.3. Распределение магнитного поля при малых отклонениях свободной границы
  - 3.4. Пульсационное течение
  - 3.5. Осредненное течение
  - 3.6. Анализ устойчивости пленки в линейной постановке
  - 3.7. Выводы по главе

- **Глава 4. Численное моделирование динамики межфазной границы при вертикальных вибрациях методом решеточных уравнений Больцмана**
  - 4.1. Макроскопическая постановка задачи
  - 4.2. Метод решеточных уравнений Больцмана для задач с межфазной границей
    - 4.2.1. Дискретная схема для восстановления уравнения переноса импульса
    - 4.2.2. Дискретная схема для восстановления уравнения для параметра порядка
  - 4.3. Верификация численной схемы
    - 4.3.1. Сравнение с линейной теорией устойчивости
    - 4.3.2. Исследование сеточной зависимости
    - 4.3.3. Неустойчивость Рэлея — Тейлора
    - 4.3.4. Влияние вибраций на неустойчивость Рэлея — Тейлора
  - 4.4. Возникновение гравитационно-капиллярных волн под действием вертикальных вибраций
  - 4.5. Движение слоя жидкости под действием вертикальных вибраций
  - 4.6. Стабилизация тяжелого слоя жидкости в легкой фракции под действием вертикальных вибраций
  - 4.7. Выводы по главе

- **Заключение**

## Структура репозитория

```text
.
├── figures/
├── supplementary_materials/
├── gost2008-1.bst
├── thesis_thin_films.bib
└── thesis_viv.tex
```

### Основные файлы и директории

- `thesis_viv.tex` — основной исходный файл диссертации в формате LaTeX.
- `thesis_thin_films.bib` — библиографическая база данных.
- `gost2008-1.bst` — стиль оформления библиографии BibTeX в соответствии с ГОСТ.
- `figures/` — иллюстрации, используемые в диссертации.
- `supplementary_materials/` — дополнительные аналитические материалы, численные результаты, программные коды и скрипты.

## Дополнительные материалы

Дополнительные материалы организованы по главам диссертации.

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

### Глава 2. Термокапиллярная конвекция тонких пленок

Содержит численные скрипты и результаты вычислений, относящиеся к теоретическому исследованию динамики тонких пленок под воздействием вертикальных вибраций.

- `dimensless_params.py` — оценка и вычисление безразмерных параметров задачи.
- `linear_stability_plotter/` — скрипты для анализа линейной устойчивости и визуализации результатов.
- `m_vs_omega_plotter.py` — построение зависимости волнового числа наиболее неустойчивой моды от частоты вибраций.
- `py_pde_stiff_solver/` — численный решатель осредненной системы уравнений на основе библиотеки `py-pde`.
- `WNA_coeff.pdf` — коэффициенты слабонелинейного анализа.
- `pulsatile_solution.pdf` — результаты расчета пульсационного решения.
- `weakly_nonlinear_analysis.pdf` — результаты слабонелинейного анализа.

### Глава 3. Динамика тонких пленок магнитной жидкости

Содержит скрипты и результаты вычислений, относящиеся к исследованию динамики пленок магнитной жидкости в стационарном магнитном поле под воздействием вертикальных вибраций.

- `governing_params_estimations.py` — оценка определяющих безразмерных параметров задачи.
- `linear_stability_plotter.py` — анализ линейной устойчивости и визуализация результатов.
- `magnetic_field_distribution.pdf` — распределение магнитного поля.
- `pulsating_fields_solutions.pdf` — результаты расчета пульсационных составляющих полей.
- `pulsating_fields_solutions_[WRONG_B_TERM_SIGN].pdf` — промежуточный результат вычислений, сохраненный для справки. Содержит ошибочный знак при магнитном слагаемом и не используется в диссертации.

### Глава 4. Численное моделирование методом решеточных уравнений Больцмана

Содержит реализацию метода решеточных уравнений Больцмана (LBM) на языке C++, использованную для прямого численного моделирования динамики межфазной границы под воздействием вертикальных вибраций.

Программная реализация разделена на отдельные заголовочные файлы:

- `main.cpp` — основной файл запуска вычислений.
- `constants.h` — параметры модели и численные константы.
- `initial_distribution.h` — инициализация функций распределения.
- `evolution.h` — эволюция функций распределения.
- `streaming.h` — этап переноса (streaming).
- `boundary_conditions.h` — граничные условия.
- `convergence.h` — процедуры, связанные с контролем сходимости.
- `health_check.h` — диагностика численной схемы и проверки согласованности.
- `io.h` — операции ввода-вывода.
- `utility_plotters/` — вспомогательные скрипты для визуализации и постобработки результатов.
- `run.sh` — скрипт запуска вычислений.

---

# Dissertation and Supplementary Materials

This repository contains the source materials for the dissertation **"Dynamics of Free Surface in Vertical Vibrational Field"**, including the LaTeX source code, bibliography database, figures, supplementary analytical and numerical results, and software implementations of the numerical methods used in the research. Full text is currently **in Russian language**. 

The repository follows the structure of the dissertation. Supplementary materials, including source code and computational results, are organized according to the corresponding chapters.

## Dissertation Contents

- **Introduction**

- **Chapter 1. Literature Review**
  - 1.1. Thin-Film Dynamics
    - 1.1.1. Gravitational Effects: Thin-Film Drainage
    - 1.1.2. Thermocapillary Convection
    - 1.1.3. Magnetic Liquid Films
    - 1.1.4. Vibrational Effects in Liquid Films
  - 1.2. Lattice Boltzmann Method
    - 1.2.1. LBM for Problems with Free Interfaces

- **Chapter 2. Thermocapillary Convection in a Thin Liquid Layer under Vertical Vibrations**
  - 2.1. Governing Equations for Thermocapillary Convection under Vibrations
  - 2.2. Solution Method
  - 2.3. Pulsatile Flow
  - 2.4. Averaged Flow
  - 2.5. Averaged Equations for Interface Dynamics and Temperature
  - 2.6. Linear Stability Analysis of the Film
  - 2.7. Numerical Simulation of the Averaged System
    - 2.7.1. Effects of the Initial Perturbation Amplitude and Wavenumber
    - 2.7.2. Stability Maps for Different Marangoni Numbers and under Microgravity and Weightlessness Conditions
  - 2.8. Weakly Nonlinear Analysis
  - 2.9. Conclusions

- **Chapter 3. Dynamics of a Thin Magnetic Liquid Layer in a Static Magnetic Field under Vertical Vibrations**
  - 3.1. Governing Equations for a Ferrofluid with a Free Surface under Vibrations
  - 3.2. Solution Method
  - 3.3. Magnetic Field Distribution for Small Free-Surface Deformations
  - 3.4. Pulsatile Flow
  - 3.5. Averaged Flow
  - 3.6. Linear Stability Analysis of the Film
  - 3.7. Conclusions

- **Chapter 4. Lattice Boltzmann Simulations of Interfacial Dynamics under Vertical Vibrations**
  - 4.1. Macroscopic Problem Formulation
  - 4.2. Lattice Boltzmann Method for Problems with an Interface
    - 4.2.1. Discrete Scheme for Recovering the Momentum Transport Equation
    - 4.2.2. Discrete Scheme for Recovering the Order Parameter Equation
  - 4.3. Numerical Scheme Verification
    - 4.3.1. Comparison with Linear Stability Theory
    - 4.3.2. Grid-Dependence Study
    - 4.3.3. Rayleigh–Taylor Instability
    - 4.3.4. Effect of Vibrations on Rayleigh–Taylor Instability
  - 4.4. Generation of Gravity-Capillary Waves under Vertical Vibrations
  - 4.5. Motion of a Liquid Layer under Vertical Vibrations
  - 4.6. Stabilization of a Heavy Liquid Layer within a Light Fluid under Vertical Vibrations
  - 4.7. Conclusions

- **Conclusion**

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
- `gost2008-1.bst` — BibTeX bibliography style conforming to GOST standards.
- `figures/` — figures used in the dissertation.
- `supplementary_materials/` — supplementary analytical materials, numerical results, source code, and scripts.

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

### Chapter 2. Thermocapillary Convection in Thin Films

Contains numerical scripts and computational results related to the theoretical investigation of thin-film dynamics under vertical vibrations.

- `dimensless_params.py` — estimation and calculation of the governing dimensionless parameters.
- `linear_stability_plotter/` — scripts for linear stability analysis and visualization.
- `m_vs_omega_plotter.py` — plotting the dependence of the most unstable mode's wavenumber on the vibration frequency.
- `py_pde_stiff_solver/` — numerical solver for the averaged system of equations based on the `py-pde` library.
- `WNA_coeff.pdf` — coefficients of the weakly nonlinear analysis.
- `pulsatile_solution.pdf` — results for the pulsatile solution.
- `weakly_nonlinear_analysis.pdf` — results of the weakly nonlinear analysis.

### Chapter 3. Dynamics of Thin Magnetic Liquid Films

Contains scripts and computational results related to the investigation of magnetic liquid film dynamics in a static magnetic field under vertical vibrations.

- `governing_params_estimations.py` — estimation of the governing dimensionless parameters.
- `linear_stability_plotter.py` — linear stability analysis and visualization.
- `magnetic_field_distribution.pdf` — magnetic field distribution.
- `pulsating_fields_solutions.pdf` — results for the pulsating components of the fields.
- `pulsating_fields_solutions_[WRONG_B_TERM_SIGN].pdf` — an intermediate computational result retained for reference. It contains an incorrect sign in the magnetic-field term and is not used in the dissertation.

### Chapter 4. Lattice Boltzmann Simulations

Contains a C++ implementation of the lattice Boltzmann method (LBM) used for direct numerical simulations of interfacial dynamics under vertical vibrations.

The implementation is divided into separate header files:

- `main.cpp` — main simulation entry point.
- `constants.h` — model parameters and numerical constants.
- `initial_distribution.h` — initialization of the distribution functions.
- `evolution.h` — evolution of the distribution functions.
- `streaming.h` — streaming step.
- `boundary_conditions.h` — boundary conditions.
- `convergence.h` — convergence-related procedures.
- `health_check.h` — numerical diagnostics and consistency checks.
- `io.h` — input/output operations.
- `utility_plotters/` — auxiliary plotting and post-processing scripts.
- `run.sh` — simulation execution script.