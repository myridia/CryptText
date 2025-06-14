    while true; do
      inotifywait -e modify "hello_sodium.c"
      make linux
      ./hello_sodium_linux
    done
