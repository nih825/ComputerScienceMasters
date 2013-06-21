function [ data ] = read_data( file, n )
    fid=fopen(file,'r');
    header = fread(fid,[1,1],'long');
    data=fread(fid,[n,n],'double');
    fclose(fid);
end

