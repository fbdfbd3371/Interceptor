#include <iostream>
#include <Integrator.hpp>
#include <Rhss.hpp>

int main()
{
	uIntegr::inputDescr_t inputDescr;

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
	inputDescr.Tk = 15;
	inputDescr.step = 0.1;
	inputDescr.init_conds.push_back(1);			  // V
	inputDescr.init_conds.push_back((39) * PI / 180); // THETA
	inputDescr.init_conds.push_back(0);				  // PSI,
	inputDescr.init_conds.push_back(0);				  // omega_x,
	inputDescr.init_conds.push_back(0);				  // omega_y,
	inputDescr.init_conds.push_back(0);				  // omega_z,
	inputDescr.init_conds.push_back((39) * PI / 180); // pitch
	inputDescr.init_conds.push_back(0);				  // yaw
	inputDescr.init_conds.push_back(0);				  // roll
	inputDescr.init_conds.push_back(0);				  // x
	inputDescr.init_conds.push_back(1500);			  // y,
	inputDescr.init_conds.push_back(0);				  // z
	inputDescr.init_conds.push_back(-100); // x_c
	inputDescr.init_conds.push_back(100);  // y_c
	inputDescr.init_conds.push_back(0);	   // z_c

	inputDescr.prm_names.push_back("V, m/s");
	inputDescr.prm_names.push_back("THETA, rad");
	inputDescr.prm_names.push_back("PSI, rad");
	inputDescr.prm_names.push_back("omega_x, rad/s");
	inputDescr.prm_names.push_back("omega_y, rad/s");
	inputDescr.prm_names.push_back("omega_z, rad/s");
	inputDescr.prm_names.push_back("pitch, rad");
	inputDescr.prm_names.push_back("yaw, rad");
	inputDescr.prm_names.push_back("roll, rad");
	inputDescr.prm_names.push_back("x_i, m");
	inputDescr.prm_names.push_back("y_i, m");
	inputDescr.prm_names.push_back("z_i, m");

	inputDescr.prm_names.push_back("x_t, m");
	inputDescr.prm_names.push_back("y_t, m");
	inputDescr.prm_names.push_back("z_t, m");

	inputDescr.funcs.emplace_back(std::pair(cur_mass, "m, kg"));
	inputDescr.funcs.emplace_back(std::pair(P, "P, N"));
	inputDescr.funcs.emplace_back(std::pair(phi_t, "phi_t, rad"));

	std::cout << "Processing starts!" << std::endl;

	uIntegr::solve_system(inputDescr);

	std::cout << "Processing done!" << std::endl;
	return 0;
}