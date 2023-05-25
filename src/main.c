#include <stdio.h>
#include <math.h>
#include <uncertain.h>


/***********************************************************************
 P U B L I C  D E F I N I T I O N S
 ***********************************************************************/

#define GASCONSTANT            287       // Gas constant for air in (N m)/(kg K)
#define SGRAVITY               0.85
#define WATERR                 9790
#define MANOMETER_WATER_HEIGHT 0.020 
#define AREA_AIRFOIL           0.1

/***********************************************************************
 P U B L I C  F U N C T I O N S
 ***********************************************************************/

/***********************************************************************
	Function to find the air density (kg/m^3)
	airDensity = (Pressure in N/m^2)) / ((Gas constant for air in (N m)/(kg K)) * (Tempreture in K)) 

	Param[in] : Pressure in Pa
	Param[in] : Tempreture in Celcius
	Return    : Air density
 ************************************************************************/
double airDensity(double pressure, double temp)
{
	double ans = 0;
    ans = (pressure / (GASCONSTANT * (temp + 273)));
    return ans;
}

/***********************************************************************
	Function to find the air Velocity (m/s)
	airVelocity (m/s) = Sqroot (2 * pressure difference in (N/m^2) / Air density in (kg/m^3))

	Param[in] : Air density
	Param[in] : Manometer water height
	Return    : Air velocity
 ************************************************************************/
double airVelocity(double airDensity, double height)
{
	double airVelocity = 0;

	/* 
	    Pressure difference (N/m^2) = specific gravity * Specific r for water in (N/m^3) * height of fluid in manometer in (m)
	*/
	
    double pDiff = SGRAVITY * WATERR * height;


    airVelocity = sqrt((2 * pDiff)/airDensity);
    return airVelocity;
}

/***********************************************************************
	Function to find lift force for airfoil (N)
	lift Force (N) = 0.5 * airDensity in (kg/m^3) * area in (m^2) * (airVelocity in (m/s))^2

	Param[in] : Air velocity
	Param[in] : Air density
	Return    : Lift force 
 ************************************************************************/
double liftForce(double airVelocity, double airDensity)
{
    double lForce = 0;
    lForce = 0.5 * airDensity * AREA_AIRFOIL * pow(airVelocity, 2);
    return lForce;
}

/***********************************************************************
	M A I N  F U N C T I O N
 ************************************************************************/
int main(int argc, char *	argv[])
{
    double pre = 98000;
    double temp =  25;

    double airVel = 0;
    double airDen = 0;
    double lForce = 0; 
    double unPressure = 0;
    double unTemp = 0;

    airDen = airDensity(pre, temp);

    airVel = airVelocity(airDen, 0.020);

    lForce = liftForce(airVel, airDen);
    printf("Lift Force is (F)\t\t= %.1E N\n", lForce);

    // Uncertainity in pressure as per uniform distribution as minimum allowed pressure is 75 and maximum allowed pressure is 101
    unPressure = libUncertainDoubleUniformDist(75, 101);
    printf("UnCertainity Pressure = %lf\n", unPressure);

    // Uncertainity in tempreture as per uniform distribution as minimum allowed tempreture is -56 and maximum allowed tempreture is 53
    unTemp = libUncertainDoubleUniformDist(-56 , 53);
    printf("Uncertainity Tempreture = %lf\n", unTemp);

    return 0;

}

