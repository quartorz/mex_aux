classdef Status < double
    %STATUS 
    %   calc_lorenzが計算できたかどうかを表す列挙型
    
    enumeration
        Failed(0)
        Incomplete(1)
        Succeeded(2)
    end
    
end

