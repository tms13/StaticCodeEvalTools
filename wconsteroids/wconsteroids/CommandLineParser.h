#ifndef COMMAND_lINE_PARSER_H
#define COMMAND_lINE_PARSER_H

/*
 * Generic class to parse command lines. The public interface should not
 * require modifications for different programs. The help message will
 * need to change on a per program basis. The help message definition may
 * need to move to the ProgramOptions class.
 * 
 * This class should be portable to Windows, Linux and Unix operating
 * systems. There are ifdefs in the implementation for this purpose.
 */
#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>
#include "Executionctrlvalues.h"

class CommandLineParser
{
public:
	CommandLineParser(int argc, char* argv[], std::string progVersion);
	bool parse(ExecutionCtrlValues& execVars);
	void printHelpMessage() const;
	void printVersion() const noexcept;
	std::string_view getProgName() const noexcept { return programName; };

protected:
	void processSingleDashOptions(std::string_view currentArg);
	void processDoubleDashOptions(std::string_view currentArg);
	void SetDefaultOptionsWhenNoFlags();
	void findAllFilesToProcess(ExecutionCtrlValues& execVars);
	void extractAllArguments();

private:
	std::vector<std::string_view> args;
	std::string_view version;
	std::string_view programName;
	ProgramOptions options;
	std::unordered_map<std::string_view, bool&> doubleDashArgs;
	std::unordered_map<char, bool&> singleDashArgs;
	std::vector<std::string_view> NotFlagsArgs;
	bool useDefaultFlags;
};

#endif // COMMAND_lINE_PARSER_H