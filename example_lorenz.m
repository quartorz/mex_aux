if exist('calc_lorenz', 'file') ~= 3
    error([
        'calc_lorenz関数が見つかりません。' ....
        'mexコマンドを使ってMEXファイルを作成してください。'
    ]);
end

[r, s] = calc_lorenz([1, 1, 1], 0, 20, 1200);

if s == Status.Failed
    disp('全く精度保証できなかった');
    return
elseif s == Status.Incomplete
    disp('途中までしか精度保証できなかった');
else
    disp('最後まで精度保証できた');
end

plot3(mid(r.x(1, :)), mid(r.x(2, :)), mid(r.x(3, :)));