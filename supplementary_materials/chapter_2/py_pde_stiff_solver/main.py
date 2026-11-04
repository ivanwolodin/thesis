from os import makedirs

# from numpy import arange

from params import get_simulation_params
from initial_conditions.init_fields import prepare_initial_conditions
from runner.run import run_simulation
from io_utils.save_txt import save_res_to_txt
from io_utils.plotter import plot_results_to_file


def params_to_folder_name(params: dict) -> str:
    excluded = {'t_range', 'dt', 'bc'}
    parts = []

    for key, value in params.items():
        if key in excluded:
            continue
        parts.append(f'{key}={value}')

    return '_'.join(parts)


def run_with_different_initial_conditions():
    params = get_simulation_params(pde_model='volodin_2025')
    # -------------------------------------------------------------
    # Корневая папка: имя формируется ИЗ ПАРАМЕТРОВ
    # -------------------------------------------------------------
    params_folder = params_to_folder_name(params)
    root_output_dir = f'results/{params_folder}'
    makedirs(root_output_dir, exist_ok=True)
    print(f'Root folder: {root_output_dir}')

    initial_amplitude_values = [
        0.001,
        0.01,
        0.1,
        0.15,
        0.2,
        0.25,
        0.3,
        0.35,
        0.4,
        0.45,
        0.5,
    ]
    wave_k_values = [
        2.4,
        2.5,
        2.6,
        2.7,
        2.8,
        2.9,
        3.0,
        3.1,
        3.2,
        3.3,
        3.4,
        3.5,
        3.6,
        3.7,
        3.8,
        3.9,
        4.0,
    ]

    for initial_amplitude in initial_amplitude_values:
        for wave_k in wave_k_values:

            initial_h, initial_T = prepare_initial_conditions(
                perturbation_amplitude=initial_amplitude,
                wave_k=wave_k,
            )

            result, storage, is_solved = run_simulation(
                pde_model='volodin_2025',
                initial_h=initial_h,
                initial_T=initial_T,
                **params,
            )
            print('Simulation stopped')

            # подпапка с параметрами начальных условий
            output_dir = (
                f'{root_output_dir}/'
                f'k={wave_k:.2f}_a={initial_amplitude}_is_solved={is_solved}'
            )
            makedirs(output_dir, exist_ok=True)

            save_res_to_txt(storage, output_dir, is_solved)
            plot_results_to_file(storage, output_dir, is_solved)


def run_with_different_external_freqs_and_amplitudes():
    params = get_simulation_params(pde_model='volodin_2025')
    amplitudes = [
        0.0,
        0.1,
        0.2,
        0.3,
        0.4,
        0.5,
        0.6,
        0.7,
        0.8,
        0.9,
        1.0,
        1.1,
        1.2,
        1.3,
        1.4,
        1.5,
        1.6,
        1.7,
        1.8,
        1.9,
        2.0,
        2.1,
        2.2,
        2.3,
        2.4,
        2.5,
        2.6,
        2.7,
        2.8,
        2.9,
        3.0,
        3.1,
        3.2,
        3.3,
        3.4,
        3.5,
        3.6,
        3.7,
        3.8,
        3.9,
        4.0,
    ]
    omega_frs = [
        0.5,
        0.6,
        0.7,
        0.8,
        0.9,
        1.0,
        1.1,
        1.2,
        1.3,
        1.4,
        1.5,
        1.6,
        1.7,
        1.8,
        1.9,
        2.0,
        2.1,
        2.2,
        2.3,
        2.4,
        2.5,
        2.6,
        2.7,
        2.8,
        2.9,
        3.0,
        3.1,
        3.2,
        3.3,
        3.4,
        3.5,
        3.6,
        3.7,
        3.8,
        3.9,
        4.0,
    ]

    initial_h, initial_T = prepare_initial_conditions(
        perturbation_amplitude=0.01,
        wave_k=2.0,
    )

    for om in omega_frs:
        for ampl in amplitudes:
            params['b'] = ampl
            params['omega'] = om
            print(f'parameters: {params}')

            result, storage, is_solved = run_simulation(
                pde_model='volodin_2025',
                initial_h=initial_h,
                initial_T=initial_T,
                **params,
            )
            print('Simulation stopped')

            # подпапка с параметрами начальных условий
            Maran = params['Ma']
            root_output_dir = f'results/Ma={Maran}_ampl={ampl}_omfr={om}_is_solved={is_solved}'
            makedirs(root_output_dir, exist_ok=True)

            save_res_to_txt(storage, root_output_dir, is_solved)
            plot_results_to_file(storage, root_output_dir, is_solved)


def run_single():
    # params = get_simulation_params(pde_model='shklyaev_2008_viii_b')
    params = get_simulation_params(pde_model='volodin_2025')
    initial_h, initial_T = prepare_initial_conditions(
        perturbation_amplitude=0.01,
        wave_k=2.0,
    )
    print(f'parameters: {params}')

    # result, storage, is_solved = run_simulation(
    #     pde_model='shklyaev_2008_viii_b',
    #     initial_h=initial_h,
    #     **params,
    # )
    result, storage, is_solved = run_simulation(
        pde_model='volodin_2025',
        initial_h=initial_h,
        initial_T=initial_T,
        **params,
    )
    print('Simulation stopped')

    root_output_dir = 'results'
    makedirs(root_output_dir, exist_ok=True)

    save_res_to_txt(storage, root_output_dir, is_solved)
    plot_results_to_file(storage, root_output_dir, is_solved)


