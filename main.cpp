#include <iostream>
#include <tuple>
#include <Integrator.hpp>
#include <Rhss.hpp>
#include <fenv.h>
#pragma STDC FENV_ACCESS ON

int main()
{
	// feenableexcept(FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW);

	double Vi0{10.0};
	double xt0{-250};
	inputDescr.propoN = 20.0;

	inputDescr.rhss.push_back(V_k);
	inputDescr.rhss.push_back(Tetta_k);
	inputDescr.rhss.push_back(Psi_k);
	inputDescr.rhss.push_back(omg_x);
	inputDescr.rhss.push_back(omg_y);
	inputDescr.rhss.push_back(omg_z);
	inputDescr.rhss.push_back(yaw);
	inputDescr.rhss.push_back(roll);
	inputDescr.rhss.push_back(x_i);
	inputDescr.rhss.push_back(y_i);
	inputDescr.rhss.push_back(z_i);
	inputDescr.rhss.push_back(x_t);
	inputDescr.rhss.push_back(y_t);
	inputDescr.rhss.push_back(z_t);

	inputDescr.T0 = 0;
	inputDescr.Tk = 40;
	inputDescr.step = 0.01;
	inputDescr.init_conds.push_back(Vi0);			  // V
	inputDescr.init_conds.push_back((45) * PI / 180); // THETA
	inputDescr.init_conds.push_back(0);				  // PSI,
	inputDescr.init_conds.push_back(0);				  // omega_x,
	inputDescr.init_conds.push_back(0);				  // omega_y,
	inputDescr.init_conds.push_back(0);				  // omega_z,
	inputDescr.init_conds.push_back(0);				  // yaw
	inputDescr.init_conds.push_back(0);				  // roll
	inputDescr.init_conds.push_back(0);				  // x_i
	inputDescr.init_conds.push_back(2);				  // y_i
	inputDescr.init_conds.push_back(0);				  // z_i
	inputDescr.init_conds.push_back(xt0);			  // x_t
	inputDescr.init_conds.push_back(250);			  // y_t
	inputDescr.init_conds.push_back(0);				  // z_t

	inputDescr.prm_names.push_back(std::pair("V, m/s", false));
	inputDescr.prm_names.push_back(std::pair("THETA, rad", false));
	inputDescr.prm_names.push_back(std::pair("PSI, rad", false));
	inputDescr.prm_names.push_back(std::pair("omega_x, rad/s", false));
	inputDescr.prm_names.push_back(std::pair("omega_y, rad/s", false));
	inputDescr.prm_names.push_back(std::pair("omega_z, rad/s", false));
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
	inputDescr.funcs.emplace_back(phi_t, "phi_t, rad", false);
	inputDescr.funcs.emplace_back(phiDeg, "phi, deg", true);
	inputDescr.funcs.emplace_back(THETADeg, "THETADeg, deg", true);
	inputDescr.funcs.emplace_back(r, "r, m", true);
	inputDescr.funcs.emplace_back(Vc, "Vc, m/s", true);
	inputDescr.funcs.emplace_back(ac, "ac, m/s^2", true);
	inputDescr.funcs.emplace_back(an, "a_n, m/s^2", true);
	inputDescr.funcs.emplace_back(Vi, "Vi, m/s", true);
	inputDescr.funcs.emplace_back(Viy, "Viy, m/s", true);
	inputDescr.funcs.emplace_back(pitchDeg, "pitch,deg", true);
	inputDescr.funcs.emplace_back(THETADerivDeg, "THETADerivDeg,deg", true);
	inputDescr.funcs.emplace_back(phiDerivNewDeg, "phiDerivNewDeg", true);

	inputDescr.stopCriteriaVector.clear();
	inputDescr.stopCriteriaVector.emplace_back(missStopCriteria);

	inputDescr.successCriteriaVector.clear();
	inputDescr.successCriteriaVector.emplace_back(altStopCriteria);

	// outFile.open("output.txt");
	// outFile << "propoN, [-]\t" << inputDescr.propoN << std::endl;
	// outFile << "Vi0, [m/s]\t" << Vi0 << std::endl;
	// outFile << "Vt, [m/s]\t" << inputDescr.Vt << std::endl;
	// outFile << "m, [kg]\t" << inputDescr.m << std::endl;
	// outFile << "Jz, [kg/m]\t" << inputDescr.Jz << std::endl;
	// outFile << "Sm, [m^2]\t" << inputDescr.Sm << std::endl;
	// outFile << "ld_lc, [m]\t" << inputDescr.ld_lc << std::endl;
	// outFile << "Vc_min, [m/s]\t" << inputDescr.Vc_min << std::endl;
	// outFile << "Kp, [-]\t" << inputDescr.Kp << std::endl;
	// outFile << "xt0, [m]\t" << xt0 << std::endl;

	std::cout << "Processing starts!" << std::endl;

	// solve_system(inputDescr);

	double phiStep = 10.0 * M_PI / 180.0;
	double startPhi = 10.0 * M_PI / 180.0;
	double endPhi = 170.0 * M_PI / 180.0;

	/// Максимальная дальность обнаружения.
	double rMax = 200.0;
	/// Горизонтальная скорость цели.
	inputDescr.Vtx = -40.0;

	std::ofstream zoneFile;
	zoneFile.open("zone.txt");

	for (double curPhi = startPhi; curPhi <= endPhi; curPhi += phiStep)
	{
		std::cerr << "curPhi: " << curPhi * 180.0 / M_PI << '\t';
		inputDescr.init_conds.clear();
		inputDescr.init_conds.push_back(Vi0);				 // V
		inputDescr.init_conds.push_back(curPhi);			 // THETA
		inputDescr.init_conds.push_back(0.0);				 // PSI,
		inputDescr.init_conds.push_back(0.0);				 // omega_x,
		inputDescr.init_conds.push_back(0.0);				 // omega_y,
		inputDescr.init_conds.push_back(0.0);				 // omega_z,
		inputDescr.init_conds.push_back(0.0);				 // yaw
		inputDescr.init_conds.push_back(0.0);				 // roll
		inputDescr.init_conds.push_back(0.0);				 // x_i
		inputDescr.init_conds.push_back(0.0);				 // y_i
		inputDescr.init_conds.push_back(0.0);				 // z_i
		inputDescr.init_conds.push_back(rMax * cos(curPhi)); // x_t
		inputDescr.init_conds.push_back(rMax * sin(curPhi)); // y_t
		inputDescr.init_conds.push_back(0.0);				 // z_t

		inputDescr.min_r = 1e+5;

		if (solve_system(inputDescr))
		{
			std::cerr << "Success!" << std::endl;
			zoneFile << curPhi << '\t' << true << std::endl;
		}
		else
		{
			std::cerr << "Unsuccess...\tr: " << inputDescr.min_r << std::endl;
			zoneFile << curPhi << '\t' << false << std::endl;
		}
	}

	std::cout << "Processing done!" << std::endl;
	zoneFile.close();
	return 0;
}