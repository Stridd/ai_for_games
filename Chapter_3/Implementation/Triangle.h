#pragma once
class Triangle
{
private:
	std::vector<SDL_FPoint> points;
	SDL_Color colour;
	float orientation;

public:
	Triangle(const std::vector<SDL_FPoint>&, SDL_Color&);
	bool rotate(double degrees);
	bool move(int xChange, int yChange);

	std::vector < SDL_Vertex> asVertex();

	void Seek(SDL_FRect&, float&);
	bool intersectsTarget(SDL_FRect&);


};

