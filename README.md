## ABOUT

This text editor (vim wannabe) was built in `C` with less than **1000 LOC**, it doesn't need external libraries and utilizes standard **VT100** escape sequences. The guide I followed, along with future implementation ideas, are available below.

## REQUIREMENTS

- Linux environment;
- GNU Compiler collection `sudo apt-get install gcc make`;

## REFERENCES

| Link                                                                                                     | Source    |
| :------------------------------------------------------------------------------------------------------- | :-------- |
| [Kilo Original](https://github.com/antirez/kilo)                                                         | GitHub    |
| [Kilo Guide](https://viewsourcecode.org/snaptoken/kilo/index.html)                                       | Website   |
| [Vim](https://www.vim.org/)                                                                              | Website   |
| [C99](https://en.wikipedia.org/wiki/C99)                                                                 | Wikipedia |
| [ANSI C](https://en.wikipedia.org/wiki/ANSI_C)                                                           | Wikipedia |
| [ANSI Escape Code](https://en.wikipedia.org/wiki/ANSI_escape_code)                                       | Wikipedia |
| [Bit Field](https://en.wikipedia.org/wiki/Bit_field)                                                     | Wikipedia |
| [ASCII Table](https://www.asciitable.com/)                                                               | Website   |
| [Software Flow Control](https://en.wikipedia.org/wiki/Software_flow_control)                             | Wikipedia |
| [Teleprinter](https://en.wikipedia.org/wiki/Teleprinter)                                                 | Wikipedia |
| [VT100](https://en.wikipedia.org/wiki/VT100)                                                             | Wikipedia |
| [VT100 User Guide](https://vt100.net/docs/vt100-ug/chapter3.html#ED)                                     | Website   |
| [Ncurses](https://en.wikipedia.org/wiki/Ncurses)                                                         | Wikipedia |
| [Terminfo](https://en.wikipedia.org/wiki/Terminfo)                                                       | Wikipedia |
| [GNU Feature Test Macros](https://www.gnu.org/software/libc/manual/html_node/Feature-Test-Macros.html) | Website   |
| [Unix Time](https://en.wikipedia.org/wiki/Unix_time)                                                     | Wikipedia |
| [Variadic Functions](https://en.wikipedia.org/wiki/Variadic_function)                                    | Wikipedia |

## IDEAS

- [ ] More filetypes;
- [ ] Line numbers;
- [ ] Soft indent;
- [ ] Auto indent;
- [ ] Hard-wrap lines;
- [ ] Soft-wrap lines;
- [ ] Use ncurses;
- [ ] Config file;
- [ ] Modal editing;
- [ ] Multiple buffers.


## LICENSE

This project is a derivative work created from scratch, inspired by the [original guide](https://viewsourcecode.org/snaptoken/kilo/) authored by [snaptoken](https://github.com/snaptoken) and the [original project](https://github.com/antirez/kilo) developed by Salvatore Sanfilippo ([antirez](https://github.com/antirez)).

It is licensed under the [BSD 2-Clause License](https://github.com/jotavare/text-editor-in-c/blob/main/LICENSE) by Salvatore Sanfilippo, included within this repository.
