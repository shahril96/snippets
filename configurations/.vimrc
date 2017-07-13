
" ---------------------------------------------
"
" Do this beforehand : 
"
" $ git clone https://github.com/VundleVim/Vundle.vim.git
"   ~/.vim/bundle/Vundle.vim
"
" If you have upgraded your YCM, then follow instruction from line (/search .ycm.extra_conf.py)  
" if you want C-family auto-complete feature 
"
" VIM BUNDLE PLUGIN MANAGER BELOW HERE
" ---------------------------------------------

set nocompatible              " be iMproved, required
filetype off                  " required

" set the run time path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

" ---------------------------------------------
"  Plugins not used anymore
" ---------------------------------------------

" Plugin 'klen/python-mode' # syntastic already done this to me
" Plugin 'vim-scripts/indentpython.vim' # python-mode already done this to me
" Plugin 'Lokaltog/powerline', {'rtp': 'powerline/bindings/vim/'} # migrated to vim-airline
" Plugin 'NLKNguyen/papercolor-theme' # migrated to vim-colors-solarized
" Plugin 'takac/vim-hardtime' # bet that I have kill that bad habit now :)

" ---------------------------------------------
"  Plugins currently use
" ---------------------------------------------

Plugin 'VundleVim/Vundle.vim' " let Vundle manage Vundle, required
Plugin 'Valloric/YouCompleteMe'
Plugin 'altercation/vim-colors-solarized'
Plugin 'bling/vim-airline'
Plugin 'scrooloose/syntastic' " syntax checking 
Plugin 'easymotion/vim-easymotion' " highlight words when navigating
Plugin 'scrooloose/nerdtree'
Bundle 'jistr/vim-nerdtree-tabs'

" All of your Plugins must be added before the following line

call vundle#end()            " required
filetype plugin indent on    " required

" change leader key to space
" my only exception own config to be put on the top
let mapleader=" "

" ---------------------------------------------
" VIM BUNDLE PLUGIN MANAGER ABOVE HERE
" ---------------------------------------------

" ---------------------------------------------
" START CONFIGURATIONS FOR PLUGINS
" ---------------------------------------------

" integrate vim-airline with syntastic
let g:airline#extensions#syntastic#enabled = 1

" use flake8 for python syntax checking
"
" make sure to install flake8 first $ sudo apt-get install pyflakes $ sudo pip
" install flake8
" 
" if flake8 don't work as expected, maybe there's an error with flake8 try to
" manually run flake8 outside the vim, that may help to figure out what error
" did flake8 have
let g:syntastic_python_checkers = ['flake8']

" use python3 instead of python2
let g:ycm_python_binary_path = '/usr/bin/python3'

" use clang_check for default c++ syntax checking
let g:syntastic_cpp_checkers = ['clang_check']

" disable syntax checker from ycm this is done in order to enable syntax
" checker for syntastic
let g:ycm_show_diagnostics_ui = 0

" this is to enable semantic auto-complete to all c/c++ files
"
" normally, you need to provide .ycm_extra_conf.py to every folder in your
" project, but i think this is cumbersome to add it all the time so better to
" globally enable it everytime
" 
" you need to download the appropriate .ycm.extra_conf.py in order to have C-family auto-complete
"
" $ wget https://goo.gl/sTC28B -O ~/.vim/bundle/YouCompleteMe/.ycm.extra_conf.py
"
let g:ycm_global_ycm_extra_conf = "~/.vim/bundle/YouCompleteMe/.ycm.extra_conf.py"

" automatically close preview windows after we'd selected text from YCM
let g:ycm_autoclose_preview_window_after_completion = 1
let g:ycm_autoclose_preview_window_after_insertion = 1

" vim-airline might get confused if preview YCM windows is opened
" exclude the preview to make it works again
let g:airline_exclude_preview = 1

" Enable vim-arline's pseudo-tab with buffer
let g:airline#extensions#tabline#enabled = 1

