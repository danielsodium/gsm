# GTK Session Manager

GSM is a session manager written in C++ to quickly change between projects using a command line interface. I plan to integrate a GUI using GTK to manage and edit sessions in the future. Currently, I use an AGS widget to quickly change between sessions which can be found in my [dotfiles](https://github.com/danielsodium/dotfiles). All sessions are stored under `~/.config/gsm`. Currently I have a lot of features hardcoded in for my own convenience which will change in the future.

## Installation

Clone the respository and run `compile.sh`.

```bash
git clone https://github.com/danielsodium/gsm.git
cd gsm && ./compile.sh
```

## Usage
All outputs are given in a json format to `std::out`.

To enter a session run
```bash
./gsm <session>
```
This will create a session with name `<session>` if one doesn't exist, otherwise it will load the session.

To set the path to the project directory, run
```bash
./gsm <session> set pwd <path>
```
To open a terminal window run
```bash
./gsm <session> term
```
To open a neovide window run
```bash
./gsm <session> edit
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

[MIT](https://choosealicense.com/licenses/mit/)
