main : sources headers
	$ gcc main.c ./Sources/print.c ./Sources/write_read_file.c ./Sources/date.c ./Sources/trie.c ./Sources/check_bool_string.c ./Sources/reservation_hotel.c ./Sources/menu_func.c -o main

headers : ./Headers/check_bool_string.h ./Headers/date.h ./Headers/menu_func.h ./Headers/print.h ./Headers/reservation_hotel.h ./Headers/struct_enum.h ./Headers/trie.h ./Headers/write_read_file.h
sources : main.c ./Sources/print.c ./Sources/write_read_file.c ./Sources/date.c ./Sources/trie.c ./Sources/check_bool_string.c ./Sources/reservation_hotel.c ./Sources/menu_func.c

