# **AIMS**witcher
**AIMS**witcher, **A**n **I**nput **M**ethod **S**witcher that **AIMS** to support switching between Chinese and English input methods or between Chinese and English modes in one input method when switching between Vim's insert and normal modes

> Note: This tool is only available for Windows

## Installation
Just download the executable file from the [releases page](https://github.com/A-23187/AIMSwitcher/releases/latest)

## Usage
```
AIMSwitcher, An Input Method Switcher
Usage: AIMSwitcher [OPTION]... [ARG]...

  --im [INPUTMETHOD]      show the current input method if INPUTMETHOD is omitted,
                          otherwise switch to the specified input method
  --imm [INPUTMETHODMODE] show the current input method mode if INPUTMETHODMODE is omitted,
                          otherwise switch to the specified input method mode
```

### Examples
AIMSwitcher uses the language identifier (i.e., the locale ID) to switch to the corresponding input method. And the locale ID of Simplified Chinese (zh_CN) is 2052, the locale ID of American English (en_US) is 1033. You can use the option `--im` without argument to discover the locale ID of your current input method
```sh
# show the locale ID of the current input method
AIMSwitcher.exe --im
```

For me, I installed Microsoft Pinyin input method for Simplified Chinese (2052), and US Keyboard input method for American English (1033). So for switching between these two input methods:
```sh
# switch to Microsoft Pinyin IM
AIMSwitcher.exe --im 2052
# switch to US Keyboard IM
AIMSwitcher.exe --im 1033
```

Microsoft Pinyin IM supports two language modes: Chinese and English. AIMSwitcher can switch between these two modes like below:
```sh
# switch to Chinese mode
AIMSwitcher.exe --imm 1025
# switch to English mode
AIMSwitcher.exe --imm 0

# you can use this option without argument to find the key of your current mode
AIMSwitcher.exe --imm
```
> Note: The functionality of switching input method mode has only been tested with Microsoft Pinyin IM, and contributions for testing with other input methods are welcome.

### AIMSwitcher + Vim
- Switch to English input method when leaving insert mode to normal mode
```vim
autocmd InsertLeave * silent !AIMSwitcher.exe --im 1033
```
- Switch to English mode of Chinese input method instead of switching input method when leaving insert mode to normal mode
```vim
autocmd InsertLeave * silent !AIMSwitcher.exe --imm 0
```

### AIMSwitcher + [VSCodeVim](https://github.com/VSCodeVim/Vim)
- Switch input method
```json
"vim.autoSwitchInputMethod.enable": true,
// Use English input method by default
"vim.autoSwitchInputMethod.defaultIM": "1033",
"vim.autoSwitchInputMethod.obtainIMCmd": "AIMSwitcher.exe --im",
// Switch to English input method when leaving insert mode to normal mode,
// And the additional argument {im} is just a placeholder, as required by VSCodeVim
"vim.autoSwitchInputMethod.switchIMCmd": "AIMSwitcher.exe --im 1033 {im}"
```
- Switch input method mode
```json
"vim.autoSwitchInputMethod.enable": true,
// Use Chinese input method by default (for me, I use Microsoft Pinyin IM)
"vim.autoSwitchInputMethod.defaultIM": "2052",
"vim.autoSwitchInputMethod.obtainIMCmd": "AIMSwitcher.exe --imm",
// Switch to English mode of the Chinese input method when leaving insert mode to normal mode,
// And the additional argument {im} is just a placeholder, as required by VSCodeVim
"vim.autoSwitchInputMethod.switchIMCmd": "AIMSwitcher.exe --imm 0 {im}"
```
About VSCodeVim's `autoSwitchInputMethod` feature, find more information [here](https://github.com/VSCodeVim/Vim#input-method)

## Credits
- [daipeihust/im-select](https://github.com/daipeihust/im-select)
- [yfzhao20/Shift-IM-for-VSCode](https://github.com/yfzhao20/Shift-IM-for-VSCode)
- [how to change input method when press <esc> in vim? - Stack Overflow](https://stackoverflow.com/a/71523260)

## License
[MIT License](https://github.com/A-23187/AIMSwitcher/blob/master/LICENSE)