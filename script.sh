valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --trace-children=yes \
         --log-file=valgrind-out.txt \
                 ./pipex archivo1.txt "grep adios" "cat" archivo2.txt