#include "PPM.h"

namespace ch
{

// Contructors
PPM::PPM() noexcept : filename{"Test.ppm"},
					  num_cols{0},
					  num_rows{0}
{
}

PPM::PPM(const std::string &fn, const size_t &cols, const size_t &rows) : filename{fn},
																		  num_cols{cols},
																		  num_rows{rows}
{
}

void PPM::write(Vec3<> *pixels[])
{
	// add check to make new file
	std::ofstream outfile;
	outfile.open(filename);

	outfile << "P3"
			<< "\n";
	outfile << num_cols << " " << num_rows << "\n";
	outfile << MAX_COLOR << "\n";

	for (size_t row = num_rows - 1; row > 0; row--)
	{
		for (size_t col = 0; col < num_cols; col++)
		{
			const auto r = static_cast<int>(255.99f * pixels[row][col].x);
			const auto g = static_cast<int>(255.99f * pixels[row][col].y);
			const auto b = static_cast<int>(255.99f * pixels[row][col].z);
			outfile << r << " " << g << " " << b << "\n";
		}
	}
	outfile.close();
}

} // namespace ch
