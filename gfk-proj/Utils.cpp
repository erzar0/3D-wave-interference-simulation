#include "Utils.h"
    
double utils::mapInterval(double start1, double stop1, double start2, double stop2, double value)
{
    return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
}

sf::Color utils::HSVtoRGB(float H, float S, float V)
{
	H = H * 360;
	float C = S * V; // Chroma
	float HPrime = std::fmod(H / 60, 6.f); // H'
	float X = C * (1 - std::fabs(std::fmod(HPrime, 2.f) - 1));
	float M = V - C;

	float R = 0.f;
	float G = 0.f;
	float B = 0.f;

	int val = static_cast<int>(HPrime);
	
	if (val == 0) {
		R = C; G = X;
	}     
	else if(val == 1)
	{
		R = X; G = C;
	}
	else if (val == 2)
	{
		G = C; B = X;
	}
	else if (val == 3)
	{
		G = X; B = C;
	}
	else if (val == 4)
	{
		R = X; B = C;
	}
	else
	{
		R = C;B = X; 
	}

	R += M;
	G += M;
	B += M;

	return sf::Color(static_cast<sf::Uint8>(std::round(R * 255)),
		 static_cast<sf::Uint8>(std::round(G * 255)),
		 static_cast<sf::Uint8>(std::round(B * 255)));

}