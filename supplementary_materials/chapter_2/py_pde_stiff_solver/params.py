def get_simulation_params(pde_model='volodin_2025'):
    if pde_model == 'volodin_2025':
        return {
            't_range': 250,
            # 'dt': 1e-4,
            'Ca': 2.5,
            'G0': 0.0,
            'phi': 0,
            'Pr': 7.0,
            'Bi': 1,
            'Ma': 5,
            'omega': 3.5,
            'b': 3,
            'bc': {'x': 'periodic'},
        }
    elif pde_model == 'shklyaev_2008_viii_b':
        return {
            't_range': 500,
            'V': 0,
            'k': 1.1,
            'G0': 3.33 * 10**-4,
            'omega': 0.02,
            'bc': {'x': 'periodic'},
        }
    else:
        raise ValueError(f'Unknown model_name: {pde_model}')
