if exist('calc_lorenz', 'file') ~= 3
    error([
        'calc_lorenz関数が見つかりません。' ....
        'mexコマンドを使ってMEXファイルを作成してください。'
    ]);
end

r = calc_lorenz([1, 1, 1], 0, 20, 1200);

plot3(mid(r.x(1, :)), mid(r.x(2, :)), mid(r.x(3, :)));