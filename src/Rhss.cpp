#include <Rhss.hpp>


double linear_interp(std::vector<double> X, std::vector<double> Y, double x)
{
	double res;

	int i0 = 0;
	// в цикле ищется интервал, в котором будем интерполировать
	for (int i = 0; i < X.size(); i++) 
	{
		if (x < X[i]) {
			i0 = i;
			break;
		}
	}
	double x0 = X[i0 - 1];
	double y0 = Y[i0 - 1];
	double x1 = X[i0];
	double y1 = Y[i0];

	res = (y1 - y0) * (x - x0) / (x1 - x0) + y0;

	return res;
}

namespace DP6sem_DZV2_funcs
{
#define sId(x) (int)sId_t::x	
	using namespace std;

	double m0 = 1160;
	double Jx = 0;
	double Jy = 0;
	double Jz = 120;
	double ld_lc = 0.21;
	double Sa = 0.15;
	double Sm = 0.2289;
	double mass_cons = 81;	// mass consumption
	double p0N = 101325;

	vector<double> vec_X_C_xa = {
		0.01, 0.55, 0.8, 0.9, 1.0, 1.06, 1.1, 1.2, 1.3, 1.4, 2.0, 2.6, 3.4, 6.0, 10.0
	};

	vector<double> vec_Y_C_xa = {
			0.30, 0.30, 0.55, 0.70, 0.84, 0.86, 0.87, 0.83, 0.80, 0.79, 0.65, 0.55, 0.50, 0.45, 0.40
	};

	vector<double> vec_X_C_ya = {
			0.01, 0.55, 0.8, 0.9, 1.0, 1.06, 1.1, 1.2, 1.3, 1.4, 2.0, 2.6, 3.4, 6.0, 10.0
	};

	vector<double> vec_Y_C_ya = {
			0.25, 0.25, 0.25, 0.20, 0.30, 0.31, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25
	};

	//--------Вспомогательные функции

	// Тяга - в связанной СК
	static double cur_mass(vector<double> st, double t)
	{
		double res;
		res = m0 - mass_cons * t;
		return res;
	}

	// Тяга - в связанной СК
	static double P(vector<double> st, double t)
	{
		double res;
		atmosphere atm(st[sId(y_g)]);
		res = 2100 * mass_cons + Sa * (p0N - atm._getPressureCurrent());
		return res;
	}

	// Скоростной напор
	static double q(vector<double> st, double t)
	{
		double res;
		atmosphere atm(st[sId(y_g)]);
		res = atm._getDensityCurrent() * pow(st[sId(V_k)], 2) / 2;
		return res;
	}

	// Число Маха
	static double M(vector<double> st, double t)
	{
		double res;
		atmosphere atm(st[sId(y_g)]);
		res = st[sId(V_k)] / atm._getSoundSpeedCurrent();
		return res;
	}

	// C_xk - коэффициент лобового сопротивления
	static double C_xk(vector<double> st, double t)
	{
		double res;
		atmosphere atm(st[sId(y_g)]);
		res = linear_interp(vec_X_C_xa, vec_Y_C_xa, M(st, t));
		return res;
	}

	// alpha - угол атаки
	static double alpha(vector<double> st, double t)
	{
		double res;
		// Должно быть так: 
		res = st[sId(pitch)] - st[sId(Tetta_k)];//?????
		return res;
	}

	// C_yk - коэффициент лобового сопротивления. Зависит от альфа (домножать на альфа)
	static double C_yk(vector<double> st, double t)
	{
		double res;
		atmosphere atm(st[sId(y_g)]);
		res = linear_interp(vec_X_C_ya, vec_Y_C_ya, M(st, t))*alpha(st,t);
		return res;
	}

	// betta - угол скольжения
	static double betta(vector<double> st, double t)
	{
		double res;
		// Должно быть так: 
		res = st[sId(Psi_k)] - st[sId(yaw)];//??????
		return res;
	}

	// Проекция суммы всех аэродинамических сил на траекторную ось Ox_k
	static double resR_xk(vector<double> st, double t)
	{
		double res;
		res = -C_xk(st, t) * q(st, t) * Sm;
		return res;
	}

	// Проекция суммы всех аэродинамических сил на траекторную ось Oy_k
	static double resR_yk(vector<double> st, double t)
	{
		double res;
		res = C_yk(st, t) * q(st, t) * Sm;
		return res;
	}

	// Проекция суммы всех аэродинамических сил на траекторную ось Oz_k
	static double resR_zk(vector<double> st, double t)
	{
		double res;
		// Должно быть так: 
		res = 0;  // = 0, так как рассматриваем задачу 5 семестра
		return res;
	}

