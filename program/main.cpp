#include <ccbs/dirs/pragmas.hpp>
#include <ccbs/util/containers.hpp>
#include <ccbs/util/find_utils.hpp>
#include <ccbs/rule/rule.hpp>

using namespace ccsh::literals;

int main(int argc, const char ** argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: ccbs <package.ccbs.hpp>";
        return 1;
    }

    auto self_include_dir = "-I" + ccsh::fs::weakly_canonical(CCBS_DOT / "../include"_p).string();

    ccsh::command_builder<ccsh::gcc> pragma_command = ccsh::gcc();
    pragma_command.args().push_back(self_include_dir);
    pragma_command.args().emplace_back(argv[1]);
    pragma_command.args().emplace_back("-E");

    int result;
    auto includes = ccbs::get_all_pragmas(pragma_command, result);
    if (result != 0)
    {
        return (pragma_command > "/dev/null"_p).run();
    }

    // TODO: detect duplicates

    ccsh::fs::path header{argv[1]};

    std::string classname = header.filename().string();
    auto dot = classname.find('.');
    if (dot != std::string::npos)
        classname = classname.substr(0, dot);

    ccsh::fs::path output = "/tmp/"_p / ccsh::generate_filename();

    std::vector<std::string> args = {
        "-D_CCBS_CLASSNAME_AUTOGEN=" + classname,
        self_include_dir,
        "-L" + (CCBS_DOT / "../lib"_p).string(),
        "-Wl,-rpath," + (CCBS_DOT / "../lib"_p).string(),
        "-lccbs_lib",
        "-L" + (CCBS_DOT / "../../ccsh/lib"_p).string(),
        "-Wl,-rpath," + (CCBS_DOT / "../../ccsh/lib"_p).string(),
        "-lccsh_lib",
        "-I" + ccsh::fs::absolute(header).parent_path().string(),
        "-o",
        output.string(),
        "-x", "c++",
        "-" // read from stdin
    };

    for (const auto& dir : includes)
        args.push_back("-I" + dir.string());

    std::string program =
    "#include <" + header.string() + ">\n" +
    R"PROGRAM(
int main()
{
    return (_CCBS_CLASSNAME_AUTOGEN){}.build();
}
    )PROGRAM";

    ccsh::command gcc_command = ccsh::shell(ccbs::get_compiler_path(), args);

    result = (gcc_command < program).run();
    if (result != 0)
        return result;

    return ccsh::shell(output).run();
}
