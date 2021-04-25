#include <regex>
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

#include "program.hpp"

namespace fs = std::filesystem;

#if defined(DEBUG) || defined(_DEBUG)
static std::string configuration = "Debug";
#else
static std::string configuration = "Release";
#endif

static int current_index;
static std::vector<ppp::Program> programs;
static std::shared_ptr<ppp::Program> current_program;

static void create_programs(fs::path root)
{
	int program_index = 0;

	for (auto& dir : fs::recursive_directory_iterator(root / "src"))
	{
		if (!dir.is_directory())
		{
			continue;
		}

		std::string dir_stem = dir.path().stem().string();
		fs::path program_exe = fs::path(root / "bin" / configuration / dir_stem).replace_extension("exe");

		if (fs::exists(program_exe))
		{
			ppp::Program program(program_index++, program_exe);
			programs.push_back(program);

			std::cout << "Added program " << program_exe << std::endl;
		}
		else
		{
			std::cerr << "Cannot find program at " << program_exe << std::endl;
		}
	}

	if (program_index == 0)
	{
		std::cerr << "No programs found in " << root / "src" << std::endl;
	}

	std::cout << std::endl;
}

static void prev_program()
{
	if (current_index > 0)
	{
		current_program = std::make_shared<ppp::Program>(programs[--current_index]);
		current_program->run();
	}
}

static void next_program()
{
	if (current_index < static_cast<int>(programs.size()) - 1)
	{
		current_program = std::make_shared<ppp::Program>(programs[++current_index]);
		current_program->run();
	}
}

int main(int argc, char* argv[])
{
	try
	{
		// determine program index
		if (argc > 1)
		{
			current_index = std::stoi(argv[1]);
		}

		// Determine location of executable
		auto root = std::filesystem::path(argv[0]).parent_path().parent_path().parent_path();

		// Create programs
		create_programs(root);

		// Run selected program
		if (programs.size() > 0)
		{
			current_program = std::make_shared<ppp::Program>(programs[current_index]);

			std::cout << "Running program \"" << static_cast<std::string>(*current_program) << "\":\n" << std::endl;
			current_program->run();
		}
		else
		{
			std::cerr << "No programs were located in " << (root / "src").string() << "." << std::endl;
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Program needs a number argument\n\t" << e.what() << std::endl;
		return 1;
	}

	return 0;
}
