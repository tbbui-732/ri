# ri (re - vi)
## Background
Vi/Vim are fantastic text editing tools because they move the user away 
from their mouse and towards their keyboard. This transition leads to 
a more comfortable and efficient working environment.

However, a significant challenge with Vi/Vim is its learning curve. 
The absence of a mouse and the plethora of key combinations can take a 
while to get used to. This difficulty leads developers to shift towards 
ready-to-use solutions like GUI text editors and IDEs.

The primary objective of Ri is to provide a user-friendly alternative to 
Vi/Vim/Nvim, enhancing both visual appeal and incorporating more familiar 
key bindings for a seamless experience. 

## Is this basically neovim? 
While neovim is ultimately more mature and offers a wider range of customizability,
I believe that this can cause analysis-by-paralysis for the end-user, ultimately 
leading them to spend more time customizing their text-editor. 

Ri's goal is to default to a more user-friendly work environment, 
to which you can see the specifics at *Ideas*.

## Why rebuild from scratch?
Because building things from scratch is fun! I don't expect
ri to dominate other text-editors nor do I necessarily want it 
to. 

## Ideas (to eventually implement)
- Utilize key-bindings from VS code's vim package
    - Visually selecting a block of text and hitting tab will indent it
    - Built-in feature to comment out blocks of code like (select + gc)
- Xcode's vim status-bar
    - Shows user key-combinations with a snippet of what they do
- TODO: Think of more features to include

## Current build
- Implement cursor movement with base hjkl keys
- Line numbers and tildes (WIP)

## Contributing
Contributions are very welcome! If you'd like to contribute to this project,
make sure to follow the contribution guidelines.

## License 
This project is licensed under the MIT License. 

## Acknowledgements 
This project is heavily inspired by the vi/vim/nvim text editor.