" Jump to anywhere you want with minimal keystrokes, with just one key binding.
" `s{char}{label}`
nmap f <Plug>(easymotion-overwin-f)

let g:EasyMotion_smartcase = 1 " Turn on case insensitive feature
let g:EasyMotion_do_mapping = 0 " Disable default mappings

" hook vim search to use easymotion's search function
map  / <Plug>(easymotion-sn)
omap / <Plug>(easymotion-tn)

" These `n` & `N` mappings are options. You do not have to map `n` & `N` to EasyMotion.
" Without these mappings, `n` & `N` works fine. (These mappings just provide
" different highlight method and have some other features )
map  n <Plug>(easymotion-next)
map  N <Plug>(easymotion-prev)

map <Leader>l <Plug>(easymotion-lineforward)
map <Leader>j <Plug>(easymotion-j)
map <Leader>k <Plug>(easymotion-k)
map <Leader>h <Plug>(easymotion-linebackward)

let g:EasyMotion_startofline = 0 " keep cursor column when JK motion

map <Leader>n <plug>NERDTreeTabsToggle<CR>

" ---------------------------------------------
" END CONFIGURATIONS FOR PLUGINS
" ---------------------------------------------

" ---------------------------------------------
" BELOW IS MY OWN VIMRC CONFIGS
" ---------------------------------------------

syntax enable
set t_Co=256
let g:solarized_termcolors=256
set background=light
colorscheme solarized

" enabling vim's syntax highlighting feature
filetype plugin on

" set default spell checking language to en_us
set spell spelllang=en_us

" enable line number inside vim 
set number 

" set copy/paste text directly from system clipboard
set clipboard=unnamedplus

" show <leader> when we pressed it
set showcmd

" enable case-insensitive search
set ic

" enable vim-airline to show
set laststatus=2

" Allow saving of files as sudo when I forgot to start vim using sudo.
" reference :
" https://stackoverflow.com/questions/2600783/how-does-the-vim-write-with-sudo-trick-work
cmap w!! w !sudo tee > /dev/null %

" enable mouse operation well there is a time when I prefer to use mouse
" rather than keyboard :)
set mouse=a

" use UTF-8 as vim default encoding
set encoding=utf-8

" set tab to use space
set expandtab " use space instead of pure tab \t
set tabstop=4 " set tab size to 4
set shiftwidth=4 " set shift size for >> and <<
set softtabstop=4 " backspace 4 spaces

" load file type-specific indent files 
filetype indent on

" visual auto complete for command menu
set wildmenu

" show matching part for (), [] and {}
set showmatch

" indent when moving to the next line while writing code
set autoindent

" show a visual line under the cursor's current line
set cursorline

" sometime you will accidentally felt into Ex mode well it's an old vi feature,
" disable it for good reference :
" http://www.bestofvim.com/tip/leave-ex-mode-good/
nnoremap Q <nop>

" search as characters are entered
set incsearch

" enable highlight and replace with clipboard in visual mode note : press 'r'
" while highlighting in visual to replace
vmap r "_dP

" press `Enter` in Insert to mode to create a newline after current line this
" option don't switch to Insert mode, it will stay in Normal mode
nmap <CR> o<Esc>

" remap key <leader>g for YCM GoTo
nnoremap <leader>g :YcmCompleter GoTo<CR>

" easier Ctrl+motion to switch between splitted windows
nnoremap <C-J> <C-W><C-J>
nnoremap <C-K> <C-W><C-K>
nnoremap <C-L> <C-W><C-L>
nnoremap <C-H> <C-W><C-H>

" using Source Code Pro font in gVim
set anti enc=utf-8
set guifont=Source\ Code\ Pro\ 11

" make buffer switch to be more easier
nnoremap <F5> :buffers<CR>:buffer<Space>

" ---------------------------------------------
" END MY VIMRC CONFIGS
" ---------------------------------------------
