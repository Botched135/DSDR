#include <filesystem>
#include <optional>
#include <fmt/core.h>

namespace DSDR
{
    // Should probably have a DB for Malice actions

    std::optional<int> LoadMDBFromFile(const std::filesystem::path& in_file_path);

}