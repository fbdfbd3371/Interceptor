#include <iostream>
#include <Integrator.hpp>
#include <Rhss.hpp>

int main()
{
	uIntegr::inputDescr_t inputDescr;

	inputDescr.rhss.push_back(DP6sem_DZV2_funcs::V_k);
	inputDescr.rhss.push_back(DP6sem_DZV2_funcs::Tetta_k);
	inputDescr.rhss.push_back(DP6sem_DZV2_funcs::Psi_k);
	inputDescr.rhss.push_back(DP6sem_DZV2_funcs::omg_x);
	inputDescr.rhss.push_back(DP6sem_DZV2_funcs::omg_y);
	inputDescr.rhss.push_back(DP6sem_DZV2_funcs::omg_z);
	inputDescr.rhss.push_back(DP6sem_DZV2_funcs::pitch);
	inputDescr.rhss.push_back(DP6sem_DZV2_funcs::yaw);
	inputDescr.rhss.push_back(DP6sem_DZV2_funcs::roll);
	inputDescr.rhss.push_back(DP6sem_DZV2_funcs::x_g);
	inputDescr.rhss.push_back(DP6sem_DZV2_funcs::y_g);
	inputDescr.rhss.push_back(DP6sem_DZV2_funcs::z_g);
	inputDescr.rhss.push_back(DP6sem_DZV2_funcs::x_c);
	inputDescr.rhss.push_back(DP6sem_DZV2_funcs::y_c);
	inputDescr.rhss.push_back(DP6sem_DZV2_funcs::z_c);

	inputDescr.T0 = 0;
	inputDescr.Tk = 4.73;
	inputDescr.step = 0.1;
	inputDescr.init_conds.push_back(54);			  // V
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
	inputDescr.prm_names.push_back("x, m");
	inputDescr.prm_names.push_back("y, m");
	inputDescr.prm_names.push_back("z, m");

	inputDescr.prm_names.push_back("x_c, m");
	inputDescr.prm_names.push_back("y_c, m");
	inputDescr.prm_names.push_back("z_c, m");

	inputDescr.funcs.emplace_back(std::pair(DP6sem_DZV2_funcs::cur_mass, "m, kg"));
	inputDescr.funcs.emplace_back(std::pair(DP6sem_DZV2_funcs::P, "P, N"));

	std::cout << "Processing starts!" << std::endl;

	uIntegr::solve_system(inputDescr);

	std::cout << "Processing done!" << std::endl;
	return 0;
}