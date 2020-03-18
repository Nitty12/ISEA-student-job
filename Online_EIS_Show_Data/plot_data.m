float = 1;

if float == 0

    load('results_frequency.mat');
    load('results_time.mat');

    results_time = results_time(2:5,1:inputsize/4);
    results_time = reshape(results_time,[],1);
    
    results_frequency = results_frequency(2:5,1:inputsize/4);
    results_frequency = reshape(results_frequency,[],1);
    
else
    load('results_frequency_float.mat');
    load('results_time_float.mat');

    results_time = results_time_float(2:3,1:inputsize/2);
    results_time = reshape(results_time,[],1);

    results_frequency = results_frequency_float(2:3,1:inputsize/2);
    results_frequency = reshape(results_frequency,[],1);
    
end 
    
    



    results_frequency_real = results_frequency(1:2:end);
    results_frequency_imag = results_frequency(2:2:end);
    results_frequency = results_frequency_real + 1i * results_frequency_imag;

    plot(1:inputsize,results_time)

    figure;
    plot(2:inputsize/2,abs(results_frequency(2:end)))



    freq_offline = fft(results_time);
    freq_offline = fftshift(freq_offline);
    
    freq_offline = freq_offline/inputsize;

    freq_offline = freq_offline(ceil(inputsize/2):end);
    freq_offline(2:end) = 2*freq_offline(2:end);

    figure;
    Fs = 1/1000;
    Fmax = 1/Fs/2;               
    frequency = linspace(-Fmax,Fmax,inputsize);
    %change to only positiv spectrum
    frequency = frequency(ceil(inputsize/2):end);
    
    plot(frequency(3:end), abs(freq_offline(3:end)));
    
