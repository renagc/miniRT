#include <minirt.h>


float cylinder_intersect(t_vector pos, t_vector dir, float t, float r)
{   
    float a;
    float b;
    float c;
    float t1;
    float t2;

    a = (dir.x * dir.x) + (dir.z * dir.z);
    b = 2*(dir.x*(pos.x-center.x) + dir.z*(pos.z-center.z));
    c = (pos.x - center.x) * (pos.x - center.x) + (pos.z - center.z) * (pos.z - center.z) - (radius*radius);
    
    float delta = b*b - 4*(a*c);
	if(fabs(delta) < 0.001) 
        return (-1.0); 
    if(delta < 0.0) 
        return (-1.0);
    t1 = (-b - sqrt(delta))/(2*a);
    t2 = (-b + sqrt(delta))/(2*a);
    if (t1>t2) 
        t = t2;
    else 
        t = t1;
    r = pos.y + t*dir.y;
    if ((r >= center.y) && (r <= center.y + height))
        return (t);
    else 
        return (-1);
}

/**
* Returns the unit normal vector at a given point.
* Assumption: The input point p lies on the sphere.
*/
Vector Cylinder::normal(Vector p)
{
    Vector n = Vector (p.x-center.x,0,p.z-center.z);
    n.normalise();
    return n;
}