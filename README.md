# notes-cli

`notes-cli` is a minimal command-line note manager written in C.
It allows you to add, list, delete, and clear notes from a single file.

Notes are stored in:

```
$HOME/notes-cli/notes.txt
```

If the directory or file does not exist, it will be created automatically.

---

## Build

To compile the program:

```sh
make
```

This produces the binary `notes-cli`.

---

## Install

```sh
sudo make install
```

By default, the binary will be installed into `/usr/local/bin`.

---

## Uninstall

```sh
sudo make uninstall
```

Removes the installed binary from `/usr/local/bin`.

---

## Usage

```
notes-cli --add <note text>      Add a new note
notes-cli --list                 Show all notes
notes-cli --delete <number>      Delete note by number
notes-cli --clear                Clear all notes
```

### Examples

Add a note:

```sh
notes-cli --add "buy milk"
notes-cli --add "finish project"
```

List notes:

```sh
notes-cli --list
# [1]: buy milk
# [2]: finish project
```

Delete a note:

```sh
notes-cli --delete 1
notes-cli --list
# [1]: finish project
```

Clear all notes:

```sh
notes-cli --clear
notes-cli --list
# (no output)
```

---

## Makefile targets

* `make` — build the binary
* `make clean` — remove compiled binary
* `make install` — copy binary to `/usr/local/bin`
* `make uninstall` — remove installed binary

---

## License

This project is released under the GPL-3.0 License.
