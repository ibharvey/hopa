#pragma once

#include <seqan3/std/filesystem>
#include <seqan3/argument_parser/all.hpp>

struct cmd_arguments
{
    std::filesystem::path in_file_path{};
    std::filesystem::path in_file_reference{};
    std::filesystem::path out_file_path{"output.fa"};
    bool reverse{};
    bool overwrite{};
    bool force{};
    bool use_gzip{};
    bool use_bzip{};
    bool has_reference{false};
    std::size_t threads{std::thread::hardware_concurrency()};
};

cmd_arguments initialize_argument_parser(int argc, char ** argv);

void check_arguments(cmd_arguments & args);
void check_in_file(std::filesystem::path & a_path);
void check_out_file(std::filesystem::path & a_path, const bool is_force);
