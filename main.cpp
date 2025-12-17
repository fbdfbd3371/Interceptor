#include <iostream>
#include <tuple>
#include <Integrator.hpp>
#include <Rhss.hpp>
#include <fenv.h>
#pragma STDC FENV_ACCESS ON

int main()
{
	feenableexcept(FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW);

	double Vi0{15.0};
	double xt0{-250};

	inputDescr.rhss.push_back(V_k);
	inputDescr.rhss.push_back(Tetta_k);
	inputDescr.rhss.push_back(Psi_k);
	inputDescr.rhss.push_back(omg_x);
	inputDescr.rhss.push_back(omg_y);
	inputDescr.rhss.push_back(omg_z);
	inputDescr.rhss.push_back(pitch);
	inputDescr.rhss.push_back(yaw);
	inputDescr.rhss.push_back(roll);
	inputDescr.rhss.push_back(x_i);
	inputDescr.rhss.push_back(y_i);
	inputDescr.rhss.push_back(z_i);
	inputDescr.rhss.push_back(x_t);
	inputDescr.rhss.push_back(y_t);
	inputDescr.rhss.push_back(z_t);

	inputDescr.T0 = 0;
	inputDescr.Tk = 20;
	inputDescr.step = 0.01;
	inputDescr.init_conds.push_back(Vi0);			  // V
	inputDescr.init_conds.push_back((45) * PI / 180); // THETA
	inputDescr.init_conds.push_back(0);				  // PSI,
	inputDescr.init_conds.push_back(0);				  // omega_x,
	inputDescr.init_conds.push_back(0);				  // omega_y,
	inputDescr.init_conds.push_back(0);				  // omega_z,
	inputDescr.init_conds.push_back((39) * PI / 180); // pitch
	inputDescr.init_conds.push_back(0);				  // yaw
	inputDescr.init_conds.push_back(0);				  // roll
	inputDescr.init_conds.push_back(0);				  // x
	inputDescr.init_conds.push_back(2);				  // y,
	inputDescr.init_conds.push_back(0);				  // z
	inputDescr.init_conds.push_back(xt0);			  // x_c
	inputDescr.init_conds.push_back(250);			  // y_c
	inputDescr.init_conds.push_back(0);				  // z_c

	inputDescr.prm_names.push_back(std::pair("V, m/s", true));
	inputDescr.prm_names.push_back(std::pair("THETA, rad", true));
	inputDescr.prm_names.push_back(std::pair("PSI, rad", false));
	inputDescr.prm_names.push_back(std::pair("omega_x, rad/s", false));
	inputDescr.prm_names.push_back(std::pair("omega_y, rad/s", false));
	inputDescr.prm_names.push_back(std::pair("omega_z, rad/s", false));
	inputDescr.prm_names.push_back(std::pair("pitch, rad", false));
	inputDescr.prm_names.push_back(std::pair("yaw, rad", false));
	inputDescr.prm_names.push_back(std::pair("roll, rad", false));
	inputDescr.prm_names.push_back(std::pair("x_i, m", true));
	inputDescr.prm_names.push_back(std::pair("y_i, m", true));
	inputDescr.prm_names.push_back(std::pair("z_i, m", false));

	inputDescr.prm_names.push_back(std::pair("x_t, m", true));
	inputDescr.prm_names.push_back(std::pair("y_t, m", true));
	inputDescr.prm_names.push_back(std::pair("z_t, m", false));

	inputDescr.funcs.emplace_back(cur_mass, "m, kg", false);
	inputDescr.funcs.emplace_back(P, "P, N", false);
	inputDescr.funcs.emplace_back(phi_t, "phi_t, rad", true);
	inputDescr.funcs.emplace_back(phiDeriv_t, "phiDeriv_t, rad/s", false);
	inputDescr.funcs.emplace_back(phiDerivDeg, "phiDerivDeg, deg/s", true);
	inputDescr.funcs.emplace_back(THETADeg, "THETADeg, deg", true);
	inputDescr.funcs.emplace_back(r, "r, m", true);
	inputDescr.funcs.emplace_back(Vc, "Vc, m/s", true);

	inputDescr.stopCriteria = stopCriteria;

	outFile.open("output.txt");
	outFile << "propoN, [-]\t" << inputDescr.propoN << std::endl;
	outFile << "Vi0, [m/s]\t" << Vi0 << std::endl;
	outFile << "Vt, [m/s]\t" << inputDescr.Vt << std::endl;
	outFile << "m, [kg]\t" << inputDescr.m << std::endl;
	outFile << "Jz, [kg/m]\t" << inputDescr.Jz << std::endl;
	outFile << "Sm, [m^2]\t" << inputDescr.Sm << std::endl;
	outFile << "ld_lc, [m]\t" << inputDescr.ld_lc << std::endl;
	outFile << "Vc_min, [m/s]\t" << inputDescr.Vc_min << std::endl;
	outFile << "Kp, [-]\t" << inputDescr.Kp << std::endl;
	outFile << "xt0, [m]\t" << xt0 << std::endl;

	std::cout << "Processing starts!" << std::endl;

	solve_system(inputDescr);

	std::cout << "Processing done!" << std::endl;
	return 0;
}