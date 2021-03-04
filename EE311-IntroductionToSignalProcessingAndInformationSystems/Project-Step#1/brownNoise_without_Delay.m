clear all 

%read the signal 
[voice,fs]=audioread('Record1.m4a');
voice= voice(:,1); % make it mono
voice = voice';
time = 0:1/fs:(length(voice)-1)/fs;
subplot(5, 2, 1);
plot(time, voice);
title('Original voice')

% Frequency Spectrum

voice_freq = fftshift(fft(voice));
freq = -fs/2: fs/(length(voice_freq)-1) : fs/2;
subplot(5, 2, 2);
plot(freq, abs(voice_freq))
title('Frequency spectrum of the signal');

% Generate noise

brown = dsp.ColoredNoise('Color', 'brown', 'SamplesPerFrame', length(voice));
brownNoise = brown();
brownNoise = brownNoise' / max(brownNoise)/20;
subplot(5, 2, 3);
plot(time, brownNoise);
title('Brown Noise');
subplot(5, 2, 4);
brownNoise_freq = fftshift(fft(brownNoise));
plot(freq, abs(brownNoise_freq));
title('Frequency Spectrum of brown Noise');

% Adding Brown Noise to Voice
bVoice = voice+brownNoise;
subplot(5, 2, 5);
plot(time, bVoice);
title('Noise Added Voice')
subplot(5, 2, 6);
bVoice_freq = fftshift(fft(bVoice));
plot(freq, abs(bVoice_freq));
title('Frequency Spectrum of Noise Added Voice')

%anti noise
AntiBrownNoise=-brownNoise;
antiAdded=AntiBrownNoise+voice;
subplot(5, 2, 7);
plot(time, antiAdded);
title('AntiNoise Added Voice')
subplot(5, 2, 8);
addedVoice_freq = fftshift(fft(antiAdded));
plot(freq, abs(addedVoice_freq));
title('Frequency Spectrum of AntiNoise Added Voice')

 %anti noise ve noise summed 
 
 orginal=antiAdded+brownNoise ;
 subplot(5, 2, 9);
plot(time, orginal);
title('AntiNoise Added Voice + BrownNoise')
subplot(5, 2, 10);
orginal_freq = fftshift(fft(orginal));
plot(freq, abs(orginal_freq));
title('Frequency Spectrum of AntiNoise Added Voice + BrownNoise')

