function [ name ] = make_name( base, ext, suffix )
    if (ext < 10)
        name = strcat(base,'00',int2str(ext),suffix);
    elseif (ext < 100)
        name = strcat(base,'0',int2str(ext),suffix);
    else
        name = strcat(base,int2str(ext),suffix);
    end
end

