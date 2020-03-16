#include "arg_parse.hpp"

cmd_arguments initialize_argument_parser(int argc, char ** argv)
{
    cmd_arguments args{};
    seqan3::argument_parser parser{"HOPA", argc, argv};
    
    parser.info.app_name = "hopa";
    parser.info.author = "Ian B Harvey";
    parser.info.short_description = "Homogenize Orientation by Pairwise Alignment.";
    parser.info.synopsis = {"./hopa [options] my_input_sequences.fa"};
    parser.info.version = "0.1";

    parser.add_positional_option(args.in_file_path, "A fast(aq) file to be oriented.");
    parser.add_option(args.in_file_reference, 'r', "reference", "An optional reference file to orient against.");
    parser.add_option(args.out_file_path, 'o', "output", "Output file for oriented sequences.");
    parser.add_flag(args.overwrite, 'w',"overwrite", "Overwrite the input file with the output.");
    parser.add_flag(args.force, 'f', "force", "Force the program to overwrite an existing file.");
    parser.add_flag(args.reverse, '\0', "reverse", "Reverse the global orientation of the output"
                                                    "compared to the reference.");
    // TODO: Implement gzip and bzip functionality
    /*
    parser.add_flag(args.use_bzip,'j',"bzip", "BZip the output file.");
    parser.add_flag(args.use_gzip,'z',"gzip", "GZip the output file.");
    */
    parser.add_option(args.threads, 't', "threads", "Number of threads to use.", seqan3::option_spec::DEFAULT, seqan3::arithmetic_range_validator{1,static_cast<double>(std::thread::hardware_concurrency())});

    parser.parse();
    check_arguments(args);
    
    return args;
}


void check_arguments(cmd_arguments & args)
{
    check_in_file(args.in_file_path);
    check_in_file(args.in_file_reference);
    check_out_file(args.out_file_path, args.force);
    return;
}

void check_in_file(std::filesystem::path & a_path)
{
    // Check the input file #1
    if(a_path.is_relative())
    {
        if(std::filesystem::exists(std::filesystem::current_path() / a_path))
        {
            a_path = std::filesystem::current_path() / a_path;
        }
        else
        {
            throw seqan3::validation_error(seqan3::detail::to_string( "The relative-path file ", a_path, " was not found."));
        }
    }else{
        if(!std::filesystem::exists(a_path))
        {
            throw seqan3::validation_error(seqan3::detail::to_string( "The full-path file ", a_path, " was not found."));
        }
    }
}

void check_out_file(std::filesystem::path & a_path, const bool is_force)
{
    if(a_path.is_relative())
    {
        a_path = std::filesystem::current_path() / a_path;
        if(std::filesystem::exists(a_path) && !is_force)
        {
            throw seqan3::validation_error(seqan3::detail::to_string( "Cowardly refusing to use an existing output file. Use '-f' to overwrite."));
        }
    }

    return;
}