	// Проекция результирующей силы от рулей на траекторную ось Ox_k
	static double resFr_xk(vector<double> st, double t)
	{
		double res;
		// Должно быть так: 
		res = 0;  // = 0, так как рассматриваем задачу 5 семестра
		return res;
	}

	// Проекция результирующей силы от рулей на траекторную ось Oy_k
	static double resFr_yk(vector<double> st, double t)
	{
		double res;
		// Должно быть так: 
		res = 0;  // = 0, так как рассматриваем задачу 5 семестра
		return res;
	}

	// Проекция результирующей силы от рулей на траекторную ось Oz_k
	static double resFr_zk(vector<double> st, double t)
	{
		double res;
		// Должно быть так: 
		res = 0;  // = 0, так как рассматриваем задачу 5 семестра
		return res;
	}

	// Проекция результирующей силы тяги на траекторную ось Ox_k
	static double resP_xk(vector<double> st, double t)
	{
		double res;
		res = P(st, t) * cos(alpha(st, t)) * cos(betta(st, t));
		return res;
	}

	// Проекция результирующей силы тяги на траекторную ось Oy_k
	static double resP_yk(vector<double> st, double t)
	{
		double res;
		double gamma_c = 0;
		res = P(st, t) * (sin(alpha(st, t)) * cos(gamma_c) 
			+ sin(gamma_c) * cos(alpha(st, t)) * sin(betta(st, t)));
		return res;
	}

	// Проекция результирующей силы тяги на траекторную ось Oz_k
	static double resP_zk(vector<double> st, double t)
	{
		double res;
		double gamma_c = 0;
		res = P(st, t) * (sin(gamma_c) * sin(alpha(st, t)) 
			- cos(gamma_c) * cos(alpha(st, t)) * sin(betta(st, t)));
		return res;
	}

	// Проекция суммы всех сил на траекторную ось Ox_k
	static double resF_xk(vector<double> st, double t)
	{
		double res;
		// Должно быть так: 
		res = resP_xk(st, t) + resFr_xk(st, t) + resR_xk(st, t);
		return res;
	}

	// Проекция суммы всех сил на траекторную ось Oy_k
	static double resF_yk(vector<double> st, double t)
	{
		double res;
		// Должно быть так: 
		res = resP_yk(st, t) + resFr_yk(st, t) + resR_yk(st, t);
		return res;
	}

	// Проекция суммы всех сил на траекторную ось Oz_k
	static double resF_zk(vector<double> st, double t)
	{
		double res;
		// Должно быть так: 
		res = resP_zk(st, t) + resFr_zk(st, t) + resR_zk(st, t);
		return res;
	}


	// Проекция суммы всех ускорений на траекторную ось Ox_k
	static double res_g_xk(vector<double> st, double t)
	{
		double res;
		atmosphere atm(st[sId(y_g)]);
		res = -atm._getGravityCurrent() * sin(st[sId(Tetta_k)]);
		return res;
	}

	// Проекция суммы всех ускорений на траекторную ось Oy_k
	static double res_g_yk(vector<double> st, double t)
	{
		double res;
		atmosphere atm(st[sId(y_g)]);
		res = -atm._getGravityCurrent() * cos(st[sId(Tetta_k)]);
		return res;
	}

	// Проекция суммы всех ускорений на траекторную ось Oz_k
	static double res_g_zk(vector<double> st, double t)
	{
		double res = 0; // = 0, так как рассматриваем задачу 5 семестра

		return res;
	}

	// Результирующий статический момент в проекции на связанную ось Ox
	static double resMst_x(vector<double> st, double t)
	{
		double res;
		res = 0; // из условий дз 5 сем
		return res;
	}

	// Результирующий статический момент в проекции на связанную ось Oy
	static double resMst_y(vector<double> st, double t)
	{
		double res;
		res = 0; // из условий дз 5 сем
		return res;
	}

	// Результирующий статический момент в проекции на связанную ось Oz
	static double resMst_z(vector<double> st, double t)
	{
		double res;
		res = (-1)*(C_xk(st, t) + C_yk(st, t))* Sm* q(st, t)* ld_lc;
		return res;
	}

	// Результирующий динамический момент в проекции на связанную ось Ox
	static double resMd_x(vector<double> st, double t)
	{
		double res;
		res = 0; // из условий дз 5 сем
		return res;
	}

