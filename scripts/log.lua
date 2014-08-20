log_file = "debug_log.txt"

function datetime()
    return os.date("%Y.%m.%d %H:%M:%S")
end

function write_log(message)
    file = io.open(log_file, "a")
    file:write(datetime() .. ": " .. message .. "\n")
    io.close(file)
end
