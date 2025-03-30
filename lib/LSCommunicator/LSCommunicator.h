#include <string>
#include <optional>
#include <unordered_set>

namespace LSCommunicator {

std::unordered_set<size_t> GetParseResult(
    const std::string& path_to_input_file,
    const std::string& path_to_decode_output_file);

}  // namespace LSCommunicator
