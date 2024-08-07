
<?xml version="1.0" encoding="UTF-8"?>
<shellProgram>
    <overview>
        This is a simple shell program written in C that provides basic command-line functionality, including executing commands, managing history, handling signals, and supporting built-in commands like <command>cd</command>, <command>pwd</command>, <command>history</command>, and <command>exit</command>. It also supports special commands like <command>!!</command> to repeat the last command and <command>!n</command> to execute the nth command from history.
    </overview>
    <features>
        <feature>Command Execution: Executes both built-in and external commands.</feature>
        <feature>History Management: Keeps track of the last 10 commands entered and allows re-execution of those commands.</feature>
        <builtInCommands>
            <command>cd: Changes the working directory.</command>
            <command>pwd: Prints the current working directory.</command>
            <command>history: Prints the history of commands.</command>
            <command>exit: Exits the shell.</command>
            <command>help: Provides information about built-in commands.</command>
            <command>!!: Repeats the last command.</command>
            <command>!n: Repeats the nth command from history.</command>
            <command>!-: Clears the command history.</command>
        </builtInCommands>
        <feature>Signal Handling: Handles <signal>SIGINT</signal> (Ctrl+C) to provide a custom help message.</feature>
    </features>
    <files>
        <file>
            <name>main.c</name>
            <description>The main source file containing the implementation of the shell program.</description>
        </file>
    </files>
    <compilation>
        <command>gcc -o shell main.c</command>
    </compilation>
    <usage>
        <command>./shell</command>
    </usage>
    <codeStructure>
        <function>
            <name>tokenize_command</name>
            <description>Tokenizes the input command string into an array of tokens.</description>
        </function>
        <function>
            <name>read_command</name>
            <description>Reads a command from the keyboard into the buffer and tokenizes it.</description>
        </function>
        <function>
            <name>addHistory</name>
            <description>Adds a command to the history.</description>
        </function>
        <function>
            <name>printHistory</name>
            <description>Prints the command history.</description>
        </function>
        <function>
            <name>isDigit</name>
            <description>Checks if a character is a digit.</description>
        </function>
        <function>
            <name>getCommandNumber</name>
            <description>Extracts the command number from a token.</description>
        </function>
        <function>
            <name>getOtherCommandNumber</name>
            <description>Extracts a number from the beginning of a string.</description>
        </function>
        <function>
            <name>getCommandFromHistory</name>
            <description>Retrieves a command from history based on the command number.</description>
        </function>
        <function>
            <name>handle_SIGINT</name>
            <description>Handles the <signal>SIGINT</signal> signal and displays a help message.</description>
        </function>
        <function>
            <name>main</name>
            <description>The main function that initializes the shell, reads commands, and executes them.</description>
        </function>
    </codeStructure>
    <builtInCommandDetails>
        <command>
            <name>cd [directory]</name>
            <description>Changes the current working directory to <param>directory</param>. If <param>directory</param> is not provided, it changes to the home directory.</description>
        </command>
        <command>
            <name>pwd</name>
            <description>Prints the current working directory.</description>
        </command>
        <command>
            <name>history</name>
            <description>Prints the last 10 commands entered.</description>
        </command>
        <command>
            <name>exit</name>
            <description>Exits the shell.</description>
        </command>
        <command>
            <name>help [command]</name>
            <description>Provides information about built-in commands. If <param>command</param> is provided, it gives detailed information about that command.</description>
        </command>
        <command>
            <name>!!</name>
            <description>Repeats the last command entered.</description>
        </command>
        <command>
            <name>!n</name>
            <description>Repeats the nth command from history.</description>
        </command>
        <command>
            <name>!-</name>
            <description>Clears the command history.</description>
        </command>
    </builtInCommandDetails>
    <errorHandling>
        The program handles various errors, such as invalid input, command not found, and execution failures, by displaying appropriate error messages.
    </errorHandling>
    <signalHandling>
        The program handles the <signal>SIGINT</signal> signal (Ctrl+C) to display a help message instead of terminating the shell.
    </signalHandling>
    <futureImprovements>
        <improvement>Add more built-in commands.</improvement>
        <improvement>Enhance error handling and validation.</improvement>
        <improvement>Implement additional features like piping and redirection.</improvement>
    </futureImprovements>
    <contributors>
        <name>Your Name</name>
    </contributors>
    <note>
        Feel free to modify and extend the functionality as needed. Contributions and suggestions are welcome!
    </note>
</shellProgram>
