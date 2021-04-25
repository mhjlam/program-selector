#include <filesystem>

namespace ppp
{
	class Program
	{
	public:
		Program(int in_index, std::filesystem::path in_exe)
		: index(in_index), exe_path(in_exe)
		{
			name = exe_path.stem().string();
			directory = exe_path.parent_path();
		}

		~Program() = default;

		operator std::filesystem::path()
		{
			return exe_path;
		}

		operator std::string()
		{
			return name;
		}

		void run()
		{
			std::system(exe_path.string().c_str());
		}

	private:
		int index;

		std::string name;
		std::filesystem::path exe_path;
		std::filesystem::path directory;
	};
}