def optimized_run_with_different_external_freqs_and_amplitudes():
    params = get_simulation_params(pde_model='volodin_2025')
    amplitudes = [round(x * 0.1, 1) for x in range(41)]  # 0.0 .. 4.0
    omega_frs = [round(x * 0.1, 1) for x in range(5, 41)]  # 0.5 .. 4.0

    initial_h, initial_T = prepare_initial_conditions(
        perturbation_amplitude=0.01,
        wave_k=2.0,
    )

    for om in omega_frs:
        print(f'\n=== omega = {om} ===')
        boundary_found = False

        for ampl in amplitudes:
            params['b'] = ampl
            params['omega'] = om
            print(f'parameters: {params}')

            result, storage, is_solved = run_simulation(
                pde_model='volodin_2025',
                initial_h=initial_h,
                initial_T=initial_T,
                **params,
            )
            print('Simulation stopped')

            G0 = params['G0']
            root_output_dir = f'results/G0={G0}_ampl={ampl}_omfr={om}_is_solved={is_solved}'
            makedirs(root_output_dir, exist_ok=True)
            # save_res_to_txt(storage, root_output_dir, is_solved)
            # plot_results_to_file(storage, root_output_dir, is_solved)

            if is_solved:
                print(
                    f'>>> Граница устойчивости найдена: om={om}, ampl={ampl}. '
                    f'Пропускаем большие амплитуды.'
                )
                boundary_found = True
                break  # дальше по амплитуде всё будет True — незачем считать

        if not boundary_found:
            print(f'>>> Для om={om} граница не найдена (всё неустойчиво).')


def optimized_run_with_different_initial_conditions():
    params = get_simulation_params(pde_model='volodin_2025')
    params_folder = params_to_folder_name(params)
    root_output_dir = f"results/Ma={params.get('Ma')}"
    makedirs(root_output_dir, exist_ok=True)
    print(f'Root folder: {root_output_dir}')

    initial_amplitude_values = sorted(
        [
            0.001,
            0.01,
            0.1,
            0.15,
            0.2,
            0.25,
            0.3,
            0.35,
            0.4,
            0.45,
            0.5,
        ]
    )  # от маленьких к большим

    wave_k_values = sorted(
        [
            1.0,
            1.1,
            1.2,
            1.3,
            1.4,
            1.5,
            1.6,
            1.7,
            1.8,
            1.9,
            2.0,
            2.1,
            2.2,
            2.3,
            2.4,
            2.5,
            2.6,
            2.7,
            2.8,
            2.9,
            3.0,
            3.1,
            3.2,
            3.3,
            3.4,
            3.5, 
            3.6, 
            3.7,
            3.8, 
            3.9,
            4.0,
        ],
        reverse=True,
    )  # от больших к маленьким

    # Запоминаем минимальное устойчивое k для каждой амплитуды
    # Всё, что ниже этой границы — заведомо False, можно пропускать
    # При росте амплитуды граница может только сдвигаться вправо (к бо́льшим k)
    min_stable_k = None  # нижняя граница устойчивости с предыдущей амплитуды

    for initial_amplitude in initial_amplitude_values:
        print(f'\n=== Amplitude: {initial_amplitude} ===')
        found_false = False

        for wave_k in wave_k_values:
            # Пропускаем k, которые заведомо неустойчивы (ниже границы прошлой амплитуды)
            # При большей амплитуде граница устойчивости сдвигается вправо,
            # поэтому k ниже предыдущей границы проверять бессмысленно
            if min_stable_k is not None and wave_k < min_stable_k:
                print(
                    f'  k={wave_k:.2f}: skipped (below previous stability boundary)'
                )
                continue

            initial_h, initial_T = prepare_initial_conditions(
                perturbation_amplitude=initial_amplitude,
                wave_k=wave_k,
            )

            result, storage, is_solved = run_simulation(
                pde_model='volodin_2025',
                initial_h=initial_h,
                initial_T=initial_T,
                **params,
            )
            print(f'  k={wave_k:.2f}: is_solved={is_solved}')

            output_dir = (
                f'{root_output_dir}/'
                f'k={wave_k:.2f}_a={initial_amplitude}_is_solved={is_solved}'
            )
            makedirs(output_dir, exist_ok=True)
            # save_res_to_txt(storage, output_dir, is_solved)
            # plot_results_to_file(storage, output_dir, is_solved)

            if not is_solved:
                # Нашли границу: дальше (меньшие k) при этой амплитуде — всё False
                print(
                    f'  → Stability boundary for amplitude={initial_amplitude}: k={wave_k:.2f}'
                )
                min_stable_k = (
                    wave_k  # обновляем границу для следующих амплитуд
                )
                found_false = True
                break  # прекращаем перебор k для этой амплитуды

        if not found_false:
            print(
                f'  → Stable for all tested k at amplitude={initial_amplitude}'
            )


def main():
    # optimized_run_with_different_initial_conditions()
    # optimized_run_with_different_external_freqs_and_amplitudes()
    # run_with_different_initial_conditions()
    # run_with_different_external_freqs_and_amplitudes()
    run_single()


if __name__ == '__main__':
    main()
