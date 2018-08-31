#include "Sphere.h"

namespace ch {

	Sphere::Sphere(Vec3<> cen, float r, std::unique_ptr<Material> mat) : center{ cen }, radius{ r }, mat_ptr{std::move(mat)}
	{}
	
	bool Sphere::hit(const Ray & r, float t_min, float t_max, hit_record & rec) const
	{
		Vec3<> oc;
		oc = r.origin() - center;

		const float a = r.direction() * r.direction();
		const float b = (oc * r.direction());
		const float c = (oc * oc) - (radius * radius);

		const float discriminant = b * b - a * c;

		if (discriminant > 0)
		{
			float temp = (-b - sqrt(b*b - a * c)) / a;
			if (temp < t_max && temp > t_min)
			{
				rec.t = temp;
				rec.p = r.point_at_t(rec.t);
				rec.normal = (rec.p - center) / radius; 
				rec.material_ptr = mat_ptr.get();
				return true;
			}
			temp = (-b + sqrt(b*b - a * c)) / a;
			if (temp < t_max && temp > t_min)
			{
				rec.t = temp;
				rec.p = r.point_at_t(rec.t);
				rec.normal = (rec.p - center) / radius; 
				rec.material_ptr = mat_ptr.get();
				return true;
			}
		}
		return false;
	}

} // namespace ch
