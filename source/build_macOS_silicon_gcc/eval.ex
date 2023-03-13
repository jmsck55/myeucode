--with trace
--trace(1)
puts(1, "Hi world.\n")
integer fn = open("data.e", "w")
puts(fn, "--with trace\n--trace(1)\n")
printf(fn, "public object data = %d\n", 2 + 2)
close(fn)
