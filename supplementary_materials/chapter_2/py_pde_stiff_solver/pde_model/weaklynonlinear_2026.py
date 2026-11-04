from pde import PDEBase, FieldCollection
from numpy import sqrt, sin, sinh, cos, cosh
import numpy as np

class Weaklynonlinear2026(PDEBase):
    def __init__(
        self,
        Ca: float = -10000,
        G0: float = -10000,
        phi: float = -10000,
        Pr: float = -10000,
        Bi: float = -10000,
        Ma: float = -10000,
        omega: float = -10000,
        b: float = -10000,
        bc: dict | None = None,
    ):
        super().__init__()
        self.Ca = Ca
        self.G0 = G0
        self.phi = phi
        self.Pr = Pr
        self.Bi = Bi
        self.Ma = Ma
        self.omega = omega
        self.b = b
        self.bc = bc or {'x': 'periodic'}
        self.g = self._gamma0(omega)
        self.m1 = self._m1(omega)
        self.m2 = self._m2(omega)
        self.R1, self.R2 = self._R1_R2(omega)
        print()
        print(
            f"Ca={self.Ca}, G0={self.G0}, phi={self.phi}, Pr={self.Pr}, Bi={self.Bi}, "
            f"Ma={self.Ma}, omega={self.omega}, b={self.b}, bc={self.bc}, "
            f"g={self.g}, m1={self.m1}, m2={self.m2}, R1={self.R1}, R2={self.R2}"
        )
        print()

    def _gamma0(self, omega: float) -> float:
        return sqrt(2.0 * omega)

    def _psi_phi(self, omega: float):
        psi_plus = cosh(self.g) + cos(self.g)
        psi_minus = cosh(self.g) - cos(self.g)
        phi_plus = sinh(self.g) + sin(self.g)
        phi_minus = sinh(self.g) - sin(self.g)
        return psi_plus, psi_minus, phi_plus, phi_minus

    def _m1(self, omega: float) -> float:
        g2 = self.g / 2.0
        num = sin(g2) * cos(g2) + sinh(g2) * cosh(g2)
        den = g2 * (cos(g2) ** 2 + sinh(g2) ** 2)
        return 1.0 - num / den

    def _m2(self, omega: float) -> float:
        g2 = self.g / 2.0

        num = cos(g2) ** 4 + sinh(g2) ** 2 * cosh(g2) ** 2 - cos(g2) ** 2
        den = (cos(g2) ** 2 + sinh(g2) ** 2) ** 2
        return num / den

    def _R1_R2(self, omega: float):
        psi_p, psi_m, phi_p, phi_m = self._psi_phi(omega)
        R1 = (
            3.0
            * (
                4.0 * sinh(self.g) * sin(self.g)
                - self.g * (psi_p * phi_p - psi_m * phi_m)
            )
            / (2.0 * self.g**2 * psi_p**2)
        )
        R2 = -1.0 / 3.0 + (11.0 * phi_m - 3.0 * self.g * psi_m) / (
            self.g**3 * psi_p**2
        )
        return R1, R2

    def _m3(self, omega: float, xi1, dxi1_dx) -> float:
        g2 = self.g / 2.0

        cos2 = cos(g2)
        sin2 = sin(g2)
        cosh2 = cosh(g2)
        sinh2 = sinh(g2)

        dxi = xi1**2 * dxi1_dx  # ξ₁² · ∂ξ₁/∂x

        denom = sqrt(2) * self.g * ((cos2**2 + sinh2**2)) ** 3

        b1 = (
            (
                -(1.0 / sqrt(2)) * self.g**2 * cosh2 * dxi
                + (self.g**2 / sqrt(2)) * sin2 * dxi
                + (-sqrt(2) * self.g**2 * dxi * cos2**2)
                + cosh2**2 * self.g * dxi
            )
            * cosh2
            * sinh2**3
        )

        b2 = (
            -3.0
            * cos2
            * (
                -(sqrt(2) / 3.0) * sin2 * cos2**2 * self.g**2 * dxi
                + cosh2**2 * sinh2 * (self.g**2 / 2.0) * dxi
                + (self.g**2 / sqrt(2)) * cosh2 * sin2
            )
            * sinh2**2
        )

        b3 = (
            (self.g**2 * cos2**2 * dxi - (3.0 / 2.0) * self.g**2 * dxi)
            * cosh2
            * cos2**2
            * sinh2
            * sqrt(2)
        )

        b4 = cos2**3 * (1.0 / sqrt(2)) * self.g**2 * sinh2

        return (-1.0 / denom) * (b1 + b2 + b3 + b4)

    def evolution_rate(self, state: FieldCollection, t: float = 0.0):
        h, T = state

        f = T - h

        if np.any(np.isnan(h.data)) or np.any(np.isinf(h.data)):
                raise ValueError("NaN/Inf detected in h at start of evolution_rate")
        if np.any(np.isnan(T.data)) or np.any(np.isinf(T.data)):
            raise ValueError("NaN/Inf detected in T at start of evolution_rate")
        
        dx_f = f.gradient(bc=self.bc)[0]    # ∂f₁/∂x

        dx_h = h.gradient(bc=self.bc)[0]    # ∂ξ₁/∂x
        d2x_h = h.laplace(bc=self.bc)       # ∂²ξ₁/∂x²
        dx_T = T.gradient(bc=self.bc)[0]    # ∂T₁/∂x

        # ---- Π⁽¹⁾ field and its gradient ----
        Pi1 = (
            self.G0 * h
            - self.Ca * d2x_h
            - (self.omega**2 * self.b**2) / 2.0 * self.m1 * d2x_h
        )

        dx_Pi1 = Pi1.gradient(bc=self.bc)[0]

        # ---- Π⁽²⁾ ----
        Pi2 = (
            # self.G * xi2
            # - self.Ca * d2x_xi2
            -(self.omega**2 * self.b**2)
            / 2.0
            * ((1.0 - self.m1) * (h * dx_h + 0) + h * dx_h * self.m2)
        )

        dx_Pi2 = Pi2.gradient(bc=self.bc)[0]

        # ---- Π⁽³⁾ = B²Ω²/2 · m₃ ----
        m3 = self._m3(self.omega, h, dx_h)
        Pi3 = (self.omega**2 * self.b**2) / 2.0 * m3

        rhs1 = (
            dx_Pi1 * h**2
            + dx_Pi2 * h
            + 1.0 / 3.0 * Pi3
            + self.Ma / 2.0 * h**2 * (dx_T - dx_h)
            - (self.omega**2 * self.b**2)
            / 2.0
            * (self.R1 * dx_h**3 + self.R2 * dx_h * h * d2x_h)
        )

        h_t = rhs1.gradient(bc=self.bc)[0]

        term1 = (
            -self.Bi / self.Pr * (T - h)
            + (h * dx_Pi1 + self.Ma * h * dx_f) * dx_f
        )

        term2 = (
            3.0 / 4.0 * h**2 * dx_Pi1
            + h / 2.0 * dx_Pi2
            + 1.0 / 3.0 * Pi3
            + self.Ma / 2.0 * h**2 * dx_f
        ).gradient(bc=self.bc)[0]

        T_t = term1 + term2

        if np.any(np.isnan(h_t.data)) or np.any(np.isinf(h_t.data)):
            print(f"WARNING: NaN/Inf in h_t at t={t}")
            return FieldCollection([h_t * 0, T_t * 0])  # Return zero to prevent blow-up
        
        return FieldCollection([h_t, T_t])
