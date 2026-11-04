from math import sqrt, radians, sin

# PHYSICAL UNITS
L = 0.35  # meters

c_s = 1 / sqrt(3)

speed_sound = 1500  # m / s
gravity = 9.8       # m / (s * s)

Ny = 1000

dy = L / Ny

visco_real = 1.6 * 10**-4
# dt = (c_s / speed_sound) * dy
visco_LBM = 0.106
tau_f = (visco_LBM / (c_s * c_s)) + 0.5
print(f'tau_f = {tau_f}')
dt = (visco_LBM / visco_real) * dy * dy

print(f'dt = {dt}')
print(f'dy = {dy}')

gravity_LBM = (gravity * (dt * dt)) / dy 

print(f'gravity_LBM={gravity_LBM}')


Re_LBM = (gravity_LBM * Ny * Ny * Ny ) / (visco_LBM * visco_LBM)

print(f'Re_LBM={Re_LBM}')

_speed_sound_ = c_s * (dy / dt)

print(f'_speed_sound_={_speed_sound_}')

sigma = 72 * 10**-3

sigma_LBM = sigma * (dt * dt) 

print(f'sigma_LBM={sigma_LBM}')

print('================================================')
print('================================================')