	// Результирующий динамический момент в проекции на связанную ось Oy
	static double resMd_y(vector<double> st, double t)
	{
		double res;
		res = 0; // из условий дз 5 сем
		return res;
	}

	// Результирующий динамический момент в проекции на связанную ось Oz
	static double resMd_z(vector<double> st, double t)
	{
		double res;
		res = 0; // из условий дз 5 сем
		return res;
	}

	// Результирующий момент от рулей в проекции на связанную ось Ox
	static double resMr_x(vector<double> st, double t)
	{
		double res;
		res = 0; // из условий дз 5 сем
		return res;
	}

	// Результирующий момент от рулей в проекции на связанную ось Oy
	static double resMr_y(vector<double> st, double t)
	{
		double res;
		res = 0; // из условий дз 5 сем
		return res;
	}

	// Результирующий момент от рулей в проекции на связанную ось Oz
	static double resMr_z(vector<double> st, double t)
	{
		double res;
		res = 0; // из условий дз 5 сем
		return res;
	}

	// Результирующий момент в проекции на связанную ось Ox
	static double resM_x(vector<double> st, double t)
	{
		double res;
		res = resMst_x(st, t) + resMd_x(st, t) + resMr_x(st, t);
		return res;
	}

	// Результирующий момент в проекции на связанную ось Oy
	static double resM_y(vector<double> st, double t)
	{
		double res;
		res = resMst_y(st, t) + resMd_y(st, t) + resMr_y(st, t);
		return res;
	}

	// Результирующий момент в проекции на связанную ось Oz
	static double resM_z(vector<double> st, double t)
	{
		double res;
		res = resMst_z(st, t) + resMd_z(st, t) + resMr_z(st,t);
		return res;
	}


	//--------ПРАВЫЕ ЧАСТИ ДУ-------

	double V_k(vector<double> st, double t)
	{
		double res;
		// Должно быть так: resF_xk()/st[sId(сmass)]+res_g_xk
		res = resF_xk(st, t) / cur_mass(st, t) + res_g_xk(st, t);
		return res;
	}

	double Tetta_k(vector<double> st, double t)
	{
		double res;
		// Должно быть так: 
		res = resF_yk(st, t) / cur_mass(st, t) / st[sId(V_k)] + res_g_yk(st, t) / st[sId(V_k)];
		return res;
 	}

	double Psi_k(vector<double> st, double t)
	{
		double res;
		// Должно быть так: 
		res = (-1) * resF_zk(st, t)
			/ (cur_mass(st,t) * st[sId(V_k)] * cos(st[sId(Tetta_k)]));
		return res;
	}

	double omg_x(vector<double> st, double t)
	{
		double res;
		// Должно быть так:
		res = 0;// из условий дз 5 сем
		return res;
	}

	double omg_y(vector<double> st, double t)
	{
		double res;
		// Должно быть так: 
		res = 0;// из условий дз 5 сем
		return res;
	}

	double omg_z(vector<double> st, double t)
	{
		double res;
		// Должно быть так: 
		res = resM_z(st, t) * alpha(st,t) / Jz;
		return res;
	}

	double pitch(vector<double> st, double t)
	{
		double res;
		double gamma = 0;
		// Должно быть так:
		res = st[sId(omg_y)] * sin(gamma) + st[sId(omg_z)] * cos(gamma);
		return res;
	}

	double yaw(vector<double> st, double t)
	{
		double res;
		double gamma = 0;
		// Должно быть так: 
		res = (st[sId(omg_y)] * cos(gamma) - st[sId(omg_z)] * sin(gamma)) / cos(st[sId(pitch)]);
		return res;
	}

	double roll(vector<double> st, double t)
	{
		double res;
		double gamma = 0;
		// Должно быть так: 
		res = st[sId(omg_x)] - tan(st[sId(pitch)]) 
			* (st[sId(omg_y)] * cos(gamma) - st[sId(omg_z)] * sin(gamma));
		return res;
	}

	double x_g(vector<double> st, double t)
	{
		double res;
		// Должно быть так: 
		res = st[sId(V_k)] * cos(st[sId(Tetta_k)]) * cos(st[sId(Psi_k)]);
		return res;
	}

	double y_g(vector<double> st, double t)
	{
		double res;
		// Должно быть так: 
		res = st[sId(V_k)] * sin(st[sId(Tetta_k)]);
		return res;
	}

	double z_g(vector<double> st, double t)
	{
		double res;
		// Должно быть так: 
		res = -st[sId(V_k)] * cos(st[sId(Tetta_k)]) * sin(st[sId(Psi_k)]);
		return res;
	}
}