file_strt = 0;
file_end = 0;
n=130;
axis manual;
axis([0 n 0 n 0 100]);
for i=file_strt:file_end
    filename = make_name('src',i,'.bin');
    disp(strcat('reading file ',filename));
    f=read_data(filename,n);
    disp(strcat('displaying ',filename));
    axis([0 n 0 n 0 100]);
    surfc(f);
    pause(.1);
    
end