clear all 

%read the signal 
[voice,fs]=audioread('Record1.m4a');
voice= voice(:,1); % make it mono
voice = voice';
time = 0:1/fs:(length(voice)-1)/fs;
subplot(5, 2, 1);
plot(time, voice);
xlabel('time'); ylabel('amplitude');
title('Original voice')

% Frequency Spectrum

voice_freq = fftshift(fft(voice));
freq = -fs/2: fs/(length(voice_freq)-1) : fs/2;
subplot(5, 2, 2);
plot(freq, abs(voice_freq))
xlabel('frequency'); ylabel('amplitude');
title('Frequency spectrum of the signal');

% Generate noise

brown = dsp.ColoredNoise('Color', 'brown', 'SamplesPerFrame', length(voice));
brownNoise = brown();
brownNoise = brownNoise' / max(brownNoise)/20;
subplot(5, 2, 3);
plot(time, brownNoise);
xlabel('time'); ylabel('amplitude');
title('Brown Noise');
subplot(5, 2, 4);
brownNoise_freq = fftshift(fft(brownNoise));
plot(freq, abs(brownNoise_freq));
xlabel('frequency'); ylabel('amplitude');
title('Frequency Spectrum of brown Noise');

% Adding Brown Noise to Voice

bVoice = voice+brownNoise;
subplot(5, 2, 5);
plot(time, bVoice);
xlabel('time'); ylabel('amplitude');
title('Noise Added Voice')
subplot(5, 2, 6);
bVoice_freq = fftshift(fft(bVoice));
plot(freq, abs(bVoice_freq));
xlabel('frequency'); ylabel('amplitude');
title('Frequency Spectrum of Noise Added Voice')

%Adding anti noise to the original with delay 

AntiBrownNoise=-brownNoise;
delay=2;%we created a delay in here as 2sec
N=delay/(1/fs);% N is the number of sample that we will shift for creating the delay
AntiBrownNoise=[zeros(1,N),AntiBrownNoise];% we added the zero samples at the begining of the AntiBrownNoise
voice= [voice,zeros(1,N)];%accordingly we adjust the length of our voices since we will add them all up
antiAdded=AntiBrownNoise+voice ;
subplot(5,2,7);
time = 0:1/fs:(length(voice)-1)/fs;
plot(time,antiAdded);
xlabel('time'); ylabel('amplitude');
title('AntiNoise Added Voice');
subplot(5, 2, 8);
anti_freq = fftshift(fft(antiAdded));
freq = -fs/2: fs/(length(anti_freq)-1) : fs/2;
plot(freq, abs(anti_freq));
xlabel('frequency'); ylabel('amplitude');
title('Frequency Spectrum of AntiNoise Added Voice')

%Adding the anti noise added voice to the noise added signal
brownNoise= [brownNoise,zeros(1,N)];
NoisySignalsAdded =antiAdded +brownNoise ;
subplot(5,2,9);
plot(time,NoisySignalsAdded );
xlabel('time'); ylabel('amplitude');
title('Noise and AntiNoiseAdded Signals Added');
subplot(5,2,10);
NoisySignalsAdded_freq= fftshift(fft(NoisySignalsAdded));
plot(freq, abs(NoisySignalsAdded_freq));
xlabel('frequency'); ylabel('amplitude');
title('Frequency Spectrum of Noise and AntiNoiseAdded SignalsAdded');

