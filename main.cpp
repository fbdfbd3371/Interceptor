#include <iostream>
#include <Integrator.hpp>
#include <Rhss.hpp>

int main()
{

	std::cout << "Hello world\n";
	uIntegr::inputDescr_t inputDescr;

	inputDescr.funcs.push_back(DP6sem_DZV2_funcs::V_k);
	inputDescr.funcs.push_back(DP6sem_DZV2_funcs::Tetta_k);
	inputDescr.funcs.push_back(DP6sem_DZV2_funcs::Psi_k);
	inputDescr.funcs.push_back(DP6sem_DZV2_funcs::omg_x);
	inputDescr.funcs.push_back(DP6sem_DZV2_funcs::omg_y);
	inputDescr.funcs.push_back(DP6sem_DZV2_funcs::omg_z);
	inputDescr.funcs.push_back(DP6sem_DZV2_funcs::pitch);
	inputDescr.funcs.push_back(DP6sem_DZV2_funcs::yaw);
	inputDescr.funcs.push_back(DP6sem_DZV2_funcs::roll);
	inputDescr.funcs.push_back(DP6sem_DZV2_funcs::x_g);
	inputDescr.funcs.push_back(DP6sem_DZV2_funcs::y_g);
	inputDescr.funcs.push_back(DP6sem_DZV2_funcs::z_g);

	inputDescr.a = 0;
	inputDescr.b = 4.73;
	inputDescr.step = 0.1;
	inputDescr.init_conds.push_back(54);			  // V_k
	inputDescr.init_conds.push_back((39) * PI / 180); // Tetta_k
	inputDescr.init_conds.push_back(0);				  // Psi_k,
	inputDescr.init_conds.push_back(0);				  // omg_x,
	inputDescr.init_conds.push_back(0);				  // omg_y,
	inputDescr.init_conds.push_back(0);				  // omg_z,
	inputDescr.init_conds.push_back((39) * PI / 180); // pitch,
	inputDescr.init_conds.push_back(0);				  // yaw,
	inputDescr.init_conds.push_back(0);				  // roll,
	inputDescr.init_conds.push_back(0);				  // x_g,
	inputDescr.init_conds.push_back(1500);			  // y_g,
	inputDescr.init_conds.push_back(0);				  // z_g,

	inputDescr.prm_names.push_back("V_k, meters/sec");
	inputDescr.prm_names.push_back("Tetta, degrees");
	inputDescr.prm_names.push_back("Psi_k");
	inputDescr.prm_names.push_back("omg_x");
	inputDescr.prm_names.push_back("omg_y");
	inputDescr.prm_names.push_back("omg_z, degrees/sec");
	inputDescr.prm_names.push_back("pitch, degrees");
	inputDescr.prm_names.push_back("yaw");
	inputDescr.prm_names.push_back("roll");
	inputDescr.prm_names.push_back("x_g, meters");
	inputDescr.prm_names.push_back("y_g, meters");
	inputDescr.prm_names.push_back("z_g, meters");

	uIntegr::solve_system(inputDescr);

	system("pause");
	return 0;
}