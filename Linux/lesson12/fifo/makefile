all:test_write test_read

test_write:write_fifo.c
	gcc $^ -o $@

test_read:read_fifo.c
	gcc $^ -o $@
