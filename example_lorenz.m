if exist('calc_lorenz', 'file') ~= 3
    error([
        'calc_lorenz�֐���������܂���B' ....
        'mex�R�}���h���g����MEX�t�@�C�����쐬���Ă��������B'
    ]);
end

[r, s] = calc_lorenz([1, 1, 1], 0, 20, 1200);

if s == Status.Failed
    disp('�S�����x�ۏ؂ł��Ȃ�����');
    return
elseif s == Status.Incomplete
    disp('�r���܂ł������x�ۏ؂ł��Ȃ�����');
else
    disp('�Ō�܂Ő��x�ۏ؂ł���');
end

plot3(mid(r.x(1, :)), mid(r.x(2, :)), mid(r.x(3, :)));