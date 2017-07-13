
#
# README
#
#  Bash script to simplify the running of the AFL (American Fuzzy Loop)
#
# It will:
#   - use AFL_HARDEN=1 to detect simple memory corruption
#   - use libdislocator to detect HEAP memory corruption
#   - use multi-thread AFL with tmux 4-panes splitted to ease viewing
#       - if you don't have tmux, then set $TMUX_SPLIT=no to run single-thread AFL
#   - use clang compiler to insert instrumentation (binary claimed to be more faster when fuzzing)
#
# Usage:
#   1) create any test cases inside the `input` folder, make sure those are distinct enough!
#   2) copy your binary source code into current directory
#   3) change the $CODE variable to your source code name
#   4) (optional) fill up $ARGV with program argument(s)
#   5) (optional) if want single-thread AFL, change $TMUX_SPLIT into `no`
#   6) run this script, `sh run-fuzzer.sh`
#

AFL_PATH=~/Desktop/afl-2.41b
INPUT_PATH=input
OUTPUT_PATH=sync_dir
CODE=chat-logger.c
ARGV=
TMUX_SPLIT=yes  # set no if you want to run single-threaded AFL

# compiles clang support for AFL
make -C $AFL_PATH/llvm_mode/ >> /dev/null

# compile with instrumentation insertion at each branches
# AFL_HARDEN=1 -> to detect simple memory bugs
AFL_HARDEN=1 $AFL_PATH/afl-clang-fast $CODE -o test_bin -g

# check input dir availability
if [ ! -d $INPUT_PATH ]; then
    printf "\n\n-- please create an input dir with initial test cases!\n\n"
    exit 1
fi

# create output dir (if not existed yet)
mkdir -p $OUTPUT_PATH

# run with libdislocator
# it helps to find heap related bugs
make -C $AFL_PATH/libdislocator >> /dev/null
AFL_PRELOAD=$AFL_PATH/libdislocator/libdislocator.so

#
# fuzz the goddamn binary!
#
if [ "$TMUX_SPLIT" = "yes" ]; then

    # run in tmux 4-panes window (multi-threads)
    tmux split-window -h "$AFL_PATH/afl-fuzz -i $INPUT_PATH -o $OUTPUT_PATH -S afl2 ./test_bin $ARGV"
    tmux split-window -v "$AFL_PATH/afl-fuzz -i $INPUT_PATH -o $OUTPUT_PATH -S afl4 ./test_bin $ARGV"
    tmux select-pane -R
    tmux split-window -v "$AFL_PATH/afl-fuzz -i $INPUT_PATH -o $OUTPUT_PATH -S afl3 ./test_bin $ARGV"
    tmux -2 attach-session -d 
    $AFL_PATH/afl-fuzz -i $INPUT_PATH -o $OUTPUT_PATH -M afl1 ./test_bin $ARGV

else 

    # single-thread
    $AFL_PATH/afl-fuzz -i $INPUT_PATH -o $OUTPUT_PATH ./test_bin $ARGV

fi
