"""
Вычисление безразмерных критериев подобия для воды:

  Pr  = ν / χ                        — число Прандтля
  G   = g·H₀³ / ν²                   — число Галилея
  Ma  = -(dσ/dT)·|∂T/∂y|·H₀² / (6ρν²) — число Марангони (модифицированное)
  Bi* = q·H₀ / κ                     — число Био (тепловой поток)
  Ca* = σ·H₀ / (ρν²)                 — число Капиллярности (модифицированное)
  B*  = a / H₀                       — безразмерная амплитуда
  ω*  = Ω·H₀² / ν                    — безразмерная частота
"""

import math

# ─────────────────────────────────────────────
# Свойства воды при T = 20 °C (по умолчанию)
# ─────────────────────────────────────────────
WATER_PROPS = {
    "T_C":        20.0,    # температура, °C
    "rho":       998.2,    # плотность, кг/м³
    "nu":       1.004e-6,  # кинематическая вязкость, м²/с
    "chi":      1.43e-7,   # температуропроводность, м²/с
    # "kappa":    0.598,     # теплопроводность ВОДЫ, Вт/(м·К)
    "kappa":    0.1,     # теплопроводность ПОДЛОЖКИ, Вт/(м·К)
    "sigma":    0.07275,   # коэффициент поверхностного натяжения, Н/м
    "dsigma_dT": -1.56e-4,  # dσ/dT, Н/(м·К)  (для воды ≈ −1.56×10⁻⁴)
    "g":        9.81,      # ускорение свободного падения, м/с²
    "Hamaker_const": 6 * math.pi * 10**-21,  # Дж, константа Гамакера 
}

# ACETONE_PROPS = {
#     "T_C":        20.0,     # температура, °C
#     "rho":        784.5,    # плотность, кг/м³
#     "nu":       3.2e-7,     # кинематическая вязкость, м²/с
#     "chi":      1.15e-7,    # температуропроводность, м²/с
#     "kappa":    0.180,      # теплопроводность, Вт/(м·К)
#     "sigma":    0.0237,     # поверхностное натяжение, Н/м
#     "dsigma_dT": -9.0e-5,   # dσ/dT, Н/(м·К)
#     "g":         9.81,      # м/с²
#     "Hamaker_const": 10**123,  # Дж, константа Гамакера 
# }


def compute_criteria(
    H0: float,          # характерный размер (толщина слоя), м
    dT_dy: float,       # градиент температуры ∂T/∂y, К/м
    q: float,           # плотность теплового потока, Вт/м²
    a: float,           # амплитуда колебаний, м
    Omega: float,       # циклическая частота колебаний, рад/с
    props: dict = None,
) -> dict:
    """Возвращает словарь со значениями всех критериев."""

    if props is None:
        props = WATER_PROPS

    nu = props["nu"]
    chi = props["chi"]
    kappa = props["kappa"]
    sigma = props["sigma"]
    dsigma = props["dsigma_dT"]
    rho = props["rho"]
    g = props["g"]
    Hamaker_const = props["Hamaker_const"]

    Pr = nu / chi
    G = g * H0**3 / nu**2
    Ma = (-dsigma * abs(dT_dy) * H0**2) / (rho * nu**2)
    Bi_star = q * H0 / kappa
    Ca_star = sigma * H0 / (rho * nu**2)
    B_star = a / H0
    omega_star = Omega * H0**2 / nu
    
    A_Hamaker = Hamaker_const / (6 * math.pi * rho * nu **  2 * H0)

    return {
        "Pr":       Pr,
        "G":        G,
        "Ma":       Ma,
        "Bi*":      Bi_star,
        "Ca*":      Ca_star,
        "B*":       B_star,
        "ω*":       omega_star,
        "A_Hamaker": A_Hamaker,
    }


def print_results(results: dict, H0, dT_dy, q, a, Omega, props):
    """Красивый вывод результатов."""
    print("=" * 55)
    print("  БЕЗРАЗМЕРНЫЕ КРИТЕРИИ ПОДОБИЯ ДЛЯ ВОДЫ")
    print("=" * 55)
    print(f"\n  Свойства воды при T = {props['T_C']} °C:")
    print(f"    ρ   = {props['rho']:.1f}   кг/м³")
    print(f"    ν   = {props['nu']:.3e} м²/с")
    print(f"    χ   = {props['chi']:.3e} м²/с")
    print(f"    κ   = {props['kappa']:.3f}  Вт/(м·К)")
    print(f"    σ   = {props['sigma']:.5f} Н/м")
    print(f"    dσ/dT = {props['dsigma_dT']:.2e} Н/(м·К)")
    print(f"\n  Задаваемые параметры задачи:")
    print(f"    H₀  = {H0}  м (толщина)")
    print(f"    ∂T/∂y = {dT_dy:.2e} К/м")
    print(f"    q   = {q} Вт/м² (поток)")
    print(f"    a   = {a} м (амплитуда)")
    print(f"    Ω   = {Omega} рад/с (частота)")
    print()
    print("  Результаты:")
    print("-" * 55)

    descriptions = {
        "Pr":  "Прандтля      Pr  = ν/χ",
        "G":   "Галилея       G   = gH₀³/ν²",
        "Ma":  "Марангони     Ma  = -(dσ/dT)|∂T/∂y|H₀²/(6ρν²)",
        "Bi*": "Био*          Bi* = qH₀/κ",
        "Ca*": "Капилл.*      Ca* = σH₀/(ρν²)",
        "B*":  "Безразм.амп.  B*  = a/H₀",
        "ω*":  "Безразм.част. ω*  = ΩH₀²/ν",
    }

    for key, val in results.items():
        label = descriptions.get(key, key)
        print(f"    {label:<42} = {val:.4e}")

    print("=" * 55)


def assess(results: dict):
    """Качественная оценка значений."""
    print("\n  Качественная оценка:")
    print("-" * 55)

    Pr = results["Pr"]
    if Pr < 1:
        note = "теплообмен интенсивнее импульсопереноса"
    elif 1 <= Pr <= 10:
        note = "умеренный режим (типично для воды)"
    else:
        note = "вязкость доминирует над теплопроводностью"
    print(f"    Pr  = {Pr:.2f}  → {note}")

    G = results["G"]
    print(
        f"    G   = {G:.3e}  → {'гравитация значима' if G > 1e4 else 'гравитация мала'}")

    Ma = results["Ma"]
    print(
        f"    Ma  = {Ma:.3e}  → {'Марангони-конвекция значима' if Ma > 1 else 'Марангони-эффект слаб'}")

    Ca = results["Ca*"]
    print(
        f"    Ca* = {Ca:.3e}  → {'поверхностное натяжение важно' if Ca > 1 else 'поверхн. натяжение слабо'}")

    print("=" * 55)


# ─────────────────────────────────────────────
# Пример: типичный тонкий слой воды
# ─────────────────────────────────────────────
if __name__ == "__main__":
    H0 = 10**-4  # толщина слоя m
    Omega = 1000
    params = dict(
        H0=H0,    # толщина слоя m
        dT_dy=1.0 / H0,  # градиент температуры К/м
        q=10.0,   # тепловой поток   Вт/м²
        a=H0 * 10,    # амплитуда колебаний m
        Omega=Omega,    # частота 10 рад/с
    )
    WATER_PROPS["nu"] = 1.0 * 10**-6 
    results = compute_criteria(**params, props=WATER_PROPS)
    print_results(results, **params, props=WATER_PROPS)
    
    # results = compute_criteria(**params, props=ACETONE_PROPS)
    # print_results(results, **params, props=ACETONE_PROPS)
    
    # assess(results)
