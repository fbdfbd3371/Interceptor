#include <Integrator.hpp>

//#define OUTPUT_DEGREES
#define OUTPUT_RADIANS

namespace uIntegr {
	map<string, vector<double>> solve_system(inputDescr_t prm) 
	{
		map<string, vector<double>> allParams;
		for (int i = 0; i < prm.funcs.size(); i++)
		{
			allParams.emplace(prm.prm_names[i], NULL);
		}
		allParams.emplace(prm.integr_param_name, NULL);

		vector<double> state_sys(prm.funcs.size());
		state_sys = prm.init_conds;

		vector<double> cur_params(prm.funcs.size());
		cur_params = prm.init_conds;

		
		for (double t = prm.a; t < prm.b; t += prm.step) 
		{
			vector<double> k1(prm.funcs.size());
			vector<double> k2(prm.funcs.size());
			vector<double> k3(prm.funcs.size());
			vector<double> k4(prm.funcs.size());

			

			
			// ------------k1-------------
			for (int i = 0; i < prm.funcs.size(); i++) 
			{
				k1[i] = prm.funcs[i](state_sys,t);
			}

			// ------------k2-------------
			state_sys = cur_params;

			for (int i = 0; i < prm.funcs.size(); i++)
			{
				state_sys[i] += 0.5 * k1[i] * prm.step;
			}

			for (int i = 0; i < prm.funcs.size(); i++)
			{
				k2[i] = prm.funcs[i](state_sys, t + prm.step/2);
			}

			
			// ------------k3-------------
			state_sys = cur_params;

			for (int i = 0; i < prm.funcs.size(); i++)
			{
				state_sys[i] += 0.5 * k2[i] * prm.step;
			}

			for (int i = 0; i < prm.funcs.size(); i++)
			{
				k3[i] = prm.funcs[i](state_sys, t + prm.step / 2);
			}

			

			// ------------k4-------------
			state_sys = cur_params;

			for (int i = 0; i < prm.funcs.size(); i++)
			{
				state_sys[i] += k3[i] * prm.step;
			}

			for (int i = 0; i < prm.funcs.size(); i++)
			{
				k4[i] = prm.funcs[i](state_sys, t + prm.step);
			}



			for (int i = 0; i < prm.funcs.size(); i++)
			{
				cur_params[i] += (prm.step / 6) * (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]);
			}

			for (int i = 0; i < prm.funcs.size(); i++)
			{
#ifdef OUTPUT_DEGREES
				allParams[prm.prm_names[i]].push_back(cur_params[i] *180 / 3.1415926535);
#endif

#ifdef OUTPUT_RADIANS
				allParams[prm.prm_names[i]].push_back(cur_params[i]);// *180 / 3.1415926535);
#endif


				
			}
			
			allParams[prm.integr_param_name].push_back(t);
		}


		
		return allParams;
	}
}
