/*


*/

#include <aligner.hpp>
#include <arg_parse.hpp>

#include <seqan3/core/debug_stream.hpp>
#include <seqan3/argument_parser/exceptions.hpp>

int main(int argc, char ** argv)
{
    try
    {
        auto args = initialize_argument_parser(argc, argv);
        return hopa_run(args);
    }
    catch (seqan3::validation_error const & ext)
    {
        seqan3::debug_stream << "Invalid argument: " << ext.what() << "\n"; 
        return -1;
    }
}
