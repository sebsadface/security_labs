source /usr/share/gef.py

# command "start" will run the following 4 consecutive commands:
# "catch exec" -> "run" -> "break main" -> "continue"
define start
    catch exec
    run
    break main
    continue
end

# command "iff" is alias to "info frame"
define iff
    info frame
end