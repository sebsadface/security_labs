source /usr/share/gef.py

# command "start" will run the following 4 consecutive commands:
# "catch exec" -> "run" -> "break main" -> "continue"
define start
    catch exec
    run
    break main
    continue
end

# command "iff" is an alias to "info frame"
define iff
    info frame
end

# command "ifr" is an alias to "info register"
define ifr
    info register
end