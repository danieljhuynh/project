" use spaces instead of tabs
:set expandtab
" default tab to 2 spaces
:set tabstop=2
" default shiftwidth of 2 spaces
:set shiftwidth=2
set autoindent
:set number
":set paste
:set nowrap
:syntax on
":let &t_Co=256
fun! <SID>StripTrailingWhitespaces()
    let l = line(".")
    let c = col(".")
    %s/\s\+$//e
    call cursor(l, c)
endfun
autocmd BufWritePre * :call <SID>StripTrailingWhitespaces()

" yellow highlight from causing search terms to be unreadable
":set hlsearch

" go straight to the first match you are searching for
:set incsearch

" always display a status line at the bottom of window
:set laststatus=2

" make the status line a lot more informative
:set statusline=%F%m%r%h%w\ [%{&ff}]\ [POS=%l,%c][%p%%]\ [LINES=%L]\ [BUFF=%n]

" display the current line and col at all times
:set ruler

" keep cursor away from edge of window for context
:set sidescroll=1
:set scrolloff=3

"" set color of comments.  Blue is easier to read than the default darkblue.
:highlight Comment ctermfg=Blue

" Go to previous cursor position when re-opening a file.
function! ResCur()
  if line("'\"") <= line("$")
    normal! g`"
    return 1
  endif
endfunction
augroup resCur
  autocmd!
  autocmd BufWinEnter * call ResCur()
augroup END

" from richard
"case insensative search
set ignorecase
set smartcase

"syntax highlighting settings
"set background=dark
"hi Identifier ctermfg=Yellow

"Don’t put these in unless you have issues
"Putty/EC compatibility
"set ttymouse=xterm
"set t_kb=^?

"Changes color
"colorscheme desert

"turn on mouse
"get mouse-=a
