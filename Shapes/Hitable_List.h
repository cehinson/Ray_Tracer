#pragma once

#include <vector>

#include "Hitable.h"

namespace ch
{

class Hitable_List
{
	std::vector<std::unique_ptr<Hitable>> h_list;

  public:
	Hitable_List() = default;

	void add(std::unique_ptr<Hitable> hitable_ptr);
	std::pair<bool, hit_record> hit_any_2(const Ray& r, float t_min, float t_max) const;
	bool hit_any(const Ray &r, float t_min, float t_max, hit_record &rec) const;
};

} // namespace ch
