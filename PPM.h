#pragma once

#include <fstream>
#include <string>
#include <cfloat>

#include "core/Ray.h"
#include "core/Vec3.h"
#include "core/Camera.h"

namespace ch {

	// Writes PPM files
	class PPM
	{
		std::string filename;
		const size_t MAX_COLOR = 255;
		const size_t num_rows, num_cols;

	public:
		PPM() noexcept;
		PPM(const std::string& fn, const size_t& cols, const size_t& rows);
		void write(Vec3<>* pixels[]);

	};

} // namespace ch
