/**
 * Copyright (c) 2011-2014 sx developers (see AUTHORS)
 *
 * This file is part of sx.
 *
 * sx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef SX_DISPATCH_HPP
#define SX_DISPATCH_HPP

#include <memory>
#include <string>
#include <boost/program_options.hpp>
#include <sx/command.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
   
/**
 * Dispatch the command with the raw arguments as provided on the command line.
 *
 * @param[in]  argc  The number of elements in the argv array.
 * @param[in]  argv  The array of arguments, including the process.
 * @return           The appropriate console return code { -1, 0, 1 }.
 */
console_result dispatch(int argc, const char* argv[]);

/**
 * Invoke the command identified by the specified arguments.
 * The first argument in the array is the command symbolic name.
 *
 * @param[in]  argc   The number of elements in the argv parameter.
 * @param[in]  argv   Array of command line arguments excluding the process.
 * @return            The appropriate console return code { -1, 0, 1 }.
 */
console_result dispatch_invoke(int argc, const char* argv[]);

/**
 * Display usage for all commands.
 *
 * @return  True if displayed successfully.
 */
bool dispatch_usage();

/**
 * Get the config variable from the variable map.
 *
 * @param[in]  variables  The variable map to read the config from.
 * @return                The read path.
 */
boost::filesystem::path get_config_variable(
    boost::program_options::variables_map& variables);

/**
 * Load command line variables.
 *
 * @param[out] variables  The variable map to populate.
 * @param[in]  instance   The command instance for the current command.
 * @param[in]  argc       The number of elements in the argv parameter.
 * @param[in]  argv       Array of command line arguments excluding process.
 */
void load_command_variables(boost::program_options::variables_map& variables,
    command& instance, int argc, const char* argv[]) throw();

/**
 * Load configuration file variable.
 *
 * @param[out] variables  The variable map to populate.
 * @param[in]  instance   The command instance for the current command.
 */
void load_configuration_variables(
    boost::program_options::variables_map& variables, command& instance)
    throw();

/**
 * Load environment variable.
 *
 * @param[out] variables  The variable map to populate.
 * @param[in]  instance   The command instance for the current command.
 */
void load_environment_variables(
    boost::program_options::variables_map& variables, command& instance)
    throw();

/**
 * Load command line variable.
 *
 * @param[out] variables  The variable map to populate.
 * @param[out] message    Displayable error message in case of failure.
 * @param[in]  instance   The command instance for the current command.
 * @param[in]  argc       The number of elements in the argv parameter.
 * @param[in]  argv       Array of command line arguments excluding process.
 * @return                True if the load is successful.
 */
bool load_variables(boost::program_options::variables_map& variables, 
    std::string& message, command& instance, int argc, const char* argv[]);

} // sx

#endif