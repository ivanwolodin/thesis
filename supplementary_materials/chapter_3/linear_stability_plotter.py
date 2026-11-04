import numpy as np
import matplotlib.pyplot as plt

# ---------------------- Параметры задачи ----------------------
G = 3
# H_ef = 90
Ca = 3
Omega = 6.1
chi = 0.5

A_values = [0.2, 2, 20]    
k = np.linspace(0, 1.8, 50) 

# ---------------------- Вычисление theta и Re[tanh(theta)/theta] ----------------------
theta = np.sqrt(1j * Omega)                 # theta^2 = i*Omega
ratio = np.tanh(theta) / theta              # комплексное число
Re_ratio = ratio.real                       # действительная часть

# ---------------------- Формула для lambda_r ----------------------
def lambda_r(k, A, H_ef):
    term_G  = -G * k**2
    term_Ca = -Ca * k**4
    term_A  = (+A * (Re_ratio - 1) * k**4) / 2.0
    term_H  = H_ef / (2 * (1 + chi) + k) * k**3
    return (term_G + term_Ca + term_A + term_H) / 2.0


plt.figure(figsize=(8, 6))

H_ef = 30
A = 20
plt.plot(k, lambda_r(k=k, A=0, H_ef=H_ef), label=fr'$A={0}, H_e={H_ef}$', linewidth=2, ls="solid")
plt.plot(k, lambda_r(k=k, A=A, H_ef=0), label=fr'$A={A}, H_e={0}$', linewidth=2, ls="dashed")
plt.plot(k, lambda_r(k=k, A=A, H_ef=H_ef), label=fr'$A={A}, H_e={H_ef}$', linewidth=2, ls = "dotted")

plt.axhline(0, color='gray', linewidth=0.8, linestyle='--')
plt.xlabel(r'$k$', fontsize=18)
plt.ylabel(r'$\lambda$', fontsize=18)
# plt.title(r'$\lambda_r(k)$ при $G=3,\ Ca=3,\ H_{ef}=20,\ \Omega=1.1,\ \chi=1$', fontsize=12)
plt.legend(fontsize=18)
plt.tick_params(axis='both', labelsize=18)
plt.grid(True, alpha=0.3)
plt.tight_layout()

# plt.savefig('lambda_r_vs_k.png', dpi=150)
plt.show()