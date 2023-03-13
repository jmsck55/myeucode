-- Copyright (c) 2023 James Cook
-- Call Euphoria code by writing a script using "Euphoria", not as fast as "C".

--with trace

--trace(1)

constant FILENAME_EVAL_EX = "eval.ex"
constant FILENAME_DATA_E = "data.e"

integer fn

object t, t0 = time()

fn = open(FILENAME_EVAL_EX, "w")
if fn = -1 then
    puts(1, "Couldn't open file.\n")
    abort(1/0)
end if
puts(fn, "--with trace\n--trace(1)\n")
puts(fn, "puts(1, \"Hi world.\\n\")\n")
printf(fn, "integer fn = open(\"%s\", \"w\")\n", {FILENAME_DATA_E})
puts(fn, "puts(fn, \"--with trace\\n--trace(1)\\n\")\n")
printf(fn, "printf(fn, \"public object data = %%d\\n\", {%d + %d})\n", {2, 2})
puts(fn, "close(fn)\n")
close(fn)

--trace(1)
atom error_code
error_code = system_exec("eui " & FILENAME_EVAL_EX, 2)
? error_code

t = time() - t0

puts(1, "execution time in seconds:\n")
? t

