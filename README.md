# minishell

*42 School project — jaimega2 & rnuno-im*

## About

A fully functional Unix shell built from scratch in C. Minishell reads user input, tokenizes and parses commands, expands environment variables, handles pipes and redirections, and executes programs — mimicking the behavior of bash.

## Usage

```bash
make
./minishell
```

## Features

- **Interactive prompt** with command history (via `readline`)
- **Pipes** — chain commands with `|`
- **Redirections** — `>`, `>>`, `<`, `<<` (heredoc)
- **Environment variable expansion** — `$VAR`, `$?`
- **Quote handling** — single quotes (no expansion) and double quotes (with expansion)
- **Signal handling** — `Ctrl+C`, `Ctrl+D`, `Ctrl+\` behave like bash
- **Built-in commands:**

| Command | Description |
|---|---|
| `echo [-n]` | Print text |
| `cd [path]` | Change directory |
| `pwd` | Print working directory |
| `export [var=val]` | Set environment variable |
| `unset [var]` | Remove environment variable |
| `env` | Print environment |
| `exit [code]` | Exit the shell |

## Project Structure

```
minishell/
├── main.c
├── Makefile
├── includes/
│   ├── minishell.h       # Prototypes and includes
│   └── structs.h         # All type definitions
├── srcs/
│   ├── lexer/            # Tokenizer, preprocessor, quote handling
│   ├── parser/           # Token list → command structs
│   ├── expander/         # Variable expansion, quote removal
│   ├── executor/
│   │   ├── builtins/     # Built-in command implementations
│   │   ├── pipex/        # Pipe and process management
│   │   ├── redirections/ # Redirections and heredoc
│   │   └── signals/      # Signal handlers
│   └── utils/            # Shell loop, env utils, error printing
└── libft/                # Custom C library + ft_printf
```

## How It Works

```
Input → Preprocess → Tokenize → Parse → Expand → Execute
```

1. **Preprocess** — normalizes operators (`|`, `>`, `>>`, `<`, `<<`) adding spaces, handles heredoc markers
2. **Tokenize** — splits input into a token array respecting quotes
3. **Parse** — builds a `t_cmd` linked list with arguments and redirections per command
4. **Expand** — resolves `$VAR` and `$?`, strips quotes
5. **Execute** — forks processes, sets up pipes and redirections, runs builtins or `execve`

## Dependencies

Requires `readline`:

```bash
sudo apt-get install libreadline-dev
```

## Concepts Covered

- Process management (`fork`, `execve`, `waitpid`)
- File descriptors and redirections (`dup2`, `open`, `pipe`)
- Signal handling (`sigaction`)
- Environment variable management
- Lexical analysis and parsing
- Memory management with zero leaks
