#include "Hitable_List.h"

namespace ch
{

void Hitable_List::add(std::unique_ptr<Hitable> hitable_ptr)
{
	h_list.push_back(std::move(hitable_ptr));
}

bool Hitable_List::hit_any(const Ray &r, float t_min, float t_max, hit_record &rec) const
{
	hit_record temp_rec;
	bool hit_anything = false;
	float closest_so_far = t_max;

	for (auto &hitable : h_list)
	{
		if (hitable->hit(r, t_min, closest_so_far, temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hit_anything;
}

} // namespace ch
