#include <Atmos.hpp>

double atmosphere::_getGeopotentialHeight()
{
	return geopotentialHeight;
}

double atmosphere::_getGravityCurrent()
{
	return gravityCurrent;
}

double atmosphere::_getTemperatureCurrent()
{
	return currentTemperature;
}

double atmosphere::_getPressureCurrent()
{
	return currentPressure;
}

double atmosphere::_getDensityCurrent()
{
	return currentDensity;
}

double atmosphere::_getSoundSpeedCurrent()
{
	return currentSoundSpeed;
}

void atmosphere::processGeopotentialHeight()
{
	geopotentialHeight = RADIUS_EARTH * currentHeight / (RADIUS_EARTH + currentHeight);

}

void atmosphere::processGravityCurrent()
{
	gravityCurrent = GRAVITY_CONST * pow((RADIUS_EARTH / (RADIUS_EARTH + currentHeight)), 2);
}

void atmosphere::processTemperatureCurrent()
{
	currentTemperature = T_star + betta * (geopotentialHeight - H_star);
}

void atmosphere::processPressureCurrent()
{
	if (betta_m != 0) {
		double log_press;
		log_press = log10(p_star) - GRAVITY_CONST *
			log10((Tm_star + betta_m * (geopotentialHeight - H_star)) / Tm_star) / betta_m / GASE_CONST;
		currentPressure = pow(10, log_press);
	}
	else {
		double log_press;
		log_press = log10(p_star) - 0.434294 * GRAVITY_CONST * (geopotentialHeight - H_star)
			/ GASE_CONST / currentTemperature;
		currentPressure = pow(10, log_press);
	}
	
}

void atmosphere::processDensityCurrent()
{
	//currentDensity = currentPressure / MOLAR_MASS / currentTemperature;
	currentDensity = currentPressure / GASE_CONST / currentTemperature;
	
}

void atmosphere::processSoundSpeed()
{
	currentSoundSpeed = 20.046796 * sqrt(currentTemperature);
}

void atmosphere::definingLayerParameters()
{
	if (geopotentialHeight >= -2000 && geopotentialHeight < 0) {
        T_star = 301.15;
		H_star = -2000;
		betta = -0.0065;//???
        p_star = 12.7774 * pow(10, 4);
        betta_m = -0.0065;
        Tm_star = 301.15;

	}
    else if (geopotentialHeight >= 0 && geopotentialHeight < 11000) {
		T_star = 288.15;
		H_star = 0;
		betta = -0.0065;
		p_star = 1.01325 * pow(10, 5);
		betta_m = -0.0065;
        Tm_star = 288.15;
	}
    else if (geopotentialHeight >= 11000 && geopotentialHeight < 20000) {
		T_star = 216.65;
        H_star = 11600;
		betta = 0.0;
        p_star = 2.0588 * pow(10, 4);
		betta_m = 0.0;
		Tm_star = 216.65;
	}
	else if (geopotentialHeight >= 20000 && geopotentialHeight < 32000) {
		T_star = 216.65;
		H_star = 20000;
		betta = 0.0010;
		p_star = 5.47487 * pow(10, 3);
		betta_m = 0.0010;
		Tm_star = 216.65;
	}
	else if (geopotentialHeight >= 32000 && geopotentialHeight < 47000) {
		T_star = 228.65;
		H_star = 32000;
		betta = 0.0028;
		p_star = 8.68014 * pow(10, 2);///////
		betta_m = 0.0028;
		Tm_star = 228.65;
	}
	else if (geopotentialHeight >= 47000 && geopotentialHeight < 51000) {
		T_star = 270.65;
		H_star = 47000;
		betta = 0.0;
		p_star = 1.10906 * pow(10, 2);///
		betta_m = 0.0;
		Tm_star = 270.65;
	}
	else if (geopotentialHeight >= 51000 && geopotentialHeight < 71000) {
		T_star = 270.65;
		H_star = 51000;
		betta = -0.0028;
		p_star = 6.69384 * pow(10, 1);///
		betta_m = -0.0028;
		Tm_star = 270.65;
	}
	else if (geopotentialHeight >= 71000 && geopotentialHeight < 85000) {
		T_star = 214.65;
		H_star = 71000;
		betta = -0.0020;
		p_star = 3.95639 * pow(10, 0);///
		betta_m = -0.0020;
		Tm_star = 214.65;
	}
	else if (geopotentialHeight >= 85000 && geopotentialHeight < 94000) {
		T_star = 186.65;
		H_star = 85000;
		betta = 0.0;
		p_star = 5.31086 * pow(10, -1);///&&&&&&&&&&&&&&&&&&
		betta_m = 0.0;
		Tm_star = 186.65;
	}
	else if (geopotentialHeight >= 94000 && geopotentialHeight < 102450) {

	}
	else if (geopotentialHeight >= 102450 && geopotentialHeight < 117777) {

	}
	else if (geopotentialHeight >= 117777 && geopotentialHeight <= 120000) {

	}
}